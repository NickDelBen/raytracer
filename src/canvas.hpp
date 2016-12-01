
#ifndef _h_canvas
#define _h_canvas

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <ctime>
#include <vector>
#include <string>
#include <cstdint>
#include <cstdlib>
#include <chrono>
#include <cstdio>

#define DEFAULT_WINDOW_X 50
#define DEFAULT_WINDOW_Y 50
#define DEFAULT_REDRAW_DELAY 100
#define MESSAGE_FONT GLUT_BITMAP_TIMES_ROMAN_10
#define FONT_HEIGHT 10
// Utility parameters
#define MILLISECOND 1000
#define CONVERT_MICROSECONDS_SECONDS(ms) ((ms)/1000000.0)
// Number of frames to keep for fps tally
#define FPS_SAMPLE_FRAMES 5

// Describes the fps counter data
typedef struct {
    uint8_t index;
    float times[FPS_SAMPLE_FRAMES];
    float sum;
} FPSCounter;

// Defines a pixel
typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} Pixel;

// Defines text to be displayed
typedef struct {
    float x;          // X position of text
    float y;          // Y position of text
    Pixel c;          // Color of text
    std::string text; // Actual characters to be written
} Message;

/**********************
* Gets string representation of current fps
* @return Current fps as string
**********************/
std::string get_string_fps();

/**********************
* Gets the current fps
* @return current fps
**********************/
float get_fps();

/**********************
* Calculates the current fps
* @param current_time Time it took to draw the current frame
**********************/
void next_fps(float current_time);

/**********************
* Window reshape event hander
**********************/
void reshape(int w, int h);

/**********************
* Adds a message to be drawn next frame
* @param x    X-coordinate for start of text
* @param y    Y-coordiante of start position for text
* @param r    red componant of text color
* @param g    green componant of text color
* @param b    blue componat of text color
* @param text Text to display
**********************/
void add_message(float x, float y, int r, int g, int b, std::string text);

/**********************
* Displays all the pending messages to the screen
**********************/
void display_messages();

/**********************
* Creates a new canvas
* @param width        Width of the opengl window
* @param height       Height of the opengl window
* @param window_title Name of the opengl window
**********************/
void create_canvas(int height, int width, std::string window_name);

/**********************
* Sets the keyboard callbacks to the specified function
* @param func Callback fucntion for keypresses
**********************/
void set_keyboard_callback(void (func)(unsigned char key, int x, int y));

/**********************
* Set the loop function for the canvas.
* The specified function will be called every specified amount of time
* @param func Animation function that will be called between redraws
* @param time Amount of time (ms) between redraws
**********************/
void loop_function(void (func)(), int time);

/**********************
* Initilizes the canvas
**********************/
void init_canvas(int argc, char** argv);

/***********************
* Sets the pixel at the current location to the specified value
* @param x x-coordinate of the pixel to set
* @param y y-coordinate of the pixel to set
* @param r red value of the pixel
* @param g freen value of the pixel
* @param b blue value of the pixel
***********************/
void set_pixel(int x, int y, int r, int g, int b);

/***********************
* Frees the memory allocated for the canvas
***********************/
void free_canvas();

/**********************
* Redraws the canvas
**********************/
void display();

/***********************
* Exits opengl and destroys the canvas
***********************/
void end_canvas();

/***********************
* Loops the animation function
* @param t time (ms) between redraws
***********************/
void timer_callback(int t);

#endif