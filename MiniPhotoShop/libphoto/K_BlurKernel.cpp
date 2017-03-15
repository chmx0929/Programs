#include "K_BlurKernel.h"
#include <math.h>

K_BlurKernel::K_BlurKernel(int kernelSize)
{
  if (kernelSize%2 == 0)
  {
    kernelSize += 1;
  }

  m_kernelSize = kernelSize;

  makeKernel();
}

K_BlurKernel::~K_BlurKernel()
{
  delete[] m_kernel;
}

void K_BlurKernel::makeKernel()
{
  int radius = 1 + m_kernelSize/2;
  float distanceVal;//distance from kernel's center
  float kernelValue;

  m_kernel = new float[m_kernelSize*m_kernelSize];

	for(int curX=0;curX < m_kernelSize; curX++)
  {
		for (int curY=0; curY < m_kernelSize; curY++)
    {
      distanceVal = pow((curX-m_kernelSize)/2,2)/((float) pow(radius,2)) + pow((curY-m_kernelSize)/2,2)/((float) pow(radius,2));

      if(distanceVal < 1.0)
      {
        kernelValue = 1.0;
      }
      else
      {
        kernelValue = 0;
      }
			m_kernel[curX+(m_kernelSize*curY)]=kernelValue;;
		}
	}
}
