/**
 * @file EnvironmentClass.cpp
 * Implemetation of EnvironmentClass.
 *
 * @author Group 6
 * @see EnvironmentClass.h
 */


#include "EnvironmentClass.h"

/* ***************************************************************************
 *
 * CONSTRUCTORS & DESTRUCTOR
 *
 * *************************************************************************** */

/**
* EnvironmentClass constructor
* @param width environment width.
* @param height environment height.
* @param margin environment margin.
*/
EnvironmentClass::EnvironmentClass( int width, int height, int margin ) {
    size = SizeStruct( width, height );
    borders = BoundaryStruct( size, margin );
}

/**
* EnvironmentClass constructor
* @param width environment width.
* @param height environment height.
* @param top top of boundary struct.
* @param bottom bottom of boundary struct.
* @param left left limit of boundary struct.
* @param right right limit of boundary struct.
*/
EnvironmentClass::EnvironmentClass( int width, int height,
    int top, int bottom, int left, int right ) {

    size = SizeStruct( width, height );
    borders = BoundaryStruct( size, top, bottom, left, right );
}

/**
* EnvironmentClass constructor
* @param width environment width
* @param height environment height
* @param objLs vector of objects (robots, targets, obstacles)
* @param margin margin of window, which would be a square
*/
EnvironmentClass::EnvironmentClass( int width, int height,
    PhysObjList &objLs, int margin ) {

    size = SizeStruct( width, height );
    borders = BoundaryStruct( size, margin );
    objects = objLs;
}

/**
* ~EnvironmentClass destructor
*/
EnvironmentClass::~EnvironmentClass() {
    // Traverse thru the list and release memory for each object.
    for ( int i = 0; i < objects.size(); i++ ) {
        delete objects[ i ];
    }
}

/* ***************************************************************************
 *
 * GETTERS & SETTERS
 *
 * *************************************************************************** */

/**
* setBoundary
* @param top top of boundary.
* @param bottom bottom of boundary.
* @param left left part of boundary.
* @param right right part of boundary.
*/
void EnvironmentClass::setBoundary( int top, int bottom, int left, int right ) {
    // If preset values are appropriate, set border values to new ones.
    if ( ( top > bottom ) && ( bottom >= 0 ) &&
        ( right > left ) && ( left >= 0 ) ) {

        borders.top = top;
        borders.bottom = bottom;
        borders.left = left;
        borders.right = right;
    }

    // Otherwise, do not make any change to the border values.
}

/* ***************************************************************************
 *
 * PUBLIC FUNCTIONS
 *
 * *************************************************************************** */

/**
* registerObject
* @param obj object to register
*/
ID EnvironmentClass::registerObject( PhysObj obj ) {
    // If the object exists, add then return its ID number.
    if ( obj ) {
        // Newly added object's ID equals to object count before adding plus 1
        ID objectID = IndextoID( getObjectCount() );
        objects.push_back( obj );
        return objectID;
    }

    // Otherwise, return zero to indicate failure from adding object to list.
    return 0;
}

/**
* touchSensorReading reading to robot from environment
* @param obj obj to do the sensor
*/
SensorValue EnvironmentClass::touchSensorReading( PhysObj obj ) {
    // any object can be passed in, we aren't testing for robot currently
    for (unsigned long int i = 0; i < objects.size(); i++) {
        if (obj->detectObstacle(objects.at(i))) {
            // check if the object collided with is the robots target, and if so, set them to deleted (removes them before next iteration)
            if (targetSensorReading( obj, objects.at(i) )) {
                printf("target sensor fired\n");
                obj->setDeleted(true);
                objects.at(i)->setDeleted(true);
            }
            return ACTIVATED;
        }
        else if (obj->detectWall(size)) {
            return ACTIVATED;
        }
    }
    return NOT_ACTIVATED;
}

bool EnvironmentClass::detectWall(PhysObj obj,BoundaryStruct borders) {
    // assumes that the position of the robot is its center,
    // so size of the robot needs to be taken into account for collisions
    //int windowWidth = windowSize.width;
    //int windowHeight = windowSize.height;

    int robotMinPosX = obj->getXPosition() - obj->getRadius();
    int robotMaxPosX = obj->getXPosition() + obj->getRadius();
    int robotMinPosY = obj->getYPosition() - obj->getRadius();
    int robotMaxPosY = obj->getYPosition() + obj->getRadius();

    if ((robotMinPosX >= borders.left) &&
        (robotMaxPosX <= borders.right) &&
        (robotMinPosY >= borders.bottom) &&
        (robotMaxPosY <= borders.top)) {
        obj->setColor(0, 255, 0);
        return false;
    }

    obj->setColor(255, 0, 0);
    return true;
}

/**
* targetSensorReading whether or not the collided object is the target
* @params PhysObj obj the object to use
* @params PhysObj target the target
* @return bool whether it was the robots target or not
*/
bool EnvironmentClass::targetSensorReading( PhysObj obj, PhysObj target) {
    return false;
}

float EnvironmentClass::vectorHoming( PhysObj obj ) {
    for ( unsigned long int i = 0; i < objects.size(); i++ ) {
        if ( objects.at(i)->getType() == TARGET ) {
            float x = objects.at(i)->getXPosition() - obj->getXPosition();
            float y = objects.at(i)->getYPosition() - obj->getYPosition();
            return ( (float) (( atan( y / x ) * 360 ) / ( 2 * 3.14 )) ); // added cast
        }
    }
    return 0;
}

void EnvironmentClass::update( double elapsedTime ) {

    printf("updating...\n");

    for (unsigned int i = 0; i < objects.size(); i++) {
        switch(objects.at(i)->getType()) {
            case ROBOT:
                if (touchSensorReading(objects.at(i))) {
                    objects.at(i)->rotate(91); // rotate away from wall or non-target
                    objects.at(i)->move(elapsedTime);
                }
                else {
                    objects.at(i)->move(elapsedTime);
                }
            break;
            case TARGET:
                if (touchSensorReading(objects.at(i))) {
                    printf("target touch sensor fired\n");
                    objects.at(i)->rotate(91);
                    objects.at(i)->move(elapsedTime);
                }
                else if (detectWall(objects.at(i),borders)) {
                    printf("target detected wall");
                    objects.at(i)->rotate(91);
                    objects.at(i)->move(elapsedTime);
                }
                else {
                    objects.at(i)->move(elapsedTime);
                }
            break;
            case OBSTACLE:
                // obstacle will just sit there?
            break;
            case LIGHT:
                if (objects.at(i)->isMovable()) {
                    if (detectWall(objects.at(i),borders)) {
                        printf("light detected wall");
                        objects.at(i)->rotate(91);
                        objects.at(i)->move(elapsedTime);
                    }
                    else {
                        objects.at(i)->move(elapsedTime);
                    }
                }
                else {
                    // do nothing
                }
            break;
        }
    }

    // doing this outside of main loop b/c things could get messy, hope it works!
    unsigned long int vectorSize = objects.size();
    for (unsigned long int i = 0; i < vectorSize; i++) {
        if (objects.at(i)->getDeleted()) {
            objects.erase(objects.begin()+i-1); // erase object
            i-=1;
            vectorSize-=1;
        }
    }

}