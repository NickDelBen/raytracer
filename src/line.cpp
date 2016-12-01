
#include "line.hpp"

// Creates and returns a new line
Line::Line(Vector3& position, Vector3& direction)
{
    this->position = position;
    this->setDirection(&direction);
}

// Sets the direction of this line to the specified vector
void Line::setDirection(Vector3* direction)
{
    this->direction = *direction;
    this->direction.normalize();
}

// Changes the position to the specified value
void Line::setPosition(Vector3* position)
{
    this->position = *position;
}

// Gets the start position of the line
Vector3* Line::getPosition()
{
    return &(this->position);
}

// Creates a new line from two points
void Line::fromPoints(Vector3* p1, Vector3* p2)
{
    Vector3 result;
    this->position = *p1;
    result = Vector3(p2->getX()-p1->getX(), p2->getY()-p1->getY(), p2->getZ()-p1->getZ());
    this->setDirection(&result);
}

// Calculate the endpoint of the vector based on the specified scaler
Vector3 Line::endpoint(float scaler)
{
    Vector3 result;

    //Scale the direction
    result = this->direction.scale(scaler);
    result = result + this->position;
    return result;
}

// Gets the direction of this ray
Vector3* Line::getDirection()
{
    return &(this->direction);
}
