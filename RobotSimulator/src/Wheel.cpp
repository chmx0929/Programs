//
// Created by Joseph Wheaton on 3/30/15.
//

#include "Wheel.h"

Wheel::Wheel() {
    this->setSpeed(0);
    this->setLightSensor(new LightSensor());
}

Wheel::~Wheel() {

}

int Wheel::getSpeed() {
    return this->speed;
}

void Wheel::setSpeed(int speed) {
    this->speed = speed;
}

int Wheel::getX() {
    return this->x;
}

void Wheel::setX(int xCoordinate) {
    this->x = xCoordinate;
}

int Wheel::getY() {
    return this->y;
}

void Wheel::setY(int yCoordinate) {
    this->y = yCoordinate;
}

LightSensor Wheel::getLightSensor() {
    return this->sensor;
}

void Wheel::setLightSensor(LightSensor* sensor) {
    this->sensor = * sensor;
}