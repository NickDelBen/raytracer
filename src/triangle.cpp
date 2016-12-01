
#include "triangle.hpp"

// Creates a triangle from the specified stream with the specified material
Triangle::Triangle(Material* mat, std::istream* stream)
{
    this->material = mat;
    this->p1 = Vector3(stream);
    this->p2 = Vector3(stream);
    this->p3 = Vector3(stream);
}

// Gets the material of this triangle
Material* Triangle::getMaterial()
{
    return this->material;
}

// Override stream operator
std::ostream& operator<< (std::ostream& stream, Triangle& triangle)
{
    return stream << "Point 1: " << triangle.p1 << " Point 2: " << triangle.p2 << " Point 3: " << triangle.p3;
}

// Checks if the specified line intersects with the triangle
int Triangle::intersects(Line* ray, float max_dist, float* coefficient, Vector3* normal)
{
    float determinant, inverse_determinant, result;

    // Find the edges of the triangle
    Vector3 edge1 = this->p2 - this->p1;
    Vector3 edge2 = this->p3 - this->p1;
    // Find cross product of edge and direction
    Vector3 s1 = ray->getDirection()->crossProduct(&edge2);
    // Calcualte the determinant
    determinant = edge1.dotProduct(&s1);
    if (determinant > -DISTANCE_OFFSET && determinant < DISTANCE_OFFSET) {
        return 0;
    }
    // Calculate the inverse determinant
    inverse_determinant = 1/determinant;
    // 
    Vector3 s2 = *(ray->getPosition()) - this->p1;
    float u = s2.dotProduct(&s1) * inverse_determinant;
    // If the u value is not in (0,1) there is no intersection
    if (u < 0 || u > 1) {
        return 0;
    }
    // 
    Vector3 s3 = s2.crossProduct(&edge1);
    //
    double v = ray->getDirection()->dotProduct(&s3) * inverse_determinant;
    // If the v value is not in (0,1) there is no intersection
    if (v < 0 || v > 1) {
        return 0;
    }
    result = edge2.dotProduct(&s3) * inverse_determinant;
    if (result < 0 || result > max_dist) {
        return 0;
    }
    *coefficient = result - DISTANCE_OFFSET;
    *normal = edge2.crossProduct(&edge1);
    normal->normalize();
    return 1;
}
