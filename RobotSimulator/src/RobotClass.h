/**
 * \author Group 6
 *
 * \file  RobotClass.h
 * \brief The representation of robot within the simulation
 *
 */

#ifndef ROBOTCLASS_H
#define ROBOTCLASS_H

#include "PhysicalObjectClass.h"
#include "LightSensor.h"
#include "TargetSensor.h"
#include "TouchSensor.h"
#include "Wheel.h"

#include <cmath>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <stdlib.h>

/** RobotClass.  This provides means to store and alter robot state. */
class RobotClass : public PhysicalObjectClass {
  public:

    /**
     * RobotClass constructor.
     */
    RobotClass();

    /**
     * ~RobotClass destructor.
     */
    ~RobotClass();

    /**
     * getOrientation get the orientation, in degrees, from the horizontal counterclockwise.
     * @return degrees
     */
    int getOrientation();

    /**
    * getWheelMovement get distance moved based on wheels
    * @return distance
    */
    int getWheelMovement();

    /**
    * getWheelOrientation get orientation from two wheels (degrees)
    * @return orientation based on wheel speed
    */
    int getWheelOrientation();

    /**
    * move move the robot.
    * @param elapsedTime time elapsed since last movement
    */
    void move(double elapsedTime);


//   /**
//    * getSpeed get speed in pps.
//    * @return speed
//    */
//    int getSpeed();
//
//   /**
//    * setSpeed set the speed.a
//    * @param pps pixels per second.
//    */
//    void setSpeed( int pps );

    /**
    * getDistanceToMove get the distance to move on next tick based on the wheel speed
    */
    int getDistanceToMove();


    /**
     * setOrientation set the orientation.
     * @param degrees degrees from horizontal, counterclockwise.
     */
    void setOrientation( int degrees );

    /**
     * detectWall detect if object has hit a wall.
     */
    bool detectWall(SizeStruct windowSize);

    /**
     * detectObstacle detect an obstacle.
     * @param robot a robot obstacle.
     * @return bool whether or not a wall is detected
     */
    bool detectObstacle( PhysicalObjectClass *obstacle );

    void rotate( int degrees ); // positive = turn left, negative = turn right

    /**
     * translateX translate robot a certain distance along X axis.
     * @param distance distance the robot is to be translated on X axis.
     * @return bool whether or not a collision has occurred
     */
    int translateX( int distance ); // distance moved, in pixels

    /**
     * translateY translate robot a certain distance along Y axis.
     * @param distance distance the robot is to be translated on Y axis.
     */
    int translateY( int distance );

    /**
     * updatePosition
     * @param tbf time between frames
     */
    void updatePosition( double tbf ); // time between frames

    /**
     * pointTo point robot to a target.
     * @param target the target to orient toward.
     * @return new orientation
     */
    void pointTo( PhysicalObjectClass *target ); // orientate towards target

    /**
    * checkSensors check robot sensors, change state (orientation, etc.)
    * @param elapsedTime time elapsed (base speed change, etc. on this or something)
    */
    void checkSensors (double elapsedTime);

protected:
  int orientation/*, speed, distanceToMove*/;
  Wheel leftWheel, rightWheel;
  TargetSensor targetSensor;
  TouchSensor touchSensor;
};
#endif
