
#include "sphere.hpp"

// Creates and returns a new sphere
Sphere::Sphere(Vector3* position, float radius, Material* material)
{
    this->position = *position;
    this->radius = radius;
    this->material = material;
}

// Creates a sphere from the specified stream with the specified material
Sphere::Sphere(Material* mat, std::istream* stream)
{
    // Store the material
    this->material = mat;
    // Store the redius
    *stream >> this->radius;
    // Read the location
    this->position = Vector3(stream);
}

// Gets the position of the sphere
Vector3* Sphere::getPosition()
{
    return &(this->position);
}

// Gets the radius of the sphere
float Sphere::getRadius()
{
    return this->radius;
}

// Gets the material of this sphere
Material* Sphere::getMaterial()
{
    return this->material;
}

// Checks if this line intersects with the specified sphere
int Sphere::intersects(Line* ray, float max_dist, float* coefficient, Vector3* normal)
{
    float a;
    Vector3 dist;
    float b;
    float c;
    float descriminant;
    float sqdescriminant;
    float intercept1;
    float intercept2;

    // Calculate r.r
    a = ray->getDirection()->dotProduct(ray->getDirection());
    // Find distance from start of line and position of circle
    dist = *(ray->getPosition()) - *this->getPosition();
    // Find dot product
    b = 2 * ray->getDirection()->dotProduct(&dist);
    // Find the dot product
    c = dist.dotProduct(&dist) - (this->getRadius() * this->getRadius());
    // Calculate the descriminant
    descriminant = b*b - 4*a*c;
    // Return 0 if there is no intersection
    if (descriminant < 0.0) {
        return 0;
    }
    // Find the location of intercept
    sqdescriminant = sqrtf(descriminant);
    intercept1 = (-b - sqdescriminant)/2.0;
    intercept2 = (-b + sqdescriminant)/2.0;
    // Result is the closest intercept to the orgin of the ray
    if (intercept1 > intercept2) {
        intercept1 = intercept2;
    }
    // Check that the closest intersection point is inside the allowed intersection range
    if (intercept1 < MINIMUM_INTERCEPT_DISTANCE || intercept1 >= max_dist) {
        return 0;
    }
    // Store the interception point in the result location and return yes
    *coefficient = intercept1;
    // Calculate the intersection betwene ray and sphere
    Vector3 intersect = ray->endpoint(intercept1);
    // Calculate the normal to the sphere at the intersect point
    *normal = intersect - *(this->getPosition());
    normal->normalize();
    return 1;
}


// Override stream operator
std::ostream& operator<< (std::ostream& stream, Sphere& sphere)
{
    return stream << "Radius: " << sphere.getRadius() << " Position " << *(sphere.getPosition());
}