//
// Created by Joseph Wheaton on 4/7/15.
// Edited by Alex Westby on 4/7/15.
//

#include "LightSensor.h"

LightSensor::LightSensor() {
    this->setSensorType(EXCITATORY);
}

LightSensor::~LightSensor() {

}

SensorType LightSensor::getSensorType() {
    return this->sensorType;
};

void LightSensor::setSensorType(SensorType val) {
    this->sensorType = val;
};

int LightSensor::sendSpeed() {
// If the sensor is Inhibitory
    if( this->getSensorType() == 0 ) {
        return 0;
    }
// Else if the sensor is Excitatory
    else {
        return 0;
    }
}
