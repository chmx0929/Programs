#include "F_Blur.h"
#include "K_BlurKernel.h"
#include "PixelBuffer.h"
#include "ColorData.h"

F_Blur::F_Blur(float parameter)
{
  int kernelSize = (int) parameter;

  if (kernelSize%2 == 0)
  {
    kernelSize += 1;
  }

  m_filterParameter.amountF = parameter;
  m_kernelSize = kernelSize;

  m_kernel = new K_BlurKernel(m_kernelSize);
}

F_Blur::~F_Blur()
{
  delete m_kernel;
}

void F_Blur::changeKernel(int kernelSize)
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

ColorData F_Blur::getBlurredColor(int canvasX, int canvasY)
{
  int distance = m_kernelSize/2;
  ColorData blurredColor;
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

  blurredColor = ColorData(red, green, blue);

  return blurredColor;
}

void F_Blur::applyFilter(PixelBuffer *canvas)
{
  ColorData newPixel;

  copyCanvas(canvas);

  for(int curX = 0; curX < canvas->getWidth(); curX++)
  {
    for(int curY = 0; curY < canvas->getHeight(); curY++)
    {
      newPixel = getBlurredColor(curX, curY);
      canvas->setPixel(curX, curY, newPixel);
    }
  }

  freeTempCanvas();
}

ColorData F_Blur::getModifiedColor(int x, int y) {
    return getBlurredColor(x, y);
}
