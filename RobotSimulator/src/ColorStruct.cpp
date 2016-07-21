/**
 * @file ColorStruct.cpp
 * Implemetation of ColorStruct.
 *
 * @author Khoi Pham
 * @see ColorStruct.h
 */


#include "ColorStruct.h"

ColorStruct::ColorStruct( int r, int g, int b )
    : rValue( 0 ), gValue( 0 ), bValue( 0 ) {

    // Set RBG values accordingly only if all of them are in range [0, 255].
    if ( ( 0 <= r && r <= 255 ) && ( 0 <= g && g <= 255 ) && ( 0 <= b && b <= 255 ) ) {
        rValue = r;
        gValue = g;
        bValue = b;
    }

    // Otherwise, default color (0, 0, 0).
}

ColorStruct::ColorStruct( std::string hex ) {
    hexStr = hex;
    setRGB();
}

void ColorStruct::setRGB() {
    // not implemented yet
}

void ColorStruct::setHex() {
    // not implemented yet
}
