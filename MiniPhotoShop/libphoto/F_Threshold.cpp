#include "F_Threshold.h"
#include "PixelBuffer.h"
#include "ColorData.h"



F_Threshold::F_Threshold(float parameter)
{
  m_filterParameter.amountF = parameter;
  m_filterParameter.amountI = 0;
}

F_Threshold::~F_Threshold()
{

}

void F_Threshold::applyFilter(PixelBuffer *canvas)
{
  float red;
  float green;
  float blue;
  ColorData curColor;
  ColorData newColor;


  for (int curX = 0; curX < canvas->getWidth(); curX++)
  {
    for (int curY = 0; curY < canvas->getHeight(); curY++)
    {
      curColor = canvas->getPixel(curX, curY);

      if (curColor.getRed() <= m_filterParameter.amountF)
      {
        red = 0.0;
      }
      else
      {
        red = 1.0;
      }

      if (curColor.getGreen() <= m_filterParameter.amountF)
      {
        green = 0.0;
      }
      else
      {
        green = 1.0;
      }

      if (curColor.getBlue() <= m_filterParameter.amountF)
      {
        blue = 0.0;
      }
      else
      {
        blue = 1.0;
      }

      newColor = ColorData(red, green, blue);

      canvas->setPixel(curX, curY, newColor);
    }
  }
}
