/**
 * @file PhysicalObjectClass.cpp
 * Implemetation of PhysicalObjectClass.
 *
 * @author Group 6
 * @see PhysicalObjectClass.h
 */


#include "PhysicalObjectClass.h"
#include "math.h"
#include <stdio.h> 
#include <iostream> 
#include <time.h>
#include <stdlib.h>
using namespace std;
#define PI 3.14159265

#include <cmath>

void PhysicalObjectClass::foo() {
    position += 1;
}

bool PhysicalObjectClass::isMovable() {
    return true;
}

bool PhysicalObjectClass::detectObstacle( PhysicalObjectClass * obs ) {
    printf("  x y\nrobot: %d %d\nobs: %d %d\n", this->getXPosition(), this->getYPosition(), obs->getXPosition(), obs->getYPosition());
    if ((this->getXPosition() >= (obs->getXPosition() - obs->getRadius())) &&
       (this->getXPosition() <= (obs->getXPosition() + obs->getRadius())) &&
       (this->getYPosition() >= (obs->getYPosition() - obs->getRadius())) &&
       (this->getYPosition() <= (obs->getYPosition() + obs->getRadius()))) {

        printf("obj detected obstacle\n");

        this->setColor(255, 0, 0);

        return true;
    }
    else {
        this->setColor(0, 255, 0);
        return false;
    }
}

bool PhysicalObjectClass::getDeleted() {
    return this->deleted;
}

void PhysicalObjectClass::setDeleted(bool val) {
    this->deleted = val;
}

int PhysicalObjectClass::getOrientation() {

    return orientation;
}

bool PhysicalObjectClass::detectWall(SizeStruct windowSize) {
    int windowWidth = windowSize.width;
    int windowHeight = windowSize.height;

    printf("WINDOW SIZE:: W: %d H: %d\n", windowWidth, windowHeight);

    int robotMinPosX = this->getXPosition() - this->radius;
    int robotMaxPosX = this->getXPosition() + this->radius;
    int robotMinPosY = this->getYPosition() - this->radius;
    int robotMaxPosY = this->getYPosition() + this->radius;

    if (
            (robotMinPosX >= 0) &&
            (robotMaxPosX <= windowWidth) &&
            (robotMinPosY >= 0) &&
            (robotMaxPosY <= windowHeight)
    ) {

        printf("obj detected wall\n%d %d %d %d\n", robotMinPosX, robotMaxPosX, robotMinPosY, robotMaxPosY);
        this->setColor(0, 255, 0);
        return false;
    }

    this->setColor(255, 0, 0);
    return true;
}

void PhysicalObjectClass::setOrientation( int degrees ) {
    orientation = degrees;
}

void PhysicalObjectClass::rotate( int degrees ) {
    // currently empty
    this->setOrientation((this->getOrientation() + degrees) % 360);
}

void PhysicalObjectClass::move(double elapsedTime){
    if(/*Type == ROBOT*/ true){
        //if (orientation<90){
            xPosition =  (int) (xPosition + speed * elapsedTime * cos( orientation * 3.14 / 180.0  ));
            yPosition =  (int) (yPosition + speed * elapsedTime * sin( orientation * 3.14 / 180.0 ));
        //}
        /*if (orientation>90&&orientation<180){
            xPosition =  xPosition - speed * elapsedTime * cos( orientation * 3.14 / 180.0  );
            yPosition =  yPosition + speed * elapsedTime * sin( orientation * 3.14 / 180.0  );
        }
        if (orientation<270&&orientation>180){
            xPosition =  xPosition - speed * elapsedTime * cos(  orientation * 3.14 / 180.0  );
            yPosition =  yPosition - speed * elapsedTime * sin(  orientation * 3.14 / 180.0  );
        }
        if (orientation>270&&orientation<360){
            xPosition =  xPosition - speed * elapsedTime * cos(  orientation * 3.14 / 180.0  );
            yPosition =  yPosition - speed * elapsedTime * sin(  orientation * 3.14 / 180.0  );
        }*/
    }
    else{
        int randomX = rand()%2;
        int randomY = rand()%2;
        if(randomX==1&&randomY==1){
            xPosition =  xPosition + rand()%5;
            yPosition =  yPosition + rand()%5;
        }
        if(randomX==1&&randomY==0){
            xPosition =  xPosition + rand()%5;
            yPosition =  yPosition - rand()%5;
        }
        if(randomX==0&&randomY==1){
            xPosition =  xPosition - rand()%5;
            yPosition =  yPosition + rand()%5;
        }
        if(randomX==0&&randomY==0){
            xPosition =  xPosition - rand()%5;
            yPosition =  yPosition - rand()%5;
        }
    }
}

void PhysicalObjectClass::pointTo( PhysicalObjectClass *target ) {

    // // lets create unit vectors out of the orientation of both of these

    // double unitX1 = 1 * cos(orientation);
    // double unitY1 = 1 * sin(orientation);

    // double unitX2 = 1 * cos(target->orientation);
    // double unitY2 = 1 * sin(target->orientation);

    // // calculate angle between vectors

    // double angle = acos( (unitX1 * unitX2 + unitY1 * unitY2) / (sqrt(unitX1 * unitX1 + unitY1 * unitY1) * sqrt(unitX2 * unitX2 + unitY1 * unitY2))) * 180/PI;

    // // set orientation to new angle

    //  rotate((int) angle);
    //  int x = target->getXPosition()-this->getXPosition();
    //  int y = target->getYPosition()-this->getYPosition();
     
    // if(x>0&&y>0){
    //     float d = atan(y/x);
    //     this->setOrientation((int)((d*360)/(2*3.14))%360);
    // }

    // if(x>0&&y<0){
    //     float d = atan(y/x);
    //     this->setOrientation((int)((d*360)/(2*3.14))%360);
    // }

    // if(x<0&&y>0){
    //     float d = atan(y/x);
    //     this->setOrientation((int)((d*360)/(2*3.14)+180)%360);
    // }

    // if(x<0&&y<0){
    //     float d = atan(y/x);
    //     this->setOrientation((int)((d*360)/(2*3.14)+180)%360);
    // }
    int x = target->getXPosition()-this->getXPosition();
    int y = target->getYPosition()-this->getYPosition();
     
    int d = sqrt(pow(x,2)+pow(y,2));
    int degree = acos(x/d);
    if(y>0){
        orientation = (degree*180)/3.14;
    }
    else{
        orientation = 360 - (degree*180)/3.14;
    }
}
