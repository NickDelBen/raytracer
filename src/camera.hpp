// Describes a camera

#ifndef _h_camera
#define _h_camera

#include <iostream>

#include "vector.hpp"
#include "line.hpp"

// Defines a camera in 3 space
class Camera
{
public:
    /***********************
    * Creates and returns a new camera
    * @param eye          Position of the eye
    * @param top_left     Position of top left of imaging plane
    * @param bottom_right Position of bottom right of imaging plane
    ***********************/
    Camera(Vector3 eye, Vector3 top_left, Vector3 bottom_right);

    /***********************
    * Creates a new camera from the specified stream
    * Format: <eye x> <eye y> <eye z> <imaging plane top left <x, y, z>> <imagine blane bottom right <x, y, z>>
    * @param stream Stream to read parameters from
    ***********************/
    Camera(std::istream* stream);
    Camera(){}
    ~Camera(){}

    /***********************
    * Gets a ray for the specified location on the imaging plane
    * @param x X-coordinate on the imaging plane for ray to pass through
    * @param y Y-coordinate on the imaging plane for ray to pass through
    * @return Ray going from origin, corresponding to the specified pixel
    ***********************/
    Line getRay(int x, int y);

    /************************
    * Gets the position of the camera
    * @return pointer to position of the camera
    ************************/
    Vector3* getPosition();

    /************************
    * Gets the top left of the imaging plane
    * @return pointer to top left of imaging plane
    ************************/
    Vector3* getTopLeft();

    /************************
    * Gets the bottom_right of the imaging plane
    * @return pointer to bottom right of imaging plane
    ************************/
    Vector3* getBottomRight();

    /***********************
    * Gets the height of the imaging plane
    * @return Height of the imaging plane
    ***********************/
    int planeHeight();

    /***********************
    * Gets the width of the imaging plane
    * @return Width of the imaging plane
    ***********************/
    int planeWidth();

    /***********************
    * Override the stream operator
    ***********************/
    friend std::ostream& operator<< (std::ostream& stream, Camera& matrix);

private:
    /* The position of the camera eye */
    Vector3 position;
    /* Top left of imaging plane */
    Vector3 top_left;
    /* Borrom right of imaging plane */
    Vector3 bottom_right;
};

#endif