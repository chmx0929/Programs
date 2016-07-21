/**
 * @file BoundaryStruct.cpp
 * Implemetation of BoundaryStruct.
 *
 * @author Khoi Pham
 * @see BoundaryStruct.h
 */


#include "BoundaryStruct.h"

BoundaryStruct::BoundaryStruct( SizeStruct &size ) {
    construct( size );
}

BoundaryStruct::BoundaryStruct( SizeStruct &size, int margin ) {
    construct( size );

    // If margin exceeds a reasonable amount, set it to zero.
    if ( ( margin > outerBoundarySize.width / 2 ) ||
        ( margin > outerBoundarySize.height / 2 )  ) {
        margin = 0;
    }

    // Adjust the inner borders with the margin.
    top -= margin;
    bottom += margin;
    left += margin;
    right -= margin;
}

BoundaryStruct::BoundaryStruct( SizeStruct &size, int tp, int bttm, int lft, int rght ) {
    construct( size );

    // If preset values are appropriate, set border values to new ones.
    if ( ( tp > bttm ) && ( rght > lft ) ) {
        top = tp;
        bottom = bttm;
        left = lft;
        right = rght;
    }
    
    // Otherwise, keep the inner boundary overlapping the outer one.
}

void BoundaryStruct::setMargin( int margin ) {
    // not implemented yet
}

/* This private helper function is used to simulate delegating constructors.
   Calling this is the same as calling BoundaryStruct(SizeStruct) constructor. */
void BoundaryStruct::construct( SizeStruct &size ) {
    outerBoundarySize = size;

    // If outer boundary's width or height is negative, set both to zero.
    if ( ( outerBoundarySize.width < 0 ) || ( outerBoundarySize.height < 0 ) ) {
        outerBoundarySize.width = outerBoundarySize.height = 0;
    }

    // Inner boundary overlaps outer boundary.
    top = outerBoundarySize.height;
    bottom = 0;
    left = 0;
    right = outerBoundarySize.width;
}
