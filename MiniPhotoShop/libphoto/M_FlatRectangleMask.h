//
// FlatRectangleMask.h
//

#ifndef M_FLATRECTANGLEMASK_H
#define M_FLATRECTANGLEMASK_H

#include "MaskBehavior.h"

class M_FlatRectangleMask : public MaskBehavior {
public:
	M_FlatRectangleMask() {};
	~M_FlatRectangleMask() {};
	float maskPattern(float maxFloat, int width, int height, int x, int y);
};
#endif
