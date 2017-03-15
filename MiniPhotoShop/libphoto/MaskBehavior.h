//
// MaskBehavior.h
//

#ifndef MASKBEHAVIOR_H
#define MASKBEHAVIOR_H

/**
* This class acts as the parent controller for the behavioral strategy pattern that ultimately controls the construction of masks. That's a mouthful, but
8 at its core each mask behavior simply stores a general function for making a 1D array version of a 2D mask.
*/
class MaskBehavior {
public:
	MaskBehavior() {};
 	virtual ~MaskBehavior() {};
	/// This mask pattern, in the sub classes, stores the mathatical methods to generate different shapes, which are used to make masks for tool subclasses
	virtual float maskPattern(float maxFloat, int width, int height, int x, int y) = 0;
};
#endif
