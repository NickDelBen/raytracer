
#include "color.hpp"

Color::Color (float red, float green, float blue)
{
    this->red = red;
    this->green = green;
    this->blue = blue;
}

// Reads a color from the specified stream
Color::Color(std::istream* stream)
{
    // Read colors from stream and store
    *stream >> this->red >> this->green >> this->blue;
}

// Sets the color channels to be at most the specified values
void Color::setMax(float new_max)
{
    this->setRed(std::fmin(new_max, this->getRed()));
    this->setGreen(std::fmin(new_max, this->getGreen()));
    this->setBlue(std::fmin(new_max, this->getBlue()));
}

// Sets the color channels to be at least the specified values
void Color::setMin(float new_min)
{
    this->setRed(std::fmax(new_min, this->getRed()));
    this->setGreen(std::fmax(new_min, this->getGreen()));
    this->setBlue(std::fmax(new_min, this->getBlue()));
}

// Sets the collor channels to be between the specified values
void Color::setRange(float new_min, float new_max)
{
    this->setMin(new_min);
    this->setMax(new_max);
}

// Creates and returns a new color, multiplied by the specified coefficnent
Color Color::scaledColor(float coefficient)
{
    Color result;

    result = Color(this->red * coefficient, this->green * coefficient, this->blue * coefficient);
    return result;
}

// Multiplies two colors together
Color Color::multiplyColor(Color* other)
{
    return Color(this->red * other->red, this->green * other->green, this->blue * other->blue);
}

// Checks iof all channels are greater than the specified value
int Color::checkGreater(float value)
{
    if (this->getRed() > value && this->getGreen() > value && this->getBlue() > value) {
        return 1;
    }
    return 0;
}

// Override the equals operator
Color& Color::operator=(const Color &other)
{
    this->red = other.red;
    this->green = other.green;
    this->blue = other.blue;
    return *this;
}

// Override the addition operator
Color Color::operator+(const Color &other)
{
    return Color(this->red + other.red, this->green + other.green, this->blue + other.blue);
}

// Gets the red componant of the color
float Color::getRed()
{
    return this->red;
}

// Gets the green componant of the color
float Color::getGreen()
{
    return this->green;
}

// Gets the blue componant of the color
float Color::getBlue()
{
    return this->blue;
}

// Sets the red componant to the specififed value
void Color::setRed(float new_red)
{
    this->red = new_red;
}

// Sets the green componant to the specififed value
void Color::setGreen(float new_green)
{
    this->green = new_green;
}

// Sets the blue componant to the specififed value
void Color::setBlue(float new_blue)
{
    this->blue = new_blue;
}

// Override the stream operator
std::ostream& operator<< (std::ostream& stream, Color& color)
{
    return stream << "(" << color.getRed() << ", " << color.getGreen() << ", " << color.getBlue() << ")";
}
