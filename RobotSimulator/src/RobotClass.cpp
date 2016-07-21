/**
 * \author Group 6
 *
 * \file  RobotClass.cpp
 * \brief The implemetation of the robot class
 *
 */

#include "RobotClass.h"

using namespace std;

#define PI 3.14159265

RobotClass::RobotClass():PhysicalObjectClass() {

    leftWheel = Wheel();
    rightWheel = Wheel();

    Type = ROBOT;

    xPosition = rand()%750+100;
    yPosition = rand()%550+100;

    leftWheel.setX(xPosition-radius/2);
    leftWheel.setY(yPosition);
    rightWheel.setX(yPosition);
    rightWheel.setY(xPosition+radius/2);

    radius = 30;
    orientation = 0;
    speed = 0;
}

RobotClass::~RobotClass() {
    // empty
}

int RobotClass::getOrientation() {
    return orientation;
}

int RobotClass::getWheelMovement() {
    double distanceBetweenWheels = sqrt( pow((leftWheel.getX() - rightWheel.getX()), 2.0) + pow((leftWheel.getY() - rightWheel.getY()), 2.0) );
    printf("distance between wheels: %f\n", distanceBetweenWheels);

    return (int) ( distanceBetweenWheels * leftWheel.getSpeed() / (rightWheel.getSpeed() - leftWheel.getSpeed()) );
}

int RobotClass::getWheelOrientation() {
    return (int) ( leftWheel.getSpeed() / ( (rightWheel.getSpeed() - leftWheel.getSpeed()) * 2 * PI) );
}

void RobotClass::move(double elapsedTime) {

    // adjust orientation, wheel speed, etc. based on sensors, this changes internal state of the robot
    checkSensors(elapsedTime);

    int movementDistance = this->getWheelMovement();

    printf("movementDistance: %f\n", movementDistance);

    /* change to use wheel movements */
    xPosition = (int) (xPosition + movementDistance * cos( orientation * 3.14 /180.0));
    yPosition = (int) (yPosition + movementDistance * sin( orientation * 3.14/180.0 ));
}

//int RobotClass::getSpeed() {
//    return speed;
//}

//void RobotClass::setSpeed( int pps ) {
//    if ( pps >= 0 ) {
//        speed = pps;
//    } else {
//        speed = 0;
//    }
//}

int RobotClass::getDistanceToMove() {
    return this->getWheelMovement();
}

void RobotClass::setOrientation( int degrees ) {
    orientation = degrees;
}

bool RobotClass::detectWall(SizeStruct windowSize) {
    // assumes that the position of the robot is its center,
    // so size of the robot needs to be taken into account for collisions
    int windowWidth = windowSize.width;
    int windowHeight = windowSize.height;

    printf("WINDOW SIZE:: W: %d H: %d\n", windowWidth, windowHeight);

    int robotMinPosX = this->getXPosition() - this->radius;
    int robotMaxPosX = this->getXPosition() + this->radius;
    int robotMinPosY = this->getYPosition() - this->radius;
    int robotMaxPosY = this->getYPosition() + this->radius;

    if ((robotMinPosX >= 0) &&
        (robotMaxPosX <= windowWidth) &&
        (robotMinPosY >= 0) &&
        (robotMaxPosY <= windowHeight)) {
        this->setColor(0, 255, 0);
        return false;
    }

    this->setColor(255, 0, 0);
    return true;
}

bool RobotClass::detectObstacle( PhysicalObjectClass * obs ) {
    // basically assumes that the obstacle is a circle, doesn't take size into account
    if ((this->getXPosition() >= (obs->getXPosition() - obs->getRadius())) &&
       (this->getXPosition() <= (obs->getXPosition() + obs->getRadius())) &&
       (this->getYPosition() >= (obs->getYPosition() - obs->getRadius())) &&
       (this->getYPosition() <= (obs->getYPosition() + obs->getRadius()))) {

        this->setColor(255, 0, 0);

        return true;
    }
    else {
        this->setColor(0, 255, 0);
        return false;
    }
}

void RobotClass::rotate( int degrees ) {
    // currently empty
    this->setOrientation((this->getOrientation() + degrees) % 360);
}

int RobotClass::translateX( int distance ) {
    return -1;
}

int RobotClass::translateY( int distance ) {
    return -1;
}

void RobotClass::updatePosition( double tbf ) {
    //this->translateX( (int) ((tbf * this->getSpeed( ) + 0.5 ) * cos(this->getOrientation()*PI/180)) );
    //this->translateY( (int) ((tbf * this->getSpeed( ) + 0.5) * sin(this->getOrientation()*PI/180)) );
    return;
}

void RobotClass::pointTo( PhysicalObjectClass *target ) {

    // lets create unit vectors out of the orientation of both of these

    double unitX1 = 1 * cos(this->getOrientation());
    double unitY1 = 1 * sin(this->getOrientation());

    double unitX2 = 1 * cos(target->getOrientation());
    double unitY2 = 1 * sin(target->getOrientation());

    // calculate angle between vectors

    double angle = acos( (unitX1 * unitX2 + unitY1 * unitY2) / (sqrt(unitX1 * unitX1 + unitY1 * unitY1) * sqrt(unitX2 * unitX2 + unitY1 * unitY2))) * 180/PI;

    // set orientation to new angle

    this->rotate((int) angle);
}

void RobotClass::checkSensors (double elapsedTime) {

}

