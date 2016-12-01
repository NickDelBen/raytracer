// Describes a vector

#ifndef _h_vector
#define _h_vector

#include <cmath>
#include <iostream>

// Defines a vector in 3 space
class Vector3 
{
public:
    /***********************
    * Creates and returns a new instance of a Vector
    * @param x x-componant of vector position 
    * @param y y-componant of vector position 
    * @param z x-componant of vector position
    ***********************/
    Vector3(float x, float y, float z);

    /***********************
    * Reads a vector from the specified stream
    * format: <x> <y> <z>
    * @param stream Stream to read vector from
    ***********************/
    Vector3(std::istream* stream);

    Vector3(){};
    ~Vector3(){};

    /***********************
    * Calculates the dot product between this vector and a specified vector
    * @param other Vector to calculate the dot product with
    * @return a new vector storing the result of the operation
    ***********************/
    float dotProduct(Vector3* other);

    /***********************
    * Calcualtes the cross product between this vector and the specified vector
    * @param other Vector to calculate the dot product with
    * @return a new vector storing the result of the operation
    ***********************/
    Vector3 crossProduct(Vector3* other);

    /***********************
    * Overrides the multiply to allow for scaling a vector
    * @param scaler Amount to scale the vector by
    * @return result of scaling the vector by the specified scaler
    ***********************/
    Vector3 scale(float scaler);

    /***********************
    * Gets the length of the vector
    * @return LEngth of the vector
    ***********************/
    float getLength();

    /***********************
    * Normalize a vector to be length of 1
    ***********************/
    void normalize();

    /***********************
    * Returns the x-componant of the vector
    * @return X-componant of vector
    ***********************/
    float getX();

    /***********************
    * Returns the y-componant of the vector
    * @return Y-componant of vector
    ***********************/
    float getY();

    /***********************
    * Returns the z-componant of the vector
    * @return Z-componant of vector
    ***********************/
    float getZ();

    /***********************
    * Sets the y-componant to the specified value
    * @param new_y Value for this vector y
    ***********************/
    void setY(float new_y);

    /***********************
    * Override the equals operator
    * @param other Right hand side of equals operator
    ***********************/
    Vector3& operator=(const Vector3 &other);

    /***********************
    * Subtract two vectors and return a new result vector
    * @param other Vector to subtract from this vector
    * @return a new vector that is the result of the operation
    ***********************/
    Vector3 operator-(const Vector3 &other);

    /***********************
    * Add two vectors and return a new result vector
    * @param other Vector to add to this vector
    * @return a new vector that is the result of this operation
    ***********************/
    Vector3 operator+(const Vector3 &other);

    /***********************
    * Override the stream operator
    ***********************/
    friend std::ostream& operator<< (std::ostream& stream, Vector3& vect);

private:
    /* The x-componant of the vector */
    float x;
    /* The y-componant of the vector */
    float y;
    /* The z-componant of the vector */
    float z;
};

#endif