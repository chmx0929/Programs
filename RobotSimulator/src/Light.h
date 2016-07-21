//
// Created by Joseph Wheaton on 3/24/15.
//

#ifndef _REPO_GROUP_6_LIGHT_H_
#define _REPO_GROUP_6_LIGHT_H_

#include "PhysicalObjectClass.h"

class Light : public PhysicalObjectClass {

    public:

        /**
        * Light constructor.
        */
        Light();
        Light(int x, int y, int r, bool movable);
        ~Light();

        /**
        * getMovable get the movable property of this object, which determines whether this light/stimulation source can
        * move.
        * @return whether or not the light/stimulation source can move
        */
        bool isMovable();

        /**
        * setMovable set the movable property of the object.
        * @param val the boolean val to which the movable property is set (true for movable, false for not movable)
        */
        void setMovable(bool val);

    protected:
        bool movable;
};


#endif //_REPO_GROUP_6_LIGHT_H_
