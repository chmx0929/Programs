/**
 * \author CSci5107 Guru
 *
 * \file  main.cpp
 * \brief Main function.
 *
 */

#include "RobotClass.h"
#include "Obstacle.h"
#include "Target.h"
#include "EnvironmentClass.h"
#include "Simulation.h"
#include <iostream>
#include "math.h"
#include <stdlib.h>
using namespace std;

// extern const int robotCount;
// extern const int obstacleCount;
// extern const int targetCount;

// extern ID robotIDs[];
// extern ID obstacleIDs[];
// extern ID targetIDs[];

int main( int argc, char* argv[] ) {
    // setting up environment
    EnvironmentClass *env = new EnvironmentClass( 800, 800 );

    // Run the simulation (it will take a pointer to the environment)
    Simulation *app = new Simulation( argc, argv, env );

    // Setting up objects (arguments for constructors will be different)
    // int obstacleCount = 6;


    // initial object and make sure no overlap
    // totally 10 objects for now
    int n =0;
    while(n < 10){
        if( n == 0){
            RobotClass *robot = new RobotClass();
            app->robotIDs[ 0 ] = env->registerObject( robot );
            n=n+1;
        }
        if(n == 1){
            RobotClass *robot = new RobotClass();
            int deltaX = robot->getXPosition() - env->getObjectList().at( 0 )->getXPosition();
            int deltaY = robot->getYPosition() - env->getObjectList().at( 0 )->getYPosition();
            int distance = sqrt(pow(deltaX,2)+pow(deltaY,2));
            if(distance > 60){
                app->robotIDs[ 1 ] = env->registerObject( robot );
                n=n+1;
            }
        }
        if(n == 2){
            Target *target = new Target();
            int count =0;
            for(int i = 0;i < n;i++){
                int deltaX = target->getXPosition() - env->getObjectList().at( i )->getXPosition();
                int deltaY = target->getYPosition() - env->getObjectList().at( i )->getYPosition();
                int distance = sqrt(pow(deltaX,2)+pow(deltaY,2));
                if(distance>60){
                    count++;
                }
            }
            if(count == n){
                app->targetIDs[ 0 ] = env->registerObject( target );
                n=n+1;
            }
        }
        if(n == 3){
            Target *target = new Target();
            int count =0;
            for(int i = 0;i < n;i++){
                int deltaX = target->getXPosition() - env->getObjectList().at( i )->getXPosition();
                int deltaY = target->getYPosition() - env->getObjectList().at( i )->getYPosition();
                int distance = sqrt(pow(deltaX,2)+pow(deltaY,2));
                if(distance>60){
                    count++;
                }
            }
            if(count == n){
                app->targetIDs[ 1 ] = env->registerObject( target );
                n=n+1;
            }
        }
        if(n > 3){
            Obstacle *obstacles = new Obstacle();
            int count =0;
            for(int i = 0;i < n;i++){
                int deltaX = obstacles->getXPosition() - env->getObjectList().at( i )->getXPosition();
                int deltaY = obstacles->getYPosition() - env->getObjectList().at( i )->getYPosition();
                int distance = sqrt(pow(deltaX,2)+pow(deltaY,2));
                if(distance>80){
                    count++;
                }
            }
            if(count == n){
                app->obstacleIDs[ n-4 ] = env->registerObject( obstacles );
                n=n+1;
            }
        }
    }
    // RobotClass *robot1 = new RobotClass();
    // RobotClass *robot2 = new RobotClass();
    
    // Target *target1 = new Target();
    // Target *target2 = new Target();
    // Obstacle *obstacles[ 6 ];
    // for ( int i = 0; i < 6; i++ ) {
    //     obstacles[ i ] = new Obstacle();
    // }

    // // Register objects
    // app->robotIDs[ 0 ] = env->registerObject( robot1 );
    // app->robotIDs[ 1 ] = env->registerObject( robot2 );
    // app->targetIDs[ 0 ] = env->registerObject( target1 );
    // app->targetIDs[ 1 ] = env->registerObject( target2 );
    // for ( int i = 0; i < 6; i++ ) {
    //     app->obstacleIDs[ i ] = env->registerObject( obstacles[ i ]  );
    // }



    app->runMainLoop();
    exit(0);
}

