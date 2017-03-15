//
// HaloEllipseMask.h
//

#ifndef M_HALOELLIPSEMASK_H
#define M_HALOELLIPSEMASK_H

#include "MaskBehavior.h"

class M_HaloEllipseMask : public MaskBehavior {
public:
	M_HaloEllipseMask() {};
	~M_HaloEllipseMask() {};
	float maskPattern(float maxFloat, int width, int height, int x, int y);
};
#endif
