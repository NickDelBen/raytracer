
#include "material.hpp"

// Creates a new light by breading values from the specified stream
Material::Material(std::istream* stream)
{
    // Read the power from the stream
    *stream >> this->power;
    // read the reflectivity from the stream
    *stream >> this->reflectivity;
    // Read the color from the stream
    this->color = Color(stream);
    // Read diffuse color from stream
    this->diffuse = Color(stream);
    // Read specular color from stream
    this->specular = Color(stream);
    // Read ambient color from stream
    this->ambient = Color(stream);
}

Material::Material()
{
    this->color = Color(0.0, 0.0, 0.0);
    this->diffuse = Color(0.0, 0.0, 0.0);
    this->specular = Color(0.0, 0.0, 0.0);
    this->ambient = Color(0.0, 0.0, 0.0);
}

// Gets the reflectivity of the material
float Material::getReflectivity()
{
    return this->reflectivity;
}

// Gets the specular power of the material
float Material::getPower()
{
    return this->power;
}

// Gets the diffuse color of the material
Color* Material::getDiffuse()
{
    return &(this->diffuse);
}

// Gets the ambient color of the material
Color* Material::getAmbient()
{
    return &(this->ambient);
}

// Sets the ambient color to the specified value
void Material::setAmbient(Color* new_ambient)
{
    this->ambient = *new_ambient;
}


// Gets the specular color of the material
Color* Material::getSpecular()
{
    return &(this->specular);
}


// Sets the diffuse color to the specified value
void Material::setDiffuse(Color* new_diffuse)
{
    this->diffuse = *new_diffuse;
}

// Sets the specular color to the specified value
void Material::setSpecular(Color* new_specular)
{
    this->specular = *new_specular;
}

// Gets the color fo the material
Color* Material::getColor()
{
    return &(this->color);
}

// Sets the color fo the material to the specified value
void Material::setColor(Color* new_color)
{
    this->color = *new_color;
}

// Override the stream operator
std::ostream& operator<< (std::ostream& stream, Material& material)
{
    return stream << "Color: " << *(material.getColor()) << " Specular: " << *(material.getSpecular()) << " Diffuse: " << *(material.getDiffuse()) << " Ambient: " << *(material.getAmbient());
}



