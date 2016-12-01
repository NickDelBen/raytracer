
#include "world.hpp"

// Creates and returns a new world
World::World()
{
    this->lights = std::vector<Light>();
    this->spheres = std::vector<Sphere>();
    this->planes = std::vector<Plane>();
}

// Gets the global ambient light
Color* World::getAmbient()
{
    return &(this->ambient);
}

// Sets the global ambient light to the specified value
void World::setAmbient(Color* new_ambient)
{
    this->ambient = *new_ambient;
}

// Gets the specified triangle from the world
Triangle* World::getTriangle(int id)
{
    return &(this->triangles[id]);
}

// Adds a new light to the world
void World::addLight(Light* new_light)
{
    this->lights.push_back(*new_light);
}

// Adds a new sphere to the world
void World::addSphere(Sphere* new_sphere)
{
    this->spheres.push_back(*new_sphere);
}

// Adds a new plane to the world
void World::addPlane(Plane* new_plane)
{
    this->planes.push_back(*new_plane);
}

// Gets the specified plane from the world
Plane* World::getPlane(int id)
{
    return &(this->planes[id]);
}

// Gets the number of planes in the world
int World::numPlanes()
{
    return this->planes.size();
}

// Gets the number of spheres in the world
int World::numSpheres()
{
    return this->spheres.size();
}

// Gets the number of materials in the world
int World::numMaterials()
{
    return this->materials.size();
}

// Gets the number of triangles in the world
int World::numTriangles()
{
    return this->triangles.size();
}

// Gets the specified sphere from the world
Sphere* World::getSphere(int id)
{
    return &(this->spheres[id]);
}

// Gets the color of the world background]
Color* World::getBackground()
{
    return &this->background;
}

// Gets the number of lights in the world
int World::numLights()
{
    return this->lights.size();
}

// Gets the specified light from the world
Light* World::getLight(int id)
{
    return &(this->lights[id]);
}

// Adds a new material to the world
void World::addMaterial(Material* new_material)
{
    this->materials.push_back(*new_material);
}

// Adds a new triangle to the world
void World::addTriangle(Triangle* new_triangle)
{
    this->triangles.push_back(*new_triangle);
}

// Gets the specified material from the world
Material* World::getMaterial(int id)
{
    return &(this->materials[id]);
}

// Sets the world background to the specified color
void World::setBackground(Color* new_color)
{
    this->background = *new_color;
}

// Gets the closest world object to the specified ray
WorldObject* World::getClosestIntersect(Line* ray, float max_dist, float* coefficient, Vector3* normal)
{
    return this->getClosestIntersect(ray, max_dist, coefficient, normal, NULL);
}

// Gets the closest world object to the specified ray
WorldObject* World::getClosestIntersect(Line* ray, float max_dist, float* coefficient, Vector3* normal, WorldObject* exclude)
{
    unsigned int object_iterator;
    float distance_limit;
    WorldObject* result;

    // Initially assume no intersection
    result = NULL;
    distance_limit = max_dist;
    // Check each sphere for intersection
    for (object_iterator = 0; object_iterator < this->numSpheres(); object_iterator++) {
        // Check if this is the object we are ignoring
        if ((WorldObject*) this->getSphere(object_iterator) == exclude) {
            continue;
        }
        // Check if and where this ray intersects
        if (this->getSphere(object_iterator)->intersects(ray, distance_limit, coefficient, normal)) {
            if (*coefficient < distance_limit) {
                result = (WorldObject*) this->getSphere(object_iterator);
                distance_limit = *coefficient;
            }
        }
    }  
    // Check each triangle for intersection
    for (object_iterator = 0; object_iterator < this->numTriangles(); object_iterator++) {
        // Check if this is the object we are ignoring
        if ((WorldObject*) this->getTriangle(object_iterator) == exclude) {
            continue;
        }
        // Check if and where the ray intersects
        if (this->getTriangle(object_iterator)->intersects(ray, distance_limit, coefficient, normal)) {
            if (*coefficient <= distance_limit) {
                distance_limit = *coefficient;
                result = (WorldObject*) this->getTriangle(object_iterator);
            }
        }
    }
    // Check each plane for intersection
    for (object_iterator = 0; object_iterator < this->numPlanes(); object_iterator++) {
        // Check if this is the object we are ignoring
        if ((WorldObject*) this->getPlane(object_iterator) == exclude) {
            continue;
        }
        // Check if and where ray intersects
        if (this->getPlane(object_iterator)->intersects(ray, distance_limit, coefficient, normal)) {
            if (*coefficient <= distance_limit) {
                distance_limit = *coefficient;
                result = (WorldObject*) this->getPlane(object_iterator);
            }
        }
    }
    return result;
}

// Checks if the specified ray intersects any obects other than the specified
int World::checkIntesect(Line* ray, float max_dist, WorldObject* exclude) {
    unsigned int object_iterator;
    float coefficient;
    Vector3 normal;

    // Check each sphere for intersection
    for (object_iterator = 0; object_iterator < this->numSpheres(); object_iterator++) {
        // Check if this is the object we are ignoring
        if ((WorldObject*) this->getSphere(object_iterator) == exclude) {
            continue;
        }
        // Check if and where this ray intersects
        if (this->getSphere(object_iterator)->intersects(ray, max_dist, &coefficient, &normal)) {
            if (coefficient <= max_dist) {
                return 1;
            }
        }
    }  
    // Check each triangle for intersection
    for (object_iterator = 0; object_iterator < this->numTriangles(); object_iterator++) {
        // Check if this is the object we are ignoring
        if ((WorldObject*) this->getTriangle(object_iterator) == exclude) {
            continue;
        }
        // Check if and where the ray intersects
        if (this->getTriangle(object_iterator)->intersects(ray, max_dist, &coefficient, &normal)) {
            if (coefficient <= max_dist) {
                return 1;
            }
        }
    }
    // Check each plane for intersection
    for (object_iterator = 0; object_iterator < this->numPlanes(); object_iterator++) {
        // Check if this is the object we are ignoring
        if ((WorldObject*) this->getPlane(object_iterator) == exclude) {
            continue;
        }
        // Check if and where this ray intersects
        if (this->getPlane(object_iterator)->intersects(ray, max_dist, &coefficient, &normal)) {
            if (coefficient <= max_dist) {
                return 1;
            }
        }
    }
    return 0;    
}




