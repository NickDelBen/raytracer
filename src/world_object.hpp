// Describes an object in the world

#ifndef _h_world_obejct
#define _h_world_obejct

#include "vector.hpp"
#include "material.hpp"
#include "line.hpp"

// The minimum intercept distance (SEE: http://www.cprogramming.com/tutorial/floating_point/understanding_floating_point_representation.html)
#define MINIMUM_INTERCEPT_DISTANCE 0.0001f

// Defines an object in the world
class WorldObject
{
public:
    /***********************
    * Checks if the specified line intersects with the object
    * @param line        Line to check for intersection with
    * @param max_dist    Maximum distance along line to check for intersection
    * @param coefficient Distance along the line the intersection occurs
    * @param normal      Vector representing normal of intersectoion
    * @return 1 if there is an intersection otherwise 0
    ***********************/
    virtual int intersects(Line* ray, float max_dist, float* coefficient, Vector3* normal)=0;

    /* Gets the material of the object */
    virtual Material* getMaterial()=0;
protected:
    /* The material of the object */
    Material* material;
};

#endif