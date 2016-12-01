// Describes a sphere

#ifndef _h_sphere
#define _h_sphere

#include <iostream>

#include "world_object.hpp"
#include "vector.hpp"
#include "line.hpp"
#include "material.hpp"

// Defines a sphere in 3 space
class Sphere : WorldObject
{
public:
    /***********************
    * Creates and returns a new sphere
    * @param position Position of the sphere
    * @param radius   Radius of the sphers
    * @param material Material of the sphere
    ***********************/
    Sphere(Vector3* position, float radius, Material* material);

    /***********************
    * Creates a sphere from the specified stream with the specified material
    * format: <radius> <position x> <position y> <position z>
    * @param mat    Material this sphere is made from
    * @param stream Stream to read sphere details from
    ***********************/
    Sphere(Material* mat, std::istream* stream);

    Sphere(){}
    ~Sphere(){}

    /***********************
    * Checks if this sphere intersects with the specified line
    * @param ray         Line to check for intersetction
    * @param max_dist    Maximum distance to check for the ray (dont want to check forever)
    * @param coefficient Location to store the amount along the line that the sphere intersects
    * @param normal      Vector representing normal of intersectoion
    * @return 0 if they do not intersect, else return 1 if they do intersect
    ***********************/
    int intersects(Line* ray, float max_dist, float* coefficient, Vector3* normal);

    /***********************
    * Gets the position of the sphere
    * @return Sphere's position
    ***********************/
    Vector3* getPosition();

    /***********************
    * Sets the position of the sphere to the specified value
    * @rparam new_position New position for the sphere
    ***********************/
    void setPosition(Vector3* new_position);

    /***********************
    * Gets the radius of the sphere
    * @return Radius of the sphere
    ***********************/
    float getRadius();

    /***********************
    * Gets the material of this sphere
    * @return Material this sphere is composed of
    ***********************/
    Material* getMaterial();

    /***********************
    * Override stream operator
    ***********************/
    friend std::ostream& operator<< (std::ostream& stream, Sphere& sphere);
private:
    /* The location of the sphere */
    Vector3 position;
    /* The radius of the sphere */
    float radius;
};

#endif