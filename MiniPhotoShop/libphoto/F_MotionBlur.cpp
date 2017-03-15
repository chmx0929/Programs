#include "F_MotionBlur.h"
#include "K_MotionBlurKernel.h"
#include "PixelBuffer.h"
#include "ColorData.h"
#include <assert.h>

F_MotionBlur::F_MotionBlur(float parameter, int direction)
{
  int kernelSize = (int) parameter;

  if (kernelSize%2 == 0)
  {
    kernelSize += 1;
  }
  m_filterParameter.amountF = parameter;
  m_filterParameter.amountI = direction;
  m_kernelSize = kernelSize;

  m_kernel = new K_MotionBlurKernel(m_kernelSize, m_filterParameter.amountI);
}

F_MotionBlur::~F_MotionBlur()
{
  delete m_kernel;
}

void F_MotionBlur::changeKernel(int kernelSize)
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

ColorData F_MotionBlur::getBlurredColor(int canvasX, int canvasY)
{
  int distance = m_kernelSize/2;
  ColorData blurredColor;
  ColorData curPixel;
  float red = 0;
  float green = 0;
  float blue = 0;
  float colorFactor = 0;
  int curX;
  int curY;
  float kernalVal;
  assert(m_filterParameter.amountI >= 0 && m_filterParameter.amountI <= 3);
  switch(m_filterParameter.amountI)
  {
    case 0:// N/S
      for(curY = 0; curY < m_kernelSize; curY++)
      {
        curX = distance;
        int xVal= canvasX + (curX - distance);
        int yVal= canvasY + (curY - distance);

        if ((xVal >= 0) && (xVal < m_tempCanvas->getWidth()) && (yVal >= 0) && (yVal < m_tempCanvas->getHeight()))
        {
            curPixel = m_tempCanvas->getPixel(xVal, yVal);
            kernalVal = m_kernel->getKernelVal(curX, curY);
            red += kernalVal * curPixel.getRed();
            green += kernalVal * curPixel.getGreen();
            blue += kernalVal * curPixel.getBlue();
            colorFactor += kernalVal;
        }
      }
      break;
    case 1:// E/W
      for(curX = 0; curX < m_kernelSize; curX++)
      {
        curY = distance;
        int xVal= canvasX + (curX - distance);
        int yVal= canvasY + (curY - distance);

        if ((xVal >= 0) && (xVal < m_tempCanvas->getWidth()) && (yVal >= 0) && (yVal < m_tempCanvas->getHeight()))
        {
            curPixel = m_tempCanvas->getPixel(xVal, yVal);
            kernalVal = m_kernel->getKernelVal(curX, curY);
            red += kernalVal * curPixel.getRed();
            green += kernalVal * curPixel.getGreen();
            blue += kernalVal * curPixel.getBlue();
            colorFactor += kernalVal;
        }
      }
      break;
    case 2:// NE/SW
      for(curX = 0; curX < m_kernelSize; curX++)
      {
        curY = curX;
        int xVal= canvasX + (curX - distance);
        int yVal= canvasY + (curY - distance);

        if ((xVal >= 0) && (xVal < m_tempCanvas->getWidth()) && (yVal >= 0) && (yVal < m_tempCanvas->getHeight()))
        {
            curPixel = m_tempCanvas->getPixel(xVal, yVal);
            kernalVal = m_kernel->getKernelVal(curX, curY);
            red += kernalVal * curPixel.getRed();
            green += kernalVal * curPixel.getGreen();
            blue += kernalVal * curPixel.getBlue();
            colorFactor += kernalVal;
        }
      }
      break;
    case 3:// NW/SE
      for(curX = 0; curX < m_kernelSize; curX++)
      {
        curY = m_kernelSize - curX - 1;
        int xVal= canvasX + (curX - distance);
        int yVal= canvasY + (curY - distance);

        if ((xVal >= 0) && (xVal < m_tempCanvas->getWidth()) && (yVal >= 0) && (yVal < m_tempCanvas->getHeight()))
        {
            curPixel = m_tempCanvas->getPixel(xVal, yVal);
            kernalVal = m_kernel->getKernelVal(curX, curY);
            red += kernalVal * curPixel.getRed();
            green += kernalVal * curPixel.getGreen();
            blue += kernalVal * curPixel.getBlue();
            colorFactor += kernalVal;
        }
      }
      break;
    default:
      for(curX = 0; curX < m_kernelSize; curX++)
      {
        for(curY = 0; curY < m_kernelSize; curY++)
        {
          int xVal= canvasX + (curX - distance);
          int yVal= canvasY + (curY - distance);

          if ((xVal >= 0) && (xVal < m_tempCanvas->getWidth()) && (yVal >= 0) && (yVal < m_tempCanvas->getHeight()))
          {
              curPixel = m_tempCanvas->getPixel(xVal, yVal);
              kernalVal = m_kernel->getKernelVal(curX, curY);
              red += kernalVal * curPixel.getRed();
              green += kernalVal * curPixel.getGreen();
              blue += kernalVal * curPixel.getBlue();
              colorFactor += kernalVal;
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

void F_MotionBlur::applyFilter(PixelBuffer *canvas)
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
