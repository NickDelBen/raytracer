// Descrines a color

#ifndef _h_color
#define _h_color

#include <iostream>
#include <cmath>

class Color
{
public:
    /***********************
    * Creates and returns a new color
    * @param red   Amount of red in the color
    * @param blue  Amount of blue in the color
    * @param green Amount of green in the color
    ***********************/
    Color(float red, float green, float blue);

    /***********************
    * Reads a color from the specified stream
    * format: <red> <green> <blue>
    * @param stream Stream to read color from
    ***********************/
    Color(std::istream* stream);

    Color(){}
    ~Color(){}

    /***********************
    * Creates and returns a new color, multiplied by the specified coefficnent
    * @param coefficient Coefficient to scale the color by
    * @return New Color resulting from scaling this color by the specified value
    ***********************/
    Color scaledColor(float coefficient);

    /***********************
    * Multiplies two colors together
    * @param other COlor to multiply this color with
    * @return New color resulting from multipling this color by a specified color
    ***********************/
    Color multiplyColor(Color* other);

    /***********************
    * Checks iof all channels are greater than the specified value
    * @param value Amount to check all channel greater than
    * @return 1 if all greater otherwise 0
    ***********************/
    int checkGreater(float value);

    /***********************
    * Override the equals operator
    * @param other Right hand side of equals operator
    ***********************/
    Color& operator=(const Color &other);

    /***********************
    * Override the addition operator
    * @param other Right hand side of addition operator
    ***********************/
    Color operator+(const Color &other);

    /***********************
    * Gets the red componant of the color
    * @return Red componant of color
    ***********************/
    float getRed();
        
    /***********************
    * Gets the green componant of the color
    * @return Green componant of color
    ***********************/
    float getGreen();

    /***********************
    * Gets the blue componant of the color
    * @return Blue componant of color
    ***********************/
    float getBlue();

    /***********************
    * Sets the red componant to the specififed value
    * @param new_red New value for red componant of the color
    ***********************/
    void setRed(float new_red);

    /***********************
    * Sets the green componant to the specififed value
    * @param new_green New value for green componant of the color
    ***********************/
    void setGreen(float new_green);

    /***********************
    * Sets the blue componant to the specififed value
    * @param new_blue New value for blue componant of the color
    ***********************/
    void setBlue(float new_blue);

    /***********************
    * Sets the color channels to be at most the specified values
    * @param new_max Maxamum value for color channels
    ***********************/
    void setMax(float new_max);

    /***********************
    * Sets the color channels to be at least the specified values
    * @param new_min Minimum value for color channels
    ***********************/
    void setMin(float new_min);

    /***********************
    * Sets the collor channels to be between the specified values
    * @param new_max Maxamum value for color channels
    * @param new_min Minimum value for color channels
    ***********************/
    void setRange(float new_min, float new_max);

    /***********************
    * Override the stream operator
    ***********************/
    friend std::ostream& operator<< (std::ostream& stream, Color& color);

private:
    /* The red amount in the color */
    float red;
    /* The green amount in the color */
    float green;
    /* The blue color in the color */
    float blue;
};

#endif