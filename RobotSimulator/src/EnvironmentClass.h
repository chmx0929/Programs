/**
 * @file EnvironmentClass.h
 * A header file contains class declaration of the class EnvironmentClass.
 *
 * @author Group 6
 * @see EnvironmentClass.cpp
 */


#ifndef ENVIRONMENTCLASS_H
#define ENVIRONMENTCLASS_H

#include "BoundaryStruct.h"
#include "Light.h"
#include "PhysicalObjectClass.h"
#include "RobotClass.h"
#include "SizeStruct.h"
#include "Target.h"

#include <cmath>
#include <vector>

/* ***************************************************************************
 *
 * ENUMERATIONS & TYPE DEFINITIONS
 *
 * *************************************************************************** */

/**
 * A sensor feedback value type.
 * Used as a return type for the touchSensorReading() function.
 * 
 * @see EnvironmentClass#touchSensorReading(PhysObj)
 */
enum SensorValue {
    NOT_ACTIVATED=0, /**< This means object not touching anything. */
    ACTIVATED=1 /**< This means object touching something. */
};

/**
 * Short-hand for a PhysicalObjectClass pointer.
 * 
 * @see PhysicalObjectClass
 */
typedef PhysicalObjectClass* PhysObj;

/**
 * Short-hand for a vector of PhysicalObjectClass pointer.
 * A list of pointers intended use for dynamic binded objects in polymorphism.
 * 
 * @see #PhysObj
 */
typedef std::vector<PhysicalObjectClass*> PhysObjList;

/**
 * An identification number type.
 * Used as a return type for the registerObject() function. ID starts at 1, while
 * array's index starts at 0.
 * 
 * @see EnvironmentClass#registerObject(PhysObj)
 * @see #IDtoIndex(ID)
 * @see #IndextoID(int)
 */
typedef int ID;

/* ***************************************************************************
 *
 * GLOBAL FUNCTIONS
 *
 * *************************************************************************** */

/**
 * Convert an ID type into an integer-type array index.
 * 
 * @see #IndextoID(int)
 */
inline int IDtoIndex( ID n ) { return n - 1; }

/**
 * Convert an integer-type array index into an ID type.
 * 
 * @see @IDtoIndex(ID)
 */
inline ID IndextoID( int n ) { return n + 1; }

/* ***************************************************************************
 *
 * ENVIRONMENT CLASS
 *
 * *************************************************************************** */

/**
 * A virtual physical environment in which objects interact.
 * The environment knows the configuration of the physical world including the
 * size and boundary of the operational environment, and it provides sensor
 * feedback to the various objects that operate in its environment @cite larson2. <BR>
 * <BR>
 * The size will be of a rectangle representing a graphical window, while the
 * boundary will limit the ground where objects (i.e., a robot) can operate.
 * 
 * @see SizeStruct
 * @see BoundaryStruct
 * @see #PhysObjList
 */
class EnvironmentClass {
  public:

    /* ***********************************************************************
     *
     * CONSTRUCTORS & DESTRUCTOR
     *
     * *********************************************************************** */

    /**
     * A normal constructor.
     * Set up an environment of rectangular shape. User can determine the margin
     * between the environment's sides and the objects' operational boundary. The
     * default setting is boundary has the same size as environment's. Upon created,
     * environment has no objects.
     * 
     * @param width width size of the environment
     * @param height height size of the environment
     * @param margin margin between size and boundary (default value is 0)
     * @see BoundaryStruct#BoundaryStruct(SizeStruct&, int)
     */
    EnvironmentClass( int width, int height, int margin=0 );

    /**
     * A constructor for setting the boundary manually.
     * 
     * @param width width size of the environment
     * @param height height size of the environment
     * @param top top border of the environment
     * @param bottom bottom border of the environment
     * @param left left border of the environment
     * @param right right border of the environment
     * @see BoundaryStruct#BoundaryStruct(SizeStruct&, int, int, int, int)
     */
    EnvironmentClass( int width, int height,
        int top, int bottom, int left, int right );

    /**
     * A constructor with a pre-defined list of operational objects.
     * This is useful to create an environment already having objects in it without
     * manually adding one by one. User can still add more objects if needed later.
     * 
     * @param width width size of the environment
     * @param height height size of the environment
     * @param objLs a list of physical objects
     * @param margin margin between size and boundary (default value is 0)
     */
    EnvironmentClass( int width, int height, PhysObjList &objLs, int margin=0 );

    /**
     * Destructor of the EnvironmentClass.
     * Cleaning up the physical object list.
     */
    ~EnvironmentClass();

    /* ***********************************************************************
     *
     * GETTERS & SETTERS
     *
     * *********************************************************************** */

    /**
     * Environment's width size getter.
     * 
     * @return width size
     */
    int getWidth() { return size.width; }

    /**
     * Environment's height size getter.
     * 
     * @return height size
     */
    int getHeight() { return size.height; }

    /**
     * Environment's top border getter.
     * 
     * @return top border
     */
    int getTopBorder() { return borders.top; }

    /**
     * Environment's bottom border getter.
     * 
     * @return bottom border
     */
    int getBottomBorder() { return borders.bottom; }

    /**
     * Environment's left border getter.
     * 
     * @return left border
     */
    int getLeftBorder() { return borders.left; }

    /**
     * Environment's right border getter.
     * 
     * @return right border
     */
    int getRightBorder() { return borders.right; }

    /**
     * Environment's object list's length getter.
     * 
     * @return how many objects currently in the list
     */
    int getObjectCount() { return objects.size(); }

    /**
     * Environment's object list getter.
     * 
     * @return a copy of the object list
     */
    PhysObjList getObjectList() { return objects; }

    /**
     * Environment's boundary setter.
     * All parameters have to be non-negative values, and the boundary has to be
     * either overlapping the environment's sides or within the environment. Refer
     * to BoundaryStruct for how the borders are represented.
     * 
     * @param top top border of the environment
     * @param bottom bottom border of the environment
     * @param left left border of the environment
     * @param right right border of the environment
     */
    void setBoundary( int top, int bottom, int left, int right );

    /* ***********************************************************************
     *
     * PUBLIC FUNCTIONS
     *
     * *********************************************************************** */

    /**
     * Function that adds objects to the environment.
     * The parameter is actually a pointer to PhysicalObjectClass. Object will not
     * be added if null pointer. Uninitialized objects may result in a core dump.
     * After objects register with the environment, they will be given an ID number
     * for later use in retrieving information from the list. The object's ID starts
     * from 1; e.g. 1 for first added object, 2 for second added and so on. <BR>
     * <BR>
     * Example usage: <BR>
     * @code{.cpp}
     * EnvironmentClass env( 800, 600 );
     * ID robotID = env.registerObject( new RobotClass() ); // ID is 1
     * RobotClass *robot = env.getObjectList().at( IDtoIndex( robotID ) ); // index is 0
     * @endcode
     * 
     * @param obj a physical object to be added
     * @return the added object's ID number, or 0 on failure
     * @see #ID
     */
    ID registerObject( PhysObj obj );

    /**
     * Function that provides "Touch" sensor feedback to an object.
     * Imagine the object has a sensor mechanism around it, if it collides with
     * anything, this sensor is activated. When the object requests "Touch" sensor
     * feedback, the environment will check if the object is touching (i.e. colliding
     * or overlapping the wall or another object) and return "1" for activated or
     * "0" for not activated @cite larson2. <BR>
     * <BR>
     * Assuming the object to be checked is a valid one of PhysicalObjectClass and
     * is in the environment's object list. Object will not be checked if null pointer.
     * 
     * @param obj a physical object to be checked
     * @return ACTIVATED if collide with another object, NOT_ACTIVATED otherwise
     * @see #SensorValue
     */
    SensorValue touchSensorReading( PhysObj obj );

    bool targetSensorReading( PhysObj obj, PhysObj target );

    /**
    * detectWall environment method for detecting walls
    * @param obj object that needs to detect
    * @param borders border of env
    */
    bool detectWall(PhysObj obj, BoundaryStruct borders);

    /**
     * vectorHoming vector "homing" sensor thing
     * @param obj thing to home in on
     * @return degrees we need to turn?
     */
    float vectorHoming( PhysObj obj );

   /**
    * update
    * @param elapsedTime time elapsed since last frame.
    */
    void update( double elapsedTime );

  private:
    SizeStruct size; /**< Size of the environment. */
    BoundaryStruct borders; /**< Actual boundary for object's operations. */
    PhysObjList objects; /**< A list of objects in the environment. */
};

#endif
