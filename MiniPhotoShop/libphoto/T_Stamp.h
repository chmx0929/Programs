#ifndef T_STAMP_H
#define T_STAMP_H

#include "Tool.h"

class T_Stamp : public Tool
{
public:
	T_Stamp();
	T_Stamp(int* bufferHeight, int* bufferWidth);
	virtual ~T_Stamp();

	void setStampBuffer(PixelBuffer* stamp);

private:
protected:
};

#endif
