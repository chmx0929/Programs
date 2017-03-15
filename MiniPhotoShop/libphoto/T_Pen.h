#ifndef T_PEN_H
#define T_PEN_H

#include "Tool.h"

class T_Pen : public Tool
{
public:
	T_Pen();
	T_Pen(int* bufferHeight, int* bufferWidth);
	virtual ~T_Pen();

private:
protected:
};

#endif
