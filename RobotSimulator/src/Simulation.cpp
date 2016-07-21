/**
 * \author Group 6
 *
 * \file  Simulation.cpp
 * \brief The implemetation of the robot simulation's class
 *
 */

#include "Simulation.h"

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
using namespace std;

#define ROBOT_COLOR 0.0f, 1.0f, 0.0f // green
#define ROBOT_DIRECTION_LINE_COLOR 1.0f, 0.0f, 0.0f // red
#define OBSTACLE_COLOR 0.0f, 0.0f, 1.0f // blue
#define TARGET_COLOR 1.0f, 0.0f, 0.0f // red
#define LIGHT_COLOR 0.0f, 1.0f, 1.0f

//const int ROBOT_RADIUS = 50;
//const int OBSTACLE_RADIUS = 50;
//const int TARGET_RADIUS = 50;

/**
* Simulation constructor for simulation
* @param argc arg count
* @param argv arg values
* @param ec environment the simulation is representing
*/
Simulation::Simulation( int argc, char* argv[], EnvironmentClass *ec )
    : BaseGfxApp( argc, argv, ec->getWidth(), ec->getHeight(),
    50, 50, GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH, true, 851, 50 ) {

    setCaption( "Robot Simulation" );

    // Creates a basic UI panel with quit button
    GLUI_Panel *toolPanel = new GLUI_Panel( m_glui, "Control Panel" ); 
    new GLUI_Button( m_glui, "Start", UI_START , (GLUI_Update_CB)s_gluicallback );
    new GLUI_Button( m_glui, "Pause", UI_PAUSE , (GLUI_Update_CB)s_gluicallback );
    new GLUI_Button( m_glui, "Reuse", UI_REUSE , (GLUI_Update_CB)s_gluicallback );
    new GLUI_Button( m_glui, "Quit", UI_QUIT, (GLUI_Update_CB)exit );

    // Initialize OpenGL
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ); 
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluOrtho2D( 0, m_width, 0, m_height );
    glViewport( 0, 0, m_width, m_height );
    

    // Bind the environment to the simulation
    env = ec;
    statement = false;
}

/**
* ~Simulation simulation destructor
*/
Simulation::~Simulation() {
    // empty
}

/* ****************************************************************************************************
 *
 * PUBLIC FUNCTIONS
 *
 * **************************************************************************************************** */

/**
* display code for displaying the environment
*/
void Simulation::display() {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    double elpasTimeStart = glutGet(GLUT_ELAPSED_TIME);

    
    drawRobot( env->getObjectList().at( IDtoIndex( robotIDs[ 0 ] ) ),env->getObjectList().at( IDtoIndex( targetIDs[ 0 ] ) ) );
    drawRobot( env->getObjectList().at( IDtoIndex( robotIDs[ 1 ] ) ),env->getObjectList().at( IDtoIndex( targetIDs[ 1 ] ) ) );
    drawTarget( env->getObjectList().at( IDtoIndex( targetIDs[ 0 ] ) ) );
    drawTarget( env->getObjectList().at( IDtoIndex( targetIDs[ 1 ] ) ) );
    //drawLight( env->getObjectList().at(IDtoIndex( lightIDs[0])));
    //drawLight( env->getObjectList().at(IDtoIndex( lightIDs[1])));
    for ( int i = 0; i < 6; i++ ) {
        drawObstacle( env->getObjectList().at( IDtoIndex( obstacleIDs[ i ] ) ) );
    }
    if(statement == true){
    double elpasTimeDown = glutGet(GLUT_ELAPSED_TIME);
    elpasTime = elpasTimeDown - elpasTimeStart;
    env->update(elpasTime);
     }
    // debugging messages
    int err;
    if ( ( err = glGetError() ) != GL_NO_ERROR ) {
        cerr << "GL is in an error state" << endl;
        cerr << "(GL error code " << err << ")\n";
        assert(0);
    
    }
    // advance
    glutSwapBuffers();
    
}



/** gluiControl glui control code
* @param controlID id for control
*/
void Simulation::gluiControl( int controlID ) {
    if(controlID == 1){
        statement = false;
    }
    else if (controlID == 2 || controlID == 3){
        statement = true;
    }
}

void Simulation::leftMouseDown( int x, int y ) {
    // nothing here for now
}

void Simulation::leftMouseUp( int x, int y ) {
    // nohing here for now
}

/* ****************************************************************************************************
 *
 * PRIVATE FUNCTIONS
 *
 * **************************************************************************************************** */

/*void Simulation::placeRobotAtRandom( RobotClass *rb ) {
    rb->setPosition( rand() % ( width() - rb->getRadius() * 2 ) + rb->getRadius(),
        rand() % ( height() - rb->getRadius() * 2 ) + rb->getRadius() );
    rb->setOrientation( rand() % 360 );
}*/

/**
* drawRobot method for drawing robots
* @param obj robot
* @param tar robot target
*/
void Simulation::drawRobot( PhysObj obj,PhysObj tar ) {
    // Draw a circle to depict the robot
    glPushMatrix();
    glTranslatef( obj->getXPosition(), obj->getYPosition(), 0.0f );
    glBegin( GL_TRIANGLE_FAN );
    glColor3f( ROBOT_COLOR ); // FIX THIS LATER!!!
    glVertex2f( 0.0f, 0.0f );
    for( int i = 0; i <= 100; i++ ) {
        glVertex2f( ( obj->getRadius() * cos( i * 2.0 * 3.14 / 20.0 ) ),
            ( obj->getRadius() * sin( i * 2.0 * 3.14 / 20.0 ) ) );
    }
    glEnd();
    glPopMatrix();

    // Draw the movement direction line
    obj->pointTo(tar);
    glPushMatrix();
    glTranslatef( obj->getXPosition(), obj->getYPosition(), 0.0f );
    glBegin( GL_LINES );
    glColor3f( ROBOT_DIRECTION_LINE_COLOR ); // FIX THIS LATER!!!
    glVertex2f( 0.0f, 0.0f );
    glVertex2f( 0.0f + obj->getRadius() * cos( obj->getOrientation() * 3.14 / 180.0 ),
        0.0f + obj->getRadius() * sin( obj->getOrientation() * 3.14 / 180.0 ) );
    glEnd();
    glPopMatrix();
}

/**
* drawObstacle
* @param obj obstacle object
*/
void Simulation::drawObstacle( PhysObj obj ) {
    // Obstacles are also circles
    glPushMatrix();
    glTranslatef( obj->getXPosition(), obj->getYPosition(), 0.0f );
    glBegin( GL_TRIANGLE_FAN );
    glColor3f( OBSTACLE_COLOR ); // FIX THIS LATER!!!
    glVertex2f( 0.0f, 0.0f );
    for( int i = 0; i <= 100; i++ ) {
        glVertex2f( ( obj->getRadius() * cos( i * 2.0 * 3.14 / 20.0 ) ),
            ( obj->getRadius() * sin( i * 2.0 * 3.14 / 20.0 ) ) );
    }
    glEnd();
    glPopMatrix();
}

/**
* drawTarget method for drawing target
* @param obj robot target
*/
void Simulation::drawTarget( PhysObj obj ) {
    // Targets are also circles
    glPushMatrix();
    glTranslatef( obj->getXPosition(), obj->getYPosition(), 0.0f );
    glBegin( GL_TRIANGLE_FAN );
    glColor3f( TARGET_COLOR ); // FIX THIS LATER!!!
    glVertex2f( 0.0f, 0.0f );
    for( int i = 0; i <= 100; i++ ) {
        glVertex2f( ( obj->getRadius() * cos( i * 2.0 * 3.14 / 20.0 ) ),
            ( obj->getRadius() * sin( i * 2.0 * 3.14 / 20.0 ) ) );
    }
    glEnd();
    glPopMatrix();
}

/**
* drawLight method for drawing light
* @param obj light
*/
void Simulation::drawLight( PhysObj light ) {
    glPushMatrix();
    glTranslatef( light->getXPosition(), light->getYPosition(), 0.0f );
    glBegin( GL_TRIANGLE_FAN );
    glColor3f( LIGHT_COLOR ); // FIX THIS LATER!!!
    glVertex2f( 0.0f, 0.0f );
    for( int i = 0; i <= 100; i++ ) {
        glVertex2f( ( light->getRadius() * cos( i * 2.0 * 3.14 / 20.0 ) ),
                ( light->getRadius() * sin( i * 2.0 * 3.14 / 20.0 ) ) );
    }
    glEnd();
    glPopMatrix();
}
