/**
 * \author Group 6
 *
 * \file  Simulation.h
 * \brief Main application class for the robot simulation
 *
 */

#ifndef SIMULATION_H
#define SIMULATION_H

#include "BaseGfxApp.h"
#include "EnvironmentClass.h"

#include <vector>

// const int robotCount = 2;
// const int obstacleCount = 6;
// const int targetCount = 2;

// ID robotIDs[ robotCount ];
// ID obstacleIDs[ obstacleCount ];
// ID targetIDs[ targetCount ];

/** The Simulation class.  This sets up the GUI and the drawing environment. */
class Simulation : public BaseGfxApp {
  public:
    enum UIControlType {
        UI_QUIT = 0,
        UI_PAUSE = 1,
        UI_START = 2,
        UI_REUSE = 3
    };

    //Simulation( int argc, char* argv[], int width, int height );
    Simulation( int argc, char* argv[], EnvironmentClass *ec );
    virtual ~Simulation();

    void display();
    //void addObstacle( Obstacle *ob );
    //void addTarget( Target *tg );
    void gluiControl( int controlID );
    void leftMouseDown( int x, int y );
    void leftMouseUp( int x, int y );
    // int robotCount = 2;
    // int obstacleCount = 6;
    // int targetCount = 2;

    ID robotIDs[ 2 ];
    ID obstacleIDs[ 6 ];
    ID targetIDs[ 2 ];
    ID lightIDs[ 2 ];

  private:
    EnvironmentClass *env;
    //RobotClass *robot;
    //Obstacle *obstacle1;
    //Obstacle *obstacle2;
    //Target *target;
    //vector<RobotClass *> simObject;

    //void placeRobotAtRandom( RobotClass *rb ); // Might reuse this!
    void drawRobot( PhysObj obj, PhysObj tar );
    void drawObstacle( PhysObj obj );
    void drawTarget( PhysObj obj );
    void drawLight( PhysObj obj );
    double elpasTime;
    bool statement;
};
#endif
