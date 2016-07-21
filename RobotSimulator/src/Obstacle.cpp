/**
 * \author Group 6
 *
 * \file  Obstacle.cpp
 * \brief The implemetation of the obstacle class
 *
 */

#include "Obstacle.h"
#include <stdio.h> 
#include <iostream> 
#include <time.h>
#include <stdlib.h>
using namespace std;

#include <cmath>
#include <cstdlib>

Obstacle::Obstacle() : PhysicalObjectClass() {
    // calling RobotClass default constructor
    // then correct its type
    Type = OBSTACLE;
    xPosition = rand()%750+100;
    yPosition = rand()%550+100;
    radius = rand()%50;
}

Obstacle::~Obstacle() {
    // empty
}
