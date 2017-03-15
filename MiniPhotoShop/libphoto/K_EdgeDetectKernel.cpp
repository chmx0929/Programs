#include "K_EdgeDetectKernel.h"

K_EdgeDetectKernel::K_EdgeDetectKernel(int kernelSize)
{
  m_kernelSize = kernelSize;

  makeKernel();
}

K_EdgeDetectKernel::~K_EdgeDetectKernel()
{
  delete[] m_kernel;
}

void K_EdgeDetectKernel::makeKernel()
{
  m_kernel = new float[m_kernelSize*m_kernelSize];

  for (int curX = 0; curX < m_kernelSize; curX++)
  {
    for (int curY = 0; curY < m_kernelSize; curY++)
    {
      m_kernel[curX+(m_kernelSize*curY)]=0;
    }
  }

  m_kernel[2+(m_kernelSize*2)] = 4.0;
  m_kernel[2+(m_kernelSize*0)] = -1.0;
  m_kernel[2+(m_kernelSize*1)] = -1.0;
  m_kernel[2+(m_kernelSize*3)] = -1.0;
  m_kernel[2+(m_kernelSize*4)] = -1.0;
}
