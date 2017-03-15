//
//  FlatRectangleMask.cpp
//

#include "M_FlatRectangleMask.h"
#include <math.h>

float M_FlatRectangleMask::maskPattern(float maxFloat, int width, int height, int x, int y) {

	int midWidth = width/2;
	int midHeight = height/2;

	float intensityVal = fmax(fabs((float) x) / midWidth, fabs((float) y) / midHeight);
	if(intensityVal <= 1.0) return maxFloat;
	else return 0;
}
