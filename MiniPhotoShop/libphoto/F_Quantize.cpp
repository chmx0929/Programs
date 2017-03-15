#include "F_Quantize.h"
#include "PixelBuffer.h"
#include "ColorData.h"

#include <stdlib.h>

F_Quantize::F_Quantize(int parameter)
{
  m_filterParameter.amountF = 0;
  m_filterParameter.amountI = parameter;
}

F_Quantize::~F_Quantize()
{

}

void F_Quantize::applyFilter(PixelBuffer *canvas)
{
  float* colorBin = new float[m_filterParameter.amountI];
  float colorDiff = (1.0/(m_filterParameter.amountI-1.0));
  ColorData curColor;
  int curRedDiff;
  float closestRed;
  int curGreenDiff;
  float closestGreen;
  int curBlueDiff;
  float closestBlue;
  int curRed;
  int curGreen;
  int curBlue;

  //initialize bin
  for(int curBin = 0; curBin < m_filterParameter.amountI; curBin++)
  {
    colorBin[curBin] = colorDiff*curBin;
  }

  for(int curX = 0; curX < canvas->getWidth(); curX++)
  {
    for(int curY = 0; curY < canvas->getHeight(); curY++)
    {
      curColor = canvas->getPixel(curX, curY);
      curRedDiff = 1000;
      curGreenDiff = 1000;
      curBlueDiff = 1000;
      curRed = curColor.getRed()*1000;
      curGreen = curColor.getGreen()*1000;
      curBlue = curColor.getBlue()*1000;

      //get Quantized colors
      for(int curBin = 0; curBin < m_filterParameter.amountI; curBin++)
      {
        if(abs(curRed-colorBin[curBin]*1000) < curRedDiff)
        {
          curRedDiff = abs(curRed-colorBin[curBin]*1000);
          closestRed = colorBin[curBin];
        }
        if(abs(curGreen-colorBin[curBin]*1000) < curGreenDiff)
        {
          curGreenDiff = abs(curGreen-colorBin[curBin]*1000);
          closestGreen = colorBin[curBin];
        }
        if(abs(curBlue-colorBin[curBin]*1000) < curBlueDiff)
        {
          curBlueDiff = abs(curBlue-colorBin[curBin]*1000);
          closestBlue = colorBin[curBin];
        }
      }

      canvas->setPixel(curX, curY, ColorData(closestRed, closestGreen, closestBlue));
    }
  }
}
