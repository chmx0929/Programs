#include "F_Wallpaper.h"
#include "PixelBuffer.h"
#include "ColorData.h"

F_Wallpaper::F_Wallpaper()
{
}

F_Wallpaper::~F_Wallpaper()
{
}
void F_Wallpaper::applyFilter(PixelBuffer *canvas)
{
	if (m_filterParameter.wallpaper) {
		for(int curX = 0; curX < canvas->getWidth(); curX++)
		{
			for(int curY = 0; curY < canvas->getHeight(); curY++)
			{	

				canvas->setPixel(curX,curY,m_filterParameter.wallpaper->getPixel(curX % m_filterParameter.wallpaper->getWidth(), curY % m_filterParameter.wallpaper->getHeight()));
			}
		}
	}
}
