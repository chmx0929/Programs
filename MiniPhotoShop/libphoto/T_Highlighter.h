#ifndef T_HIGHLIGHTER_H
#define T_HIGHLIGHTER_H

#include "Tool.h"

class T_Highlighter : public Tool
{
public:
	T_Highlighter();
	T_Highlighter(int* bufferHeight, int* bufferWidth);
	virtual ~T_Highlighter();

	/*
	void draw(int x,int y, ColorData curColor, PixelBuffer* canvas);
	void drawLine(int orig_x, int orig_y, int dest_x, int dest_y, ColorData curColor, PixelBuffer* canvas);
	*/
private:

protected:
};

#endif
