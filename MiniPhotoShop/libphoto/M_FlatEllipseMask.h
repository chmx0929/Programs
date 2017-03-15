//
// FlatEllipseMask.h
//

#ifndef M_FLATELLIPSEMASK_H
#define M_FLATELLIPSEMASK_H

#include "MaskBehavior.h"

class M_FlatEllipseMask : public MaskBehavior {
public:
	M_FlatEllipseMask() {};
	~M_FlatEllipseMask() {};
	float maskPattern(float maxFloat,int width, int height, int x, int y);
};
#endif
