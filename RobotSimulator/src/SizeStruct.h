/**
 * @file SizeStruct.h
 * A header file contains a size struct to be used in the robot simulation.
 *
 * @author Khoi Pham
 * @see SizeStruct.cpp
 */


#ifndef SIZESTRUCT_H
#define SIZESTRUCT_H

/**
 * Contains information about different types of size.
 * Can be either width and height of a rectangular object or radius of a circular
 * one. Note that all values are assumed to be non-negative. Value's negativity
 * checking should be handled by the using class or struct.
 */
struct SizeStruct {
    int width; /**< Width of a rectangle. */
    int height; /**< Height of a rectangle. */
    double radius; /**< Radius of a circle. */

    /**
     * A default constructor.
     * Set everything to zeros.
     */
    SizeStruct() : width( 0 ), height( 0 ), radius( 0 ) {}

    /**
     * A constructor for a rectangle's size.
     * Radius is set to zero.
     *
     * @param w rectangle's width
     * @param h rectangle's height
     */
    SizeStruct( int w, int h ) : width( w ), height( h ), radius( 0 ) {}

    /**
     * A constructor for a circle's size.
     * Width and height are set to circle's diameter. In this case, the circle
     * is enclosed inside an invisible square with the size of its diameter.
     *
     * @param r circle's radius
     */
    SizeStruct( double r ) : radius( r ) { width = height = r * 2; }

    /**
     * Using width and height to set radius accordingly.
     * Width and height must be equal and non-zero.
     * Radius will be half as much.
     */
    void setRadius();
};

#endif
