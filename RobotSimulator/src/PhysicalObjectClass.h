#ifndef PHYSICALOBJECTCLASS_H
#define PHYSICALOBJECTCLASS_H

#include "SizeStruct.h"
#include "ColorStruct.h"
#include <cmath>
#include <stdlib.h>
#define PI 3.14159265

/**
* DOCUMENTATION GOES HERE!
*/
enum type { // "type" is so general, let's come up with a more specific name
  ROBOT, /**< DOCUMENTATION GOES HERE! */
  OBSTACLE, /**< DOCUMENTATION GOES HERE! */
  TARGET, /**< DOCUMENTATION GOES HERE! */
  LIGHT
};

/**
* The representation of a physical object within the simulation.
*/
class PhysicalObjectClass {
  public:
    /**
    * Default Constructor.
    */
    PhysicalObjectClass() : position( 0 ) { deleted = false; speed = 25; }


    /**
    * Destructor. (I wonder if we need to have documentation for destructors)
    */
    ~PhysicalObjectClass() {speed = 2;} ; // IMPLEMENT

    /**
    * Position getter.
    * @return position
    */
    int getPosition() { return position; }

    /** foo I have no idea.
    */
    void foo();

    virtual bool isMovable();

    /**
    * X-coordinate getter.
    * @return x-coordinate
    */
    int getXPosition() { return xPosition; }

    /**
    * Y-coordinate getter.
    * @return y-coordinate
    */
    int getYPosition() { return yPosition; }

    /**
    * Radius getter.
    * @return radius
    */
    int getRadius() { return radius; }

    /**
    * XY-coordinate setter.
    * @param x x-coordinate
    * @param y y-coordinate
    */
    void setPosition( int x, int y ) { xPosition = x; yPosition = y; }

    /**
    * Radius setter. (assuming object is a circle)
    * @param r radius
    */
    void setRadius( int r ) { radius = r; }

    /**
    * getType get the physical object type.
    */
    type getType() { return Type; }

    /**
    * detectObstacle detect an obstacle
    * @param obstacle obstacle to detect
    */
    virtual bool detectObstacle( PhysicalObjectClass *obstacle );

    /**
    * detectWall detect a wall, virtual method
    * @param windowSize size of window as a SizeStruct
    */
    virtual bool detectWall(SizeStruct windowSize);

    /**
    * move move the object.
    * @param elapsedTime the time elapsed, to be used in conjunction with speed
    */
    virtual void move(double elapsedTime);

    /**
    * setDeleted set the deleted member to true or false, so it can be cleaned up in another loop.
    * @param val boolean val to put in
    */
    void setDeleted(bool val);

    /**
    * getDeleted return the deleted member.
    * @return whether or not it was deleted, and should be removed
    */
    bool getDeleted();

    /**
    * setColor set color of obj
    * @param r red 0-255
    * @param g green 0-255
    * @param b blue 0-255
    */
    void setColor( int r, int g, int b ) {
      // todo: don't hard code, use the color struct methods, but not in iter 2
      color.rValue = r; color.gValue = g; color.bValue = b;
    }

    /**
    * pointTo point to a target
    * @param target target to point to
    */
    virtual void pointTo( PhysicalObjectClass *target ); // orientate towards target

    /**
    * setOrientation set the orientation.
    * @param degrees degrees from horizontal, counterclockwise.
    */
    virtual void setOrientation( int degrees );

    /**
    * getOrientation get the orientation, in degrees, from the horizontal counterclockwise.
    * @return degrees
    */
    virtual int getOrientation();

    /**
    * rotate rotate robot.
    * @param degrees degrees to rotate
    */
    virtual void rotate( int degrees ); // positive = turn left, negative = turn right

  protected:
    type Type; // in type
    int xPosition; // in pixels
    int yPosition; // in pixels
    int radius; // in pixels
    int position;
    int orientation;
    double speed;
    bool deleted; // whether or not the obj should be deleted on next iteration
    /* I created SizeStruct and ColorStruct. Consider using it? */
    SizeStruct size; // use the radius within the struct
    ColorStruct color; // use rValue, gValue, bValue
};

#endif
