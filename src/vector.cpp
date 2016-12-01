
#include "vector.hpp"

// Creates and returns a new instance of a Vector
Vector3::Vector3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

// Reads a vector from the specified stream
Vector3::Vector3(std::istream* stream)
{
    *stream >> this->x >> this->y >> this->z;
}

// Calculates the dot product between this vector and a specified vector
float Vector3::dotProduct(Vector3 * other)
{
    return this->x * other->x + this->y * other-> y + this->z * other->z;
}

 // Calcualtes the cross product between this vector and the specified vector
Vector3 Vector3::crossProduct(Vector3* other)
{
    float tx;
    float ty;
    float tz;

    tx = this->y * other->z - this->z * other->y;
    ty = this->z * other->x - this->x * other->z;
    tz = this->x * other->y - this->y * other->x;
    return Vector3(tx, ty, tz);
}

// Overrides the multiply to allow for scaling a vector
Vector3 Vector3::scale(float scaler)
{
    Vector3 result;

    result = *this;
    result.x *= scaler;
    result.y *= scaler;
    result.z *= scaler;
    return result;
}

// Gets the length of the vector
float Vector3::getLength()
{
    float result;
    result = this->x*this->x + this->y*this->y + this->z*this->z;
    return sqrtf(result);
}

// Normalize a vector to be length of 1
void Vector3::normalize()
{
    float length;

    length = this->getLength();
    this->x = this->x / length;
    this->y = this->y / length;
    this->z = this->z / length;
}

// Returns the x-componant of the vector
float Vector3::getX()
{
    return this->x;
}

// Returns the y-componant of the vector
float Vector3::getY()
{
    return this->y;
}

// Returns the z-componant of the vector
float Vector3::getZ()
{
    return this->z;
}

// Sets the y-componant to the specified value
void Vector3::setY(float new_y)
{
    this->y = new_y;
}

// Override the equals operator
Vector3& Vector3::operator=(const Vector3 &other)
{
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    return *this;
}

// Subtract two vectors and return a new result vector
Vector3 Vector3::operator-(const Vector3 &other)
{
    return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);;
}

// Add two vectors and return a new result vector
Vector3 Vector3::operator+(const Vector3 &other)
{
    return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
}

// Override the stream operator
std::ostream& operator<< (std::ostream& stream, Vector3& vect)
{
    return stream << "(" << vect.getX() << ", " << vect.getY() << ", " << vect.getZ() << ")";
}

