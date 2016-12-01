
#include "plane.hpp"

Plane::Plane(Vector3* normal, Vector3* point)
{
    this->normal = *normal;
    this->point = *point;
    this->material = NULL;
}

// Creates and returns a new plane from the specified stream
Plane::Plane(Material* mat, std::istream* stream)
{
    this->material = mat;
    this->normal = Vector3(stream);
    this->point = Vector3(stream);
}

// Checks if the specified line intersects with the plane
int Plane::intersects(Line* ray, float max_dist, float* coefficient, Vector3* normal)
{
    // Calculate the dot result of a plane intersection
    float dot_result = ray->getDirection()->dotProduct(&(this->normal));
    // If we are dividing by zero there is no intersection
    if (dot_result > -PLANE_ROUNDING_OFFSET && dot_result < PLANE_ROUNDING_OFFSET) {
        return 0;
    }
    // Calculate the distance along the line that the intersection occurs
    Vector3 point_difference = this->point - *(ray->getPosition());
    float intersect_distance = this->normal.dotProduct(&point_difference);
    // Check to ensure the intersect happens within our acceptable distance
    if (intersect_distance > max_dist || intersect_distance < -max_dist) {
        return 0;
    }
    // Store the resulting distance
    *coefficient = intersect_distance;
    // The normal is simply the normal to the plane
    *normal = this->normal;
    return 1;
}

// Override stream operator
std::ostream& operator<< (std::ostream& stream, Plane& plane)
{
    return stream << "Normal: " << plane.normal << " Point: " << plane.point;
}


// Sets the material to the specified material
void Plane::setMaterial(Material* mat)
{
    this->material = mat;
}

// Gets the material this plane is made of
Material* Plane::getMaterial()
{
    return this->material;
}