/**
 * @file ColorStruct.h
 * A header file contains various a color struct to be used in the robot simulation.
 *
 * @author Khoi Pham
 * @see ColorStruct.cpp
 */


#ifndef COLORSTRUCT_H
#define COLORSTRUCT_H

#include <string>

/**
 * Contains information about color.
 * Colors can be represented both in RGB values or hexadecimal string. The string
 * has 6 characters, e.g. FFFFFF for color white.
 * The string can be in upper or lower case. The RGB values must be in range of
 * [0, 255].
 */
struct ColorStruct {
    int rValue; /**< Red component of the color. */
    int gValue; /**< Green component of the color. */
    int bValue; /**< Blue component of the color. */
    std::string hexStr; /**< Hexadecimal representation. */

    /**
     * A default constructor.
     * Default color is black.
     */
    ColorStruct() : rValue( 0 ), gValue( 0 ), bValue( 0 ), hexStr( "000000" ) {}

    /**
     * A constructor using RGB values.
     * The hexadecimal string will NOT be set automatically using this constructor.
     * User will have to set it manually if needed by calling setHex(). If one of
     * the RBG values is out of range, set to default color black (0, 0, 0).
     *
     * @param r red component
     * @param g green component
     * @param b blue component
     * @see #setHex()
     */
    ColorStruct( int r, int g, int b );

    /**
     * A constructor using the hexadecimal representation.
     * The color's RGB values will be set automatically using this constructor.
     *
     * @param hex hexadecimal string (e.g. FFFFFF)
     * @see #setRGB()
     */
    ColorStruct( std::string hex );

    /**
     * Using hexadecimal string to set RGB values accordingly.
     * The hexadecimal string has to be in the right format, having 6 characters
     * (0-9 or A-F). For instance, FF0000 -> (255, 0, 0).
     * Unexpected results if the string is not in the right format.
     */
    void setRGB();

    /**
     * Using RGB values to set hexadecimal string accordingly.
     * The result string will have 6 characters (0-9 or A-F).
     * For instance, (255, 0, 0) -> FF0000.
     */
    void setHex();
};

#endif
