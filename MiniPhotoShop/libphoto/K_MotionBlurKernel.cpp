#include "K_MotionBlurKernel.h"

K_MotionBlurKernel::K_MotionBlurKernel(int kernelSize, int direction)
{
  if (kernelSize%2 == 0)
  {
    kernelSize += 1;
  }

  m_kernelSize = kernelSize;
  m_direction = direction;

  makeKernel();
}

K_MotionBlurKernel::~K_MotionBlurKernel()
{
  delete[] m_kernel;
}

void K_MotionBlurKernel::makeKernel()
{
  int centerVal = m_kernelSize/2;
  float kernelValue;

  m_kernel = new float[m_kernelSize*m_kernelSize];

	for(int curX=0;curX < m_kernelSize; curX++)
  {
		for (int curY=0; curY < m_kernelSize; curY++)
    {
      switch(m_direction)
      {
        case 0:
          if(curX == centerVal)
          {
            kernelValue = 1.0;
          }
          else
          {
            kernelValue = 0;
          }
          break;
        case 1:
          if(curY == centerVal)
          {
            kernelValue = 1.0;
          }
          else
          {
            kernelValue = 0;
          }
          break;
        case 2:
          if(curX == curY)
          {
            kernelValue = 1.0;
          }
          else
          {
            kernelValue = 0;
          }
          break;
        case 3:
          if(curX == ((m_kernelSize-1)-curY))
          {
            kernelValue = 1.0;
          }
          else
          {
            kernelValue = 0;
          }
          break;
      }
			m_kernel[curX+(m_kernelSize*curY)]=kernelValue;
		}
	}
}
