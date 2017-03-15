#include "F_Dither.h"
#include "PixelBuffer.h"
#include "ColorData.h"

#include <iostream>
//#include <math.h>

F_Dither::F_Dither(int parameter)
{
	m_filterParameter.amountF = (float)parameter;
	m_filterParameter.amountI = 0;
}

F_Dither::~F_Dither()
{

}

ColorData F_Dither::find_closest_palette_color(ColorData input, float degree)
{
	//std::cout << input.getRed() << input.getGreen() << input.getBlue() << std::endl;
	return input.ColorDataFloor(input, degree);
	//std::cout << out.getRed() << out.getGreen() << out.getBlue() << std::endl;
}

void F_Dither::applyFilter(PixelBuffer *canvas)
{
	float d1 = 0.4375;
	float d2 = 0.1875;
	float d3 = 0.3125;
	float d4 = 0.0625;

	//std::cout << m_filterParameter.amountF << std::endl;
	for(int curY = 0; curY < canvas->getHeight()-1; curY++)
	{
		for(int curX = 1; curX < canvas->getWidth()-1; curX++)
		{
			ColorData currColor = canvas->getPixel(curX, curY);
			ColorData newColor = find_closest_palette_color(currColor, m_filterParameter.amountF);
			canvas->setPixel(curX, curY, newColor);
			ColorData quant_error = currColor - newColor; // don't understand

			ColorData temp1 = canvas->getPixel(curX+1, curY  ) + (quant_error * d1);
			ColorData temp2 = canvas->getPixel(curX-1, curY+1) + (quant_error * d2);
			ColorData temp3 = canvas->getPixel(curX  , curY+1) + (quant_error * d3);
			ColorData temp4 = canvas->getPixel(curX+1, curY+1) + (quant_error * d4);
			canvas->setPixel(curX+1, curY  , temp1);
			canvas->setPixel(curX-1, curY+1, temp2);
			canvas->setPixel(curX  , curY+1, temp3);
			canvas->setPixel(curX+1, curY+1, temp4);
		}
	}
}
