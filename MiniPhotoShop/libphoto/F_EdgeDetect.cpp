#include "F_EdgeDetect.h"
#include "K_EdgeDetectKernel.h"
#include "PixelBuffer.h"
#include "ColorData.h"

F_EdgeDetect::F_EdgeDetect()
{
  m_kernelSize = 5;

  m_kernel = new K_EdgeDetectKernel(m_kernelSize);
}

F_EdgeDetect::~F_EdgeDetect()
{
  delete m_kernel;
}

ColorData F_EdgeDetect::getColor(int canvasX, int canvasY)
{
  int distance = m_kernelSize/2;
  ColorData newColor;
  ColorData curPixel;
  float red = 0;
  float green = 0;
  float blue = 0;
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
  			}
      }
    }
  }

  newColor = ColorData(red, green, blue);

  return newColor;
}

void F_EdgeDetect::applyFilter(PixelBuffer *canvas)
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
