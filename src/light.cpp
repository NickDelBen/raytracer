
#include "light.hpp"

// Creates and returns a new light
Light::Light(Color intensity, Vector3 position)
{
    this->intensity = intensity;
    this->position = position;
}


// Creates a light by reading the parameters from the specified stream
Light::Light(std::istream* stream)
{
    // Read position from stream
    this->position = Vector3(stream);
    // Read intensioty from stream
    this->intensity = Color(stream);
}

// Gets the position of the light
Vector3* Light::getPosition()
{
    return &(this->position);
}

// Gets the intensity of the light
Color* Light::getIntensity()
{
    return &(this->intensity);
}

// Override stream operator
std::ostream& operator<< (std::ostream& stream, Light& light)
{
    return stream << "Position: " << *(light.getPosition()) << " Intensity: " << *(light.getIntensity());
}