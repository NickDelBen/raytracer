// Describes a light

#ifndef _h_light
#define _h_light

#include <iostream>

#include "vector.hpp"
#include "color.hpp"

// Defines a light in 3 space
class Light
{
public:
    /***********************
    * Creates and returns a new light
    * @param intensity color of the light
    * @param position  location of the light
    ***********************/
    Light(Color intensity, Vector3 position);
    
    /***********************
    * Creates a light by reading the parameters from the specified stream
    * Format <position x> <position y> <position z> <intensity red> <intensity green> <intensity blue>
    * @param stream Stream to read details from
    ***********************/
    Light(std::istream* stream);
    Light(){}
    ~Light(){}

    /**********************
    * Gets the position of the light
    * @return Pisition of the light
    **********************/
    Vector3* getPosition();

    /**********************
    * Gets the intensity of the light
    * @return Lights intensity
    **********************/
    Color* getIntensity();

    /***********************
    * Override the stream operator
    ***********************/
    friend std::ostream& operator<< (std::ostream& stream, Light& light);

private:
    /* The position of the light */
    Vector3 position;
    /* The intensity of the light */
    Color intensity;
};

#endif