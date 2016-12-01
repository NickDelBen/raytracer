// Describes a ray tracer

#ifndef _h_raytracer
#define _h_raytracer

#include <cmath>
#include <algorithm>
#include <iostream>

#include "world.hpp"
#include "world_object.hpp"
#include "plane.hpp"
#include "sphere.hpp"
#include "triangle.hpp"
#include "color.hpp"
#include "camera.hpp"
#include "material.hpp"
#include "light.hpp"

#define MAXIMUM_RAYTRACE_DEPTH 1
#define MAXIMUM_DISTANCE 25000.0
#define DEFAULT_REFLECTIVE_COEFFICIENT 1.0
#define REFLECTION_BIAS 60

// Defines a raytracer for a 3d world
class Raytracer
{
public:
    Raytracer(){}
    ~Raytracer();

    /***********************
    * Reads a raytracer from the specified stream
    * @param stream Stream to read the raytracer from
    * @return 1 if world is read properly otherwise 0
    ***********************/
    int readFrom(std::istream* stream);

    /***********************
    * Compleatly traces the ray at the specific pixel
    * @param x X-coordinate of pixel to trace
    * @param y Y-coordinate of pixel to trace
    * @return Color of the pixel at the specified x,y coordinate on the imaging plane
    ***********************/
    Color getPixel(int x, int y);

    /***********************
    * Compleatly traces the specified ray
    * @param ray   Ray to be traced
    * @param depth Current reflective depth of the ray
    * @return Color of pixel resulting from specified ray
    ***********************/
    Color traceRay(Line* ray, int depth);

    /***********************
    * Gets the world
    * @return Pointer to the world being traced
    ***********************/
    World* getWorld();

    /***********************
    * Gets the camera
    * @reutrn pointer to the camera
    ***********************/
    Camera* getCamera();

    /***********************
    * Cretes the list fo rays taht are to be traced
    ***********************/
    void createRays();

    /***********************
    * Gets the specified ray
    * @param x X coordinate of ray to get
    * @param y Y coordinate of ray to get
    * @return pointer to the specified ray
    ***********************/
    Line* getRay(int x, int y);

    /**********************
    * Gets the specified ray
    * @param index Index of ray in raylist to return
    * @return pointer to the specified ray
    **********************/
    Line* getRay(int index);

    /**********************
    * Frees the space allocated for rays
    **********************/
    void freeRays();

    /**********************
    * Calculates the reflection ray
    * @param intial_ray       Initial ray that caused the trace to occur
    * @param intersection     Position the intersection with an object occured
    * @param intersect_normal Normal to the point of intersection
    * @return Reflection Ray from point of incidence
    **********************/
    static Line calculareReflectionRay(Line* initial_ray, Vector3* intersection, Vector3* intersect_normal);

    /**********************
    * Calculates the ambient shading of an object
    * @param material      Material hit by the light
    * @param world_ambient Amient light throughout the world
    * @return Ambient light
    **********************/
    static Color calculateAmbient(Material* material, Color* world_ambient);

    /**********************
    * Calculates the diffuse lighting of an intersection
    * @param ray                 Light ray
    * @param intersection_normal Normal to the intersection wth the object
    * @param light               Light ray is directed from
    * @param material            Material the light ray is hitting
    * @return Diffuse light
    **********************/
    static Color calculateDiffuse(Line* ray, Vector3* intersection_normal, Light* light, Material* material);

    /**********************
    * Calculates the specular lighting of a reflection
    * @param initial_ray         Initial ray from plane
    * @param reflection_ray      Ray reflected off object to light
    * @param intersection_normal Normal to intersection with object
    * @param light               Light ray is directed from
    * @param material            Material light ray is hitting
    * @return Specular light
    **********************/
    static Color calculateSpecular(Line* initial_ray, Line* reflection_ray, Vector3* intersection_normal, Light* light, Material* material);

private:
    /* The current rays in the world */
    Line* rays;
    /* The world being raytraced */
    World world;
    /* The camera in the world */
    Camera camera;
};


#endif