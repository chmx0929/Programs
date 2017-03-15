#include "F_Saturate.h"
#include "PixelBuffer.h"
#include "ColorData.h"

#include <math.h>

F_Saturate::F_Saturate(float parameter)
{
  m_filterParameter.amountF = parameter;
  m_filterParameter.amountI = 0;
}

F_Saturate::~F_Saturate()
{

}

void F_Saturate::applyFilter(PixelBuffer *canvas)
{
	for(int curX = 0; curX < canvas->getWidth(); curX++)
	{
		for(int curY = 0; curY < canvas->getHeight(); curY++)
		{
			ColorData curColor = canvas->getPixel(curX, curY);
			float P = sqrt((curColor.getRed() * curColor.getRed() * 0.2126) +
						   (curColor.getGreen() * curColor.getGreen() * 0.7152) +
						   (curColor.getBlue() * curColor.getBlue() * 0.0722));
			float newR = P + (curColor.getRed() - P) * m_filterParameter.amountF;
			float newG = P + (curColor.getGreen() - P) * m_filterParameter.amountF;
			float newB = P + (curColor.getBlue() - P) * m_filterParameter.amountF;

			canvas->setPixel(curX, curY, ColorData(newR, newG, newB));
		}
	}
}
