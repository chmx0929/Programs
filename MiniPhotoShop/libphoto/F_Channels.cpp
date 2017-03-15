#include "F_Channels.h"
#include "PixelBuffer.h"
#include "ColorData.h"

F_Channels::F_Channels(float red, float green, float blue)
{
  m_filterParameter.red = red;
  m_filterParameter.green = green;
  m_filterParameter.blue = blue;
}

F_Channels::~F_Channels()
{

}

void F_Channels::applyFilter(PixelBuffer *canvas)
{
  ColorData curColor;
  float red;
  float green;
  float blue;

  for(int curX = 0; curX < canvas->getWidth(); curX++)
  {
    for (int curY = 0; curY < canvas->getHeight(); curY++)
    {
      curColor = canvas->getPixel(curX, curY);
      red = curColor.getRed() * m_filterParameter.red;
      green = curColor.getGreen() * m_filterParameter.green;
      blue = curColor.getBlue() * m_filterParameter.blue;

      canvas->setPixel(curX, curY, ColorData(red, green, blue));
    }
  }
}
