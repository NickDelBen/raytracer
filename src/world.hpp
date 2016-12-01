// Describes a 3d world

#ifndef _h_world
#define _h_world

#include <vector>

#include "plane.hpp"
#include "color.hpp"
#include "line.hpp"
#include "material.hpp"
#include "light.hpp"
#include "world_object.hpp"
#include "sphere.hpp"
#include "triangle.hpp"

// Defines the world
class World
{
public:
    /***********************
    * Creates and returns a new world
    ***********************/
    World();

    /***********************
    * Adds a new light to the world
    * @param new_light the new light to add
    ***********************/
    void addLight(Light* new_light);

    /***********************
    * Adds a new plane to the world
    * @param new_plane the new plane to add
    ***********************/
    void addPlane(Plane* new_plane);

    /***********************
    * Gets the specified plane from the world
    * @param id ID (index) of plane to get
    * @return Plane at the specified index
    ***********************/
    Plane* getPlane(int id);

    /***********************
    * Adds a new sphere to the world
    * @param new_sphere the new sphere to add
    ***********************/
    void addSphere(Sphere* new_sphere);

    /***********************
    * Adds a new triangle to the world
    * @param new_triangle the new triangle to add
    ***********************/
    void addTriangle(Triangle* new_triangle);

    /***********************
    * Adds a new material to the world
    * @param new_material the new material to add
    ***********************/
    void addMaterial(Material* new_material);

    /***********************
    * Gets the specified material from the world
    * @param id ID (index) of material to get
    * @return Pointer to material at specified index
    ***********************/
    Material* getMaterial(int id);

    /***********************
    * Gets the number of spheres in the world
    * @return Number of spheres
    ***********************/
    int numSpheres();

    /***********************
    * Gets the number of lights in the world
    * @return Number of lights
    ***********************/
    int numLights();

    /***********************
    * Gets the number of planes in the world
    * @return Number of planes
    ***********************/
    int numPlanes();

    /***********************
    * Gets the number of materials in the world
    * @return Number of materials
    ***********************/
    int numMaterials();

    /**********************
    * Gets the number of triangles in the world
    * @return Number of triangles
    **********************/
    int numTriangles();

    /**********************
    * Gets the closest world object to the specified ray
    * @param ray         Line to check for intersection
    * @param max_dist    Maximum distance to check for intersection
    * @param coefficient Distance along the line the intersection occurs
    * @param normal      Vector representing normal of intersectoion
    * @return NULL if no intersect occurs otherwise the intersected object
    **********************/
    WorldObject* getClosestIntersect(Line* ray, float max_dist, float* coefficient, Vector3* normal);

    /**********************
    * Gets the closest world object to the specified ray
    * @param ray         Line to check for intersection
    * @param max_dist    Maximum distance to check for intersection
    * @param coefficient Distance along the line the intersection occurs
    * @param normal      Vector representing normal of intersectoion
    * @param exclude     Pointer to object to exclude from intersect check
    * @return NULL if no intersect occurs otherwise the intersected object
    **********************/
    WorldObject* getClosestIntersect(Line* ray, float max_dist, float* coefficient, Vector3* normal, WorldObject* exclude);

    /***********************
    * Gets the specified sphere from the world
    * @param id ID (index) of sphere to get
    * @return Sphere at the specified index
    ***********************/
    Sphere* getSphere(int id);

    /***********************
    * Gets the specified triangle from the world
    * @param id ID (index) of the triangle to get
    * @return Triangle at the specified index
    ***********************/
    Triangle* getTriangle(int id);

    /***********************
    * Gets the specified light from the world
    * @param id ID (index) of light to get
    * @return Light at the specified ondex
    ***********************/
    Light* getLight(int id);

    /***********************
    * Gets the color of the world background 
    * @return Background color
    ***********************/
    Color* getBackground();

    /**********************
    * Gets the global ambient light
    * @return Global ambient light value
    **********************/
    Color* getAmbient();

    /***********************
    * Sets the global ambient light to the specified value
    * @param new_ambient Value for global ambient light
    ***********************/
    void setAmbient(Color* new_ambient);

    /***********************
    * Sets the world background to the specified color
    * @param new_color Color for the world background
    ***********************/
    void setBackground(Color* new_color);

    /***********************
    * Checks if the specified ray intersects any obects other than the specified
    * @param ray      Line to check for intersect with
    * @param max_dist Maximum distance to cehck for intersection
    * @param exclude  Pointer to object to exclude from intersect check
    * @return 1 if intersects and object otherwise 0
    ***********************/
    int checkIntesect(Line* ray, float max_dist, WorldObject* exclude);

private:
    /* The background color fo the world */
    Color background;
    /* The global ambient light */
    Color ambient;
    /* The lights in the world */
    std::vector<Light> lights;
    /* The spheres in the world */
    std::vector<Sphere> spheres;
    /* The materials that exist in the world */
    std::vector<Material> materials;
    /* The triangles in the world */
    std::vector<Triangle> triangles;
    /* The planes that make up the world */
    std::vector<Plane> planes;
};

#endif