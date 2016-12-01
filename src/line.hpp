// Describes a line

#ifndef _h_line
#define _h_line

#include <cmath>
#include "vector.hpp"

// Defines a line in 3 space
class Line
{
public:
    /***********************
    * Creates and returns a new line
    * @param direction Direction of the line
    * @param position  Position of the line
    ***********************/
    Line(Vector3& position, Vector3& direction);
    Line(){}
    ~Line(){}

    /***********************
    * Creates a new line from two points
    * @param p1 The first point
    * @param p2 The second point
    ***********************/
    void fromPoints(Vector3* p1, Vector3* p2);

    /***********************
    * Sets the direction of this line to the specified vector
    * Normalizes the input vector in all cases
    * @param direction Direction to set this direction to
    ***********************/
    void setDirection(Vector3* direction);

    /***********************
    * Calculate the endpoint of the vector based on the specified scaler
    * @param scaler Amount to scale the distance by
    * @return Vector representing the endpoint of the line
    ***********************/
    Vector3 endpoint(float scaler);

    /***********************
    * Gets the direction of this ray
    * Return direction vector for this ray
    ***********************/
    Vector3* getDirection();

    /***********************
    * Changes the position to the specified value
    * @param position New position for this line
    ***********************/
    void setPosition(Vector3* position);

    /***********************
    * Gets the start position of the line
    * @return pointer to start position of line
    ***********************/
    Vector3* getPosition();

private:
    /* Direction this vector is pointing */
    Vector3 direction;
    /* Position of this line */
    Vector3 position;
};

#endif