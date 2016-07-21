/**
 * @file BoundaryStruct.h
 * A header file contains various a boundary struct to be used in the robot simulation.
 *
 * @author Khoi Pham
 * @see BoundaryStruct.cpp
 */


#ifndef BOUNDARYSTRUCT_H
#define BOUNDARYSTRUCT_H

#include "SizeStruct.h"

/**
 * Contains information about a retangular boundary.
 * The boundary is in fact an innner boundary within an outer one. Because of that,
 * user has to provide information about the outer boundary, specifically its size.
 * User also has to make sure the outer boundary size's width and height are non-
 * negative values. <BR>
 * <BR>
 * The inner boundary is represented as four border values top, bottom, left, and
 * right. Assuming the outer boundary is a rectangle on a normal XY-coordinate
 * system with its bottom left corner at origin and its top right corner at location
 * (outerBoundarySize.width, outerBoundarySize.height), the inner boundary's top
 * border is the y-intercept of its top line, bottom is the y-intercept of its
 * bottom line, left is the x-intercept of its left line, and right is the x-intercept
 * of its right line. <BR>
 * <BR>
 * The border values can have negative values; however, then the inner boundary
 * may not be "inner" boundary anymore.
 *
 * @see SizeStruct
 */
struct BoundaryStruct {
    SizeStruct outerBoundarySize; /**< The outer boundary's size. */
    int top; /**< Top border. */
    int bottom; /**< Bottom border. */
    int left; /**< Left border. */
    int right; /**< Right border. */

    /**
     * A default constructor.
     * WARNING: This is an empty constructor for the sake of place-holding. <BR>
     * <BR>
     * Use this if absolutely needed! It is recommended to use others instead.
     */
    BoundaryStruct() {}

    /**
     * A normal constructor for setting up the boundary structure.
     * The outer boundary will be overlapped with the inner one. User has to make
     * sure the size parameter has non-negative values for both width and height.
     *
     * @param size the size of the outer boundary
     */
    BoundaryStruct( SizeStruct &size );

    /**
     * A constructor setting the inner borders thought a margin.
     * The inner boundary will be offset by the same amount of margin. Margin's
     * size should not exceed half the outer boundary's size, either width or height.
     * Negative values of margin will have unexpected behaviours. Use non-negative.
     *
     * @param size the size of the outer boundary
     * @param margin the preset margin
     */
    BoundaryStruct( SizeStruct &size, int margin );

    /**
     * A constructor setting the inner borders with preset values.
     * All preset values have to be appropriate, e.g. top has to be greater than
     * bottom. Allow negative values for the preset values of border.
     *
     * @param size the size of the outer boundary
     * @param top preset value for top border
     * @param bottom preset value for bottom border
     * @param left preset value for left border
     * @param right preset value for right border
     */
    BoundaryStruct( SizeStruct &size, int tp, int bttm, int lft, int rght );

    /**
     * Set border values according to a preset margin.
     * Similar to when construct a boundary struct through a margin.
     *
     * @param margin the preset margin
     * @see BoundaryStruct#BoundaryStruct(SizeStruct&, int)
     */
    void setMargin( int margin );

  private:
    void construct( SizeStruct &size );
};

#endif
