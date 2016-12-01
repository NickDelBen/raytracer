// Describes a plane

#ifndef _h_plane
#define _h_plane

#include "world_object.hpp"
#include "vector.hpp"
#include "line.hpp"
#include "material.hpp"

#define PLANE_ROUNDING_OFFSET 0.005

// Defines a plane in 3 space
class Plane : WorldObject
{
public:
    /***********************
    * Cretes and returns a new plane
    * @param normal Direction normal to the plane
    * @param point  Point on the plane anchoring it along the normal
    ***********************/
    Plane(Vector3* normal, Vector3* point);

    /***********************
    * Creates and returns a new plane from the specified stream
    * Format: <normal> <point>
    * @param mat    Material this triangle is made from
    * @param stream Stream to read triangle details from
    ***********************/
    Plane(Material* mat, std::istream* stream);

    /***********************
    * Checks if the specified line intersects with the plane
    * @param line        Line to check for intersection with
    * @param max_dist    Maximum distance along line to check for intersection
    * @param coefficient Distance along the line the intersection occurs
    * @param normal      Vector representing normal of intersectoion
    * @return 1 if there is an intersection otherwise 0
    ***********************/
    int intersects(Line* ray, float max_dist, float* coefficient, Vector3* normal);

    /***********************
    * Sets the material to the specified material
    * @param mat Material the plane is made of
    ************************/
    void setMaterial(Material* mat);

    /***********************
    * Gets the material this plane is made of
    * @return Material properties of the plane
    ***********************/
    Material* getMaterial();

    /***********************
    * Override stream operator
    ***********************/
    friend std::ostream& operator<< (std::ostream& stream, Plane& plane);

private:
    /* The normal to the plane */
    Vector3 normal;
    /* A point on the plane */
    Vector3 point;
    /* Material the plane is made of */
    Material* plane;
};

#endif