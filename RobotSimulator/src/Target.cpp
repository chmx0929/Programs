/**
 * \author Group 6
 *
 * \file  Target.cpp
 * \brief The implemetation of the target class
 *
 */

#include "Target.h"
#include <stdio.h> 
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <cmath>
#include <cstdlib>

using namespace std;

Target::Target() : PhysicalObjectClass() {
    // calling RobotClass default constructor
    // then correct its type
    Type = TARGET;
    xPosition = rand()%750+100;
    yPosition = rand()%550+100;
    radius = 30;
}

Target::~Target() {
    // empty
}

