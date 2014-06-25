#include "color.h"

color::color() : red(255), blue(255), green(255)
{
}

color::color(int red, int green, int blue)
{
    this->red = red;
    this->green = green;
    this->blue = blue;
}

color::color(int idx)
{
    switch (idx%6)
    {
    case 0: red = 255; blue = 0; green = 0; break;
    case 1: red = 0; blue = 255; green = 0; break;
    case 2: red = 0; blue = 0; green = 255; break;
    case 3: red = 255; blue = 255; green = 0; break;
    case 4: red = 0; blue = 255; green = 255; break;
    case 5: red = 255; blue = 255; green = 255; break;
    default: red = 255; blue = 255; green = 255; break;
    }
}
