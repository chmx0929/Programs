//
//  GradientRectangleMask.cpp
//

#include "M_GradientRectangleMask.h"
#include <math.h>

float M_GradientRectangleMask::maskPattern(float maxFloat, int width, int height, int x, int y) {

	int xViaCorner = x + width/2;
	int yViaCorner = -y + height/2;
	float intensityVal;

	if(xViaCorner>=0 && xViaCorner<width && yViaCorner>=0 && yViaCorner<height) {
		intensityVal =  0.5*(xViaCorner/((float) width)) + 0.5*(yViaCorner/((float) height));
		return maxFloat * intensityVal;
	} else {
		return 0;
	}
}
