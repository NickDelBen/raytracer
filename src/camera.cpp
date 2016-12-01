
#include "camera.hpp"

// Creates and returns a new camera
Camera::Camera(Vector3 eye, Vector3 top_left, Vector3 bottom_right)
{
    this->position = eye;
    this->top_left = top_left;
    this->bottom_right = bottom_right;
}

// Creates a new camera from the specified stream
Camera::Camera(std::istream* stream)
{
    // Read position from stream
    this->position = Vector3(stream);
    // Read top left of imaging plane from stream
    this->top_left = Vector3(stream);
    // Read bottom right of imaging plane from stream
    this->bottom_right = Vector3(stream);
}

// Gets a ray for the specified location on the imaging plane
Line Camera::getRay(int x, int y)
{
    Line result;
    Vector3 point2;

    // Calculate the second point (where the ray intersects the plane)
    point2 = Vector3(this->bottom_right.getX() + x, this->bottom_right.getY() + y, 0.0);
    result.fromPoints(&(this->position), &point2);
    return result;
} 

// Gets the height of the imaging plane
int Camera::planeHeight()
{
    return this->top_left.getY() - this->bottom_right.getY();
}

// Gets the width of the imaging plane
int Camera::planeWidth()
{
    return this->top_left.getX() - this->bottom_right.getX();
}

// Gets the position of the camera
Vector3* Camera::getPosition()
{
    return &(this->position);
}

// Gets the top left of the imaging plane
Vector3* Camera::getTopLeft()
{
    return &(this->top_left);
}

// Gets the bottom_right of the imaging plane
Vector3* Camera::getBottomRight()
{
    return &(this->bottom_right);
}

// Override the stream operator
std::ostream& operator<<(std::ostream& stream, Camera& cam)
{
    return stream << "Eye: " << *(cam.getPosition()) << " Imaging Top Left: " << *(cam.getTopLeft()) << " Imaging Bottom Right: " << *(cam.getBottomRight());
}
