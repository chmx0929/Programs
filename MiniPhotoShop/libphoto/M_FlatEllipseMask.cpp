//
//  FlatEllipseMask.cpp
//

#include "M_FlatEllipseMask.h"
#include <math.h>

float M_FlatEllipseMask::maskPattern(float maxFloat, int width, int height, int x, int y) {
	int midWidth = width/2;
	int midHeight = height/2;

	float intensityVal = pow(x,2)/((float) pow(midWidth,2)) + pow(y,2)/((float) pow(midHeight,2));
	if(intensityVal<=1) return maxFloat;
	else return 0;
}
