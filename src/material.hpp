// Describes a material

#ifndef _h_material
#define _h_material

#include <iostream>

#include "color.hpp"

// Defines a material
class Material
{
public:
    /***********************
    * Creates a new light by breading values from the specified stream
    * format: <power> <reflectivity> <material color> <diffuse reflection> <specular reflection> <ambient reflection>
    * @param stream Stream to read data from
    ***********************/
    Material(std::istream* stream);

    Material();
    ~Material(){}

    /***********************
    * Gets the diffuse color of the material
    * @return Diffuse color of the material
    ***********************/
    Color* getDiffuse();

    /***********************
    * Gets the specular color of the material
    * @return Specular color of the material
    ***********************/
    Color* getSpecular();

    /***********************
    * Gets the ambient color of the material
    * @return Ambient color for the material
    ***********************/
    Color* getAmbient();

    /***********************
    * Sets the ambient color to the specified value
    * @param new_ambient Ambient value for the material
    ***********************/
    void setAmbient(Color* new_ambient);

    /***********************
    * Sets the diffuse color to the specified value
    * @param new_diffuse Diffuse value for this material
    ***********************/
    void setDiffuse(Color* new_diffuse);

    /***********************
    * Sets the specular color to the specified value
    * @param new_specular Specular value for this material
    ***********************/
    void setSpecular(Color* new_specular);

    /***********************
    * Gets the color fo the material
    * @return Color of the material
    ***********************/
    Color* getColor();

    /***********************
    * Gets the reflectivity of the material
    * @return Reflectivity of the material
    ***********************/
    float getReflectivity();

    /***********************
    * Sets the color fo the material to the specified value
    * @param new_color Color for this material
    ***********************/
    void setColor(Color* new_color);

    /***********************
    * Gets the specular power of the material
    * @return Material specular power
    ***********************/
    float getPower();

    /***********************
    * Override the stream operator
    ***********************/
    friend std::ostream& operator<< (std::ostream& stream, Material& material);
    
private:
    /* Reflectivity coefficient */
    float reflectivity;
    /* Specular power */
    float power;
    /* The color of the material */
    Color color;
    /* The color of the diffuse */
    Color diffuse;
    /* The specular color */
    Color specular;
    /* The color of the ambient */
    Color ambient;
};

#endif