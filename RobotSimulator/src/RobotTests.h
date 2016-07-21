#include <cxxtest/TestSuite.h>
#include "RobotClass.h"
#include "Obstacle.h"
#include "Target.h"

class RobotTests : public CxxTest::TestSuite {
  public:
    RobotClass *robot;
    RobotClass *obstacle;
    RobotClass *target;

    void setUp() {
    robot = new RobotClass();
	obstacle = new RobotClass();
	target = new RobotClass();
    }

    void tearDown() {
        delete robot;
	delete obstacle;
	delete target;
    }

    /* ****************************************************************************************************
     *
     * TESTING GETTERS AND SETTERS
     *
     * **************************************************************************************************** */
    
    /** 
      * testPosition test position of robot.
      */
    void testPosition() {
        // A default robot is at position ( 0, 0 )
        TS_ASSERT_EQUALS( robot->getXPosition(), 0 );
        TS_ASSERT_EQUALS( robot->getYPosition(), 0 );

        robot->setPosition( 1, 1 );
        TS_ASSERT_EQUALS( robot->getXPosition(), 1 );
        TS_ASSERT_EQUALS( robot->getYPosition(), 1 );
    }

    /**
     * testRadius test radius of robot
     */
    void testRadius() {
        // A default robot has radius of 0
        TS_ASSERT_EQUALS( robot->getRadius(), 0 );

        robot->setRadius( 10 );
        TS_ASSERT_EQUALS( robot->getRadius(), 10 );
    }

    /**
     * testRadiusForNegativeValue test if radius is proper value
     */
    void testRadiusForNegativeValues() {
        // When set to negative, radius is set to 0
        robot->setRadius( -10 );
        TS_ASSERT_EQUALS( robot->getRadius(), 0 );
    }

    /**
     * testRadiusForNegativeValues see of radius is set to 0 properly
     */
    void testOrientation() {
        // A default robot's orientation is 0 degrees
        TS_ASSERT_EQUALS( robot->getOrientation(), 0 );

        robot->setOrientation( 30 );
        TS_ASSERT_EQUALS( robot->getOrientation(), 30 );
    }

    void testSpeed() {
        // A default robot's speed is 0 pixels per second
        TS_ASSERT_EQUALS( robot->getSpeed(), 0 );

        robot->setSpeed( 5 );
        TS_ASSERT_EQUALS( robot->getSpeed(), 5 );
    }

    void testSpeedForNegativeValues() {
        // When set to negative, speed is set to 0
        robot->setSpeed( -5 );
        TS_ASSERT_EQUALS( robot->getSpeed(), 0 );
    }

    /* ****************************************************************************************************
     *
     * TESTING DETECT_WALL FUNCTION
     *
     * **************************************************************************************************** */

    // thus no params necessary
    void testDetectWallCollision() {
        // set at 0,0 there should be a collision if the robot is size 50
        robot->setPosition( 0, 0 );
	robot->setRadius(25);
        TS_ASSERT( robot->detectWall() );
    }


    void testDetectWallNoCollision() {
        // set at 200,200 there should not be a collision if the robot is size 50
        robot->setPosition( 200, 200 );
	robot->setRadius(25);
        TS_ASSERT( !(robot->detectWall()) );
    }

    void testDetectWallEdge() {
        // set at 25,25 there should not be a collision if the robot is size 50
        robot->setPosition( 25, 25 );
	robot->setRadius(25);
        TS_ASSERT( !(robot->detectWall()) );
    }

    /* ****************************************************************************************************
     *
     * TESTING DETECT_OBSTACLE FUNCTION
     *
     * **************************************************************************************************** */

    void testDetectObstacleCollision() {
        robot->setPosition( 100, 100 );
	robot->setRadius(25);
        obstacle->setPosition( 100, 100 );
	obstacle->setRadius(25);
        TS_ASSERT( robot->detectObstacle( obstacle ) );
    }

    void testDetectObstacleNoCollision() {
        robot->setPosition( 100, 100 );
	robot->setRadius(25);
        obstacle->setPosition( 200, 200 );
	obstacle->setRadius(25);
        TS_ASSERT( !(robot->detectObstacle( obstacle )) );
    }

    /* ****************************************************************************************************
     *
     * TESTING ROTATE FUNCTION
     *
     * **************************************************************************************************** */

    void testRotateTurnLeft() {
        robot->setOrientation( 90 );
        robot->rotate( 10 );
        TS_ASSERT_EQUALS( robot->getOrientation(), 100 );
    }

    void testRotateTurnRight() {
        robot->setOrientation( 90 );
        robot->rotate( -10 );
        TS_ASSERT_EQUALS( robot->getOrientation(), 80 );
    }

    /* ****************************************************************************************************
     *
     * TESTING TRANSLATE_X AND TRANSLATE_Y FUNCTION
     *
     * **************************************************************************************************** */

    void testTranslateXHorizontally() {
        // This test tests functionality of int RobotClass::translateX( int )
        // on the x-axis

        // Explicitly set robot's position
        robot->setPosition( 0, 0 );

        // Test to ensure the robot's x position is translated properly
        robot->setOrientation( 0 );
        TS_ASSERT_EQUALS( robot->translateX( 10 ), 10 );
        robot->setOrientation( 180 );
        TS_ASSERT_EQUALS( robot->translateX( 20 ), -10 );
    }

    void testTranslateXVertically() {
        // This test tests functionality of int RobotClass::translateX( int )
        // on the y-axis

        // Explicitly set robot's position
        robot->setPosition( 0, 0 );

        // Test to ensure the robot's x position is not changed
        robot->setOrientation( 90 );
        TS_ASSERT_EQUALS( robot->translateX( 10 ), 0 );
        robot->setOrientation( 270 );
        TS_ASSERT_EQUALS( robot->translateX( 20 ), 0 );
    }

    void testTranslateXDiagonally() {
        // This test tests functionality of int RobotClass::translateX( int )
        // on the y = x line

        // Explicitly set robot's position
        robot->setPosition( 0, 0 );

        // Test to ensure the robot's x position is translated properly
        robot->setOrientation( 45 );
        TS_ASSERT_EQUALS( robot->translateX( 10 ), 7 );
        robot->setOrientation( 225 );
        TS_ASSERT_EQUALS( robot->translateX( 20 ), -7 );
    }

    void testTranslateYHorizontally() {
        // This test tests functionality of int RobotClass::translateY( int )
        // on the x-axis

        // Explicitly set robot's position
        robot->setPosition( 0, 0 );

        // Test to ensure the robot's y position is not changed
        robot->setOrientation( 0 );
        TS_ASSERT_EQUALS( robot->translateY( 10 ), 0 );
        robot->setOrientation( 180 );
        TS_ASSERT_EQUALS( robot->translateY( 20 ), 0 );
    }

    void testTranslateYVertically() {
        // This test tests functionality of int RobotClass::translateY( int )
        // on the y-axis

        // Explicitly set robot's position
        robot->setPosition( 0, 0 );

        // Test to ensure the robot's y position is translated properly
        robot->setOrientation( 90 );
        TS_ASSERT_EQUALS( robot->translateY( 10 ), 10 );
        robot->setOrientation( 270 );
        TS_ASSERT_EQUALS( robot->translateY( 20 ), -10 );
    }

    void testTranslateYDiagonally() {
        // This test tests functionality of int RobotClass::translateY( int )
        // on the y = x line

        // Explicitly set robot's position
        robot->setPosition( 0, 0 );

        // Test to ensure the robot's y position is translated properly
        robot->setOrientation( 45 );
        TS_ASSERT_EQUALS( robot->translateY( 10 ), 7 );
        robot->setOrientation( 225 );
        TS_ASSERT_EQUALS( robot->translateY( 20 ), -7 );
    }

    /* ****************************************************************************************************
     *
     * TESTING UPDATE_POSITION FUNCTION
     *
     * **************************************************************************************************** */

    void testUpdatePosition() {
        // This tests functionality of void RobotClass::updatePosition( double )

        // Explicitly set robot's position, orientation and speed
        robot->setPosition( 0, 0 );
        robot->setSpeed( 5 );
        robot->setOrientation( 90 );

        // Test to see updatePosition properly translates the robot up 10 pixels over 2 seconds
        // When the speed is equal to 5 pps
        robot->updatePosition( 2.00 );
        TS_ASSERT_EQUALS( robot->getXPosition(), 10 );
        robot->updatePosition( 1.00 );
        TS_ASSERT_EQUALS( robot->getXPosition(), 15 );

        // Test to see if updatePosition works in the y direction or in other orientation
        robot->setOrientation( 0 );
        robot->updatePosition( 2.00 );
        TS_ASSERT_EQUALS( robot->getYPosition(), 10 );
        robot->updatePosition( 1.00 );
        TS_ASSERT_EQUALS( robot->getYPosition(), 15 );
    }

    /* ****************************************************************************************************
     *
     * TESTING POINT_TO FUNCTION
     *
     * **************************************************************************************************** */

    void testPointTo() {
        robot->setPosition( 0, 0 );
	robot->setOrientation( 0 );
	target->setPosition( 100, 100 );

	// assuming horizontal is zero and moving counterclockwise, robot should point to 45 degrees
        robot->pointTo( target );
	TS_ASSERT_EQUALS( robot->getOrientation(), 45 );
    }
};
