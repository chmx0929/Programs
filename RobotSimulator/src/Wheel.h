//
// Created by Joseph Wheaton on 3/30/15.
//

#include "LightSensor.h"

#ifndef _REPO_GROUP_6_WHEEL_H_
#define _REPO_GROUP_6_WHEEL_H_


class Wheel {
    public:
        Wheel();
        ~Wheel();

        /**
        * getSpeed get the wheel speed.
        * @return the speed of the wheel as an integer
        */
        int getSpeed();

        /**
        * setSpeed set the wheel speed.
        * @param speed the speed to set the wheel to
        */
        void setSpeed(int speed);

        /**
        * getX get the x coordinate value of the wheel.
        * The wheels may be at different coordinate values.
        * @return the x coordinate value
        */
        int getX();

        /**
        * setX set the x coordinate of the wheel.
        * @param xCoordinate integer value to assign to the x coord of the wheel
        */
        void setX(int xCoordinate);

        /**
        * getY get the y coordinate value of the wheel.
        * The wheels may be at different coordinate values.
        * @return the y coordinate value
        */
        int getY();

        /**
        * setY set the y coordinate of the wheel.
        * @param yCoordinate integer value to assign to the y coord of the wheel
        */
        void setY(int yCoordinate);

        /**
        * getLightSensor get the light sensor on this wheel, ie, the wheel will only have one sensor.
        * @return a LightSensor object
        */
        LightSensor getLightSensor();

        /**
        * setLightSensor set the light sensor on this wheel.
        * @param sensor the LightSensor object to assign to this wheel
        */
        void setLightSensor(LightSensor* sensor);

    private:
        int speed, x, y;
        LightSensor sensor;
};


#endif //_REPO_GROUP_6_WHEEL_H_
