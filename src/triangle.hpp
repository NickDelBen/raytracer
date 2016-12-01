// Decribes a traingle

#ifndef _h_triangle
#define _h_triangle

#include <iostream>

#include "world_object.hpp"
#include "vector.hpp"
#include "line.hpp"
#include "material.hpp"

#define DISTANCE_OFFSET 0.005

// Defines a triangle in 3 space
class Triangle : WorldObject
{
public:

    /***********************
    * Creates a triangle from the specified stream with the specified material
    * format: <point 1> <point 2> <point 3>
    * @param mat    Material this triangle is made from
    * @param stream Stream to read triangle details from
    ***********************/
    Triangle(Material* mat, std::istream* stream);
    Triangle(){};
    ~Triangle(){};

    /***********************
    * Gets the material of this triangle
    * @return Material this triangle is composed of
    ***********************/
    Material* getMaterial();

    /***********************
    * Checks if the specified line intersects with the triangle
    * @param line        Line to check for intersection with
    * @param max_dist    Maximum distance along line to check for intersection
    * @param coefficient Distance along the line the intersection occurs
    * @param normal      Vector representing normal of intersectoion
    * @return 1 if there is an intersection otherwise 0
    ***********************/
    int intersects(Line* ray, float max_dist, float* coefficient, Vector3* normal);

    /***********************
    * Override stream operator
    ***********************/
    friend std::ostream& operator<< (std::ostream& stream, Triangle& triangle);

private:

    /* First point of triangle */
    Vector3 p1;
    /* Second point fo triangle */
    Vector3 p2;
    /* Third point of triangle */
    Vector3 p3;
};

#endif
