//
// GradientRectangleMask.h
//

#ifndef M_GRADIENTRECTANGLEMASK_H
#define M_GRADIENTRECTANGLEMASK_H

#include "MaskBehavior.h"

class M_GradientRectangleMask : public MaskBehavior {
public:
	M_GradientRectangleMask() {};
	~M_GradientRectangleMask() {};
	float maskPattern(float maxFloat, int width, int height, int x, int y);
};
#endif
