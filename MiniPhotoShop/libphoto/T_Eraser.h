#ifndef T_ERASER_H
#define T_ERASER_H

#include "Tool.h"

class T_Eraser : public Tool
{
	public:
		T_Eraser();
		T_Eraser(int* bufferHeight, int* bufferWidth);
		virtual ~T_Eraser();

	private:

	protected:
};

#endif
