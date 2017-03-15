#include "F_Sharpen.h"
#include "K_SharpenKernel.h"
#include "PixelBuffer.h"
#include "ColorData.h"

#include <cmath>

F_Sharpen::F_Sharpen(float parameter)
{
  int kernelSize = (int) parameter;

  if (kernelSize%2 == 0)
  {
    kernelSize += 1;
  }

  m_filterParameter.amountF = parameter;
  m_kernelSize = kernelSize;

  m_kernel = new K_SharpenKernel(m_kernelSize);
}

F_Sharpen::~F_Sharpen()
{
  delete m_kernel;
}

void F_Sharpen::changeKernel(int kernelSize)
{
  if (kernelSize%2 == 0)
  {
    kernelSize += 1;
  }

  m_kernelSize = kernelSize;

  m_kernel->setKernelParam(kernelSize, m_filterParameter.amountI);
  m_kernel->freeKernel();
  m_kernel->makeKernel();
}

ColorData F_Sharpen::getColor(int canvasX, int canvasY)
{
  int distance = m_kernelSize/2;
  ColorData newColor;
  ColorData curPixel;
  float red = 0;
  float green = 0;
  float blue = 0;
  float colorFactor = 0;
  float kernelValue;

  for(int curX = 0; curX < m_kernelSize; curX++)
  {
    for(int curY = 0; curY < m_kernelSize; curY++)
    {
      int xVal= canvasX + (curX - distance);
			int yVal= canvasY + (curY - distance);
      kernelValue = m_kernel->getKernelVal(curX, curY);

      if (kernelValue != 0)
      {
  			if ((xVal >= 0) && (xVal < m_tempCanvas->getWidth()) && (yVal >= 0) && (yVal < m_tempCanvas->getHeight()))
        {
          curPixel = m_tempCanvas->getPixel(xVal, yVal);
  				red += kernelValue * curPixel.getRed();
          green += kernelValue * curPixel.getGreen();
          blue += kernelValue * curPixel.getBlue();
          colorFactor += kernelValue;
  			}
      }
    }
  }

  red /= colorFactor;
  green /= colorFactor;
  blue /= colorFactor;

  newColor = ColorData(red, green, blue);

  return newColor;
}

void F_Sharpen::applyFilter(PixelBuffer *canvas)
{
  ColorData newPixel;

  copyCanvas(canvas);

  for(int curX = 0; curX < canvas->getWidth(); curX++)
  {
    for(int curY = 0; curY < canvas->getHeight(); curY++)
    {
      newPixel = getColor(curX, curY);
      canvas->setPixel(curX, curY, newPixel);
    }
  }

  freeTempCanvas();
}
