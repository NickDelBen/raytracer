// Ray traces the specified scene
// Nick DelBen
// November 20, 2016

#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <fstream>
#include <pthread.h>
#include <string>

#include "util.h"
#include "canvas.hpp"
#include "color.hpp"
#include "sphere.hpp"
#include "raytracer.hpp"

// Program parameters
#define WINDOW_NAME "Tracer"
#define ANIMATE_SPHERES 1
#define MINIMUM_SPHERE_SPEED 3.0
#define MAXIMUM_SPHERE_SPEED 18.0
#define MINIMUM_SHERE_HEIGHT 0
#define MAXIMUM_SPHERE_HEIGHT 500
// Optimization parameters
#define WORKER_THREADS 8
#define MAX_FPS 30
#define EASTER_EGG 1

// Describes the data being sent to a thread
typedef struct {
    int thread_id;
} thread_info;

void timed_execution();  // Times the exercution of the trace rays function
void trace_rays();       // Ray traces a frame of the scene
void* render_function(); // Function for a worker thread to render it's part of the scene
void animate_scene();    // Animates the scene
// Callbacks for the keys during execution
void key_handlers(unsigned char key, int x, int y);

// The ray tracer
Raytracer rt;
// The number of frames that have been rendered
int rendered_frames = 0;
// Directions the spheres are travelling
float* directions;

// Animates the scene in the specified manner
void animate_scene()
{
    int sphere_iterator;
    Sphere* current_sphere;
    float next_step;

    for (sphere_iterator = 0; sphere_iterator < rt.getWorld()->numSpheres(); sphere_iterator++) {
        current_sphere = rt.getWorld()->getSphere(sphere_iterator);
        next_step = current_sphere->getPosition()->getY() + directions[sphere_iterator];
        next_step += directions[sphere_iterator] < 0 ? -current_sphere->getRadius() : current_sphere->getRadius();
        // Check if below speed
        if (next_step < MINIMUM_SHERE_HEIGHT || next_step > MAXIMUM_SPHERE_HEIGHT) {
            directions[sphere_iterator] *= -1;
        }
        current_sphere->getPosition()->setY(current_sphere->getPosition()->getY() + directions[sphere_iterator]);
    }
}

// Function for a worker thread to render it's part of the scene
void* render_function(void* arg)
{
    int current_job, pixel_x, pixel_y;
    Color result;
    thread_info* data = (thread_info*) arg;
    current_job = data->thread_id;
    while (current_job < rt.getCamera()->planeWidth() * rt.getCamera()->planeHeight()) {
        // Calculate the coordinates of the current pixel
        pixel_y = current_job / rt.getCamera()->planeWidth();
        pixel_x = current_job % rt.getCamera()->planeWidth();
        // Increment the job
        current_job += WORKER_THREADS;
        // Get the pixel at the current location
        result = rt.getPixel(pixel_x, pixel_y);
        // Store the calculated pixel on the canvas
        set_pixel(pixel_x, pixel_y, result.getRed(), result.getGreen(), result.getBlue());
    }
    return NULL;
}

void trace_rays()
{
    int thread_i;
    pthread_t thread_id[WORKER_THREADS];
    thread_info thread_infos[WORKER_THREADS];

    // Animate the scene
    if (ANIMATE_SPHERES) {
        animate_scene();
    }
    // Create the worker threads for rendering
    for (thread_i = 0; thread_i < WORKER_THREADS; thread_i++) {
        thread_infos[thread_i].thread_id = thread_i;
        pthread_create(&thread_id[thread_i], NULL, render_function, (void*) &thread_infos[thread_i]);
    }
    // Wait for the worker threads to finish
    for (thread_i = 0; thread_i < WORKER_THREADS; thread_i++) {
        pthread_join(thread_id[thread_i], NULL);
    }
    // Add the fps message to the screen
    add_message(0, rt.getCamera()->planeHeight() - FONT_HEIGHT, 255, 255, 255, get_string_fps());
}

// Keyboard shortcuts
void key_handlers(unsigned char key, int x, int y) {
    switch (key) {
        // Q key exits opengl
        case 'q':
            rt.freeRays();
            free_canvas();
            exit(0);
            break;
        case 'n':
            if (EASTER_EGG) {
                printf("Nick ;)\n");
            }
        default:
            break;
    }
}


// Ray traces a frame of the scene
int main(int argc, char** argv)
{
    std::istream* source;
    std::ifstream file_in;
    int sphere_iterator;

    setbuf(stdout, NULL);
    // Seed the random generator
    srand((unsigned) time(NULL));
    source = &std::cin;
    // Check if a file was wpecified to read from
    if (argc == 1) {
        // If no file specified assume world defined in stdin
        printf("Reading world from stdin\n");
    } else if (argc == 2) {
        // If file specified assume that is source file
        file_in.open(argv[1]);
        // Ensure file opened properly
        if (! file_in.is_open()) {
            printf("There was an error opening the world file: %s\n", argv[1]);
        }
        source = &file_in;
        printf("Reading world from %s\n", argv[1]);
    } else {
        // Invalid execution
        printf("Usage:\n    ./bin/raytracer <world_file>\n");
        return 0;
    }
    // Create the raytracer
    if (!rt.readFrom(source)) {
        printf("World file %s was malformed.\n", argv[1]);
        printf("    Ensure a camera and background color are specified.\n    Ensure all linked materials are created before objects use them\n");
        return 0;
    }
    // Initially soheres are travelling down
    directions = (float*) malloc(sizeof(float) * rt.getWorld()->numSpheres());
    for (sphere_iterator = 0; sphere_iterator < rt.getWorld()->numSpheres(); sphere_iterator++) {
        directions[sphere_iterator] = get_random_float(MINIMUM_SPHERE_SPEED, MAXIMUM_SPHERE_SPEED);
    }
    // Create a canvas to show the result    
    create_canvas(rt.getCamera()->planeWidth(), rt.getCamera()->planeHeight(), WINDOW_NAME);
    // Bind our key callbacks to the canvas loop
    set_keyboard_callback(key_handlers);
    // Bind our raytrace function to the canvas draw loop
    loop_function(trace_rays, MILLISECOND / MAX_FPS);
    // Initilize the application
    init_canvas(argc, argv);
    
    return 0;
}