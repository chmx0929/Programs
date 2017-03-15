//
// FalloffEllipseMask.h
//

#ifndef M_FALLOFFELLIPSEMASK_H
#define M_FALLOFFELLIPSEMASK_H

#include "MaskBehavior.h"

class M_FalloffEllipseMask : public MaskBehavior {
public:
	M_FalloffEllipseMask() {};
	~M_FalloffEllipseMask() {};
	float maskPattern(float maxFloat, int width, int height, int x, int y);
};
#endif
