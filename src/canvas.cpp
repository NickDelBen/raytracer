
#include "canvas.hpp"

/* The canvas pixels */
Pixel * pixels;
/* The canvas dimensions */
int canvas_height;
int canvas_width;
/* The title of the canvas window */
std::string window_name;
/* The animation function */
void (*animate)();
/* The keyboard callback function */
void (*key_callbacks)(unsigned char key, int x, int y) = NULL;
/* Time between redraws */
int redraw_delay;
/* Pending messages to be written */
std::vector<Message> messages;
// Current fps timer
FPSCounter status = {0, {0}, 0};

// Gets string representation of current fps
std::string get_string_fps()
{
    char buffer[64];
    sprintf(buffer, "FPS: %.2f", get_fps());
    return buffer;
}

// Gets the current fps
float get_fps()
{
   return 1.0 / (status.sum / FPS_SAMPLE_FRAMES);
}

// Calculates the current fps and adds the time for the current frame to the title
void iterate_fps(float current_time)
{
    // Modify the sum
    status.sum = status.sum - status.times[status.index] + current_time;
    // Change the value at the current idnex of the circular array queue
    status.times[status.index] = current_time;
    // Increment the index of the curcular array
    status.index = (status.index + 1) % FPS_SAMPLE_FRAMES;
}

// Sets the message to be drawn at the next frame
void add_message(float x, float y, int r, int g, int b, std::string text) {
   Message new_message;
   new_message.x = x;
   new_message.y = y;
   new_message.c.red = r;
   new_message.c.green = g;
   new_message.c.blue = b;
   new_message.text = text;
   messages.push_back(new_message);
}

// Displays the specified text at the specified potition
void display_messages() {
   std::vector<Message>::iterator current_message;
   int character_iterator;

   // Iterate over the messages
   for (current_message = messages.begin(); current_message != messages.end(); ++current_message) {
      // Set the color of the message
      glColor3ub(current_message->c.red, current_message->c.green, current_message->c.blue);
      // Set the location of the message
      glRasterPos2i(current_message->x, current_message->y);
      // Draw the chracters
      for (character_iterator = 0; character_iterator < current_message->text.length(); character_iterator++) {
         glutBitmapCharacter(MESSAGE_FONT, current_message->text.at(character_iterator));
      }
   }
   // Empty the pending messages
   messages.clear();
}

// Clocked loop
void timer_callback(int t)
{
    std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();
    animate();
    glutPostRedisplay();
    std::chrono::high_resolution_clock::time_point end_time = std::chrono::high_resolution_clock::now();
    long long duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    iterate_fps(CONVERT_MICROSECONDS_SECONDS(duration));
    glutTimerFunc(redraw_delay, timer_callback, 0);
}

// Redraws the canvas
void display()
{
   int x_itr;
   int y_itr;
   Pixel * p;

   // Redraw the pixels
   glBegin(GL_POINTS);
   for (y_itr = 0; y_itr < canvas_height; y_itr++) {
      for (x_itr = 0; x_itr < canvas_width; x_itr++) {
         p = &pixels[y_itr * canvas_width + x_itr];
         glColor3ub(p->red, p->green, p->blue);
         glVertex2f(x_itr, y_itr);
      }
   }
   glEnd();

   display_messages();
   glutSwapBuffers();
}

// Creates a new canvas
void create_canvas(int height, int width, std::string window_name)
{
   canvas_height = height;
   canvas_width = width;
   window_name = window_name;
   redraw_delay = DEFAULT_REDRAW_DELAY;
   pixels = (Pixel *) std::malloc(height * width * sizeof(Pixel));
   std::memset(pixels, 0, height * width * sizeof(Pixel));
}

// Initilizes the canvas
void init_canvas(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(canvas_height, canvas_width);
   glutInitWindowPosition(DEFAULT_WINDOW_X, DEFAULT_WINDOW_Y);
   glutCreateWindow(window_name.c_str());
   if (key_callbacks != NULL) {
      glutKeyboardFunc(key_callbacks);
   }
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   timer_callback(redraw_delay);
   glutMainLoop();
}

// Sets the keyboard callbacks to the specified function
void set_keyboard_callback(void (func)(unsigned char key, int x, int y))
{
    key_callbacks = func;
}

// Sets the pixel at the current location to the specified value
void set_pixel(int x, int y, int r, int g, int b)
{
   Pixel * p;

   p = &pixels[y * canvas_width + x];
   p->red = r;
   p->green = g;
   p->blue = b;   
}

// Frees the memory allocated for the canvas
void free_canvas()
{
   std::free(pixels);
}

// Set the loop function for the canvas.
void loop_function(void (func)(), int time)
{
   animate = func;
   redraw_delay = time;
}

// Reshape the window event handler
void reshape(int w, int h)
{
   // Set viewport size
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   // Set relative ortho
   glOrtho(0, canvas_width, 0, canvas_height, -1, 1);  
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}
