/**
 * @file SizeStruct.cpp
 * Implemetation of SizeStruct.
 *
 * @author Khoi Pham
 * @see SizeStruct.h
 */


#include "SizeStruct.h"

void SizeStruct::setRadius() {
    if ( ( width * height != 0 ) && ( width == height ) ) {
        radius = width / 2.0;
    } else {
        // do nothing, keep the radius value the same
    }
}
