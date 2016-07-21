//
// Created by Joseph Wheaton on 4/7/15.
// Edited by Alex Westby on 4/7/15.
//

#ifndef _REPO_GROUP_6_LIGHTSENSOR_H_
#define _REPO_GROUP_6_LIGHTSENSOR_H_

enum SensorType {
    INHIBITORY=0,
    EXCITATORY=1
};

class LightSensor {
    public:

        /**
        * LightSensor default constructor.
        */
        LightSensor();

        /**
        * LightSensor destructor.
        */
        ~LightSensor();

        /**
        * getSensorType get the sensor type (inhibitory or excitatory) of this sensor.
        * @return the type of sensor
        */
        SensorType getSensorType();

        /**
        * setSensorType set the type of the sensor (inhibitory or excitatory).
        * @param val the type of the sensor
        */
        void setSensorType(SensorType val);

        /**
        * sendSpeed get the data from the environment and return a speed (for the wheel to read)
        * @return speed to set wheel in pps (pixels per second)
        */
	int sendSpeed();

    private:
        SensorType sensorType;

};


#endif //_REPO_GROUP_6_LIGHTSENSOR_H_
