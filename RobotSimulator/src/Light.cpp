//
// Created by Joseph Wheaton on 3/24/15.
//

#include "Light.h"

using namespace std;

Light::Light() : PhysicalObjectClass() {
    Type = LIGHT;
    xPosition = rand()%750+100;
    yPosition = rand()%550+100;
    radius = 10;
    orientation = 0;
    speed = 10;
    setMovable(false);
}

Light::Light(int x, int y, int r, bool movable) : PhysicalObjectClass() {
    Type = LIGHT;
    xPosition = x;
    yPosition = y;
    radius = r;
    this->setMovable(movable);
}

Light::~Light() {

}

bool Light::isMovable() {
    return movable;
}

void Light::setMovable(bool val) {
    movable = val;
}