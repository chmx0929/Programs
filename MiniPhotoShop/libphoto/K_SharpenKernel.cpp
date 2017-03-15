#include "K_SharpenKernel.h"
#include <iostream>

K_SharpenKernel::K_SharpenKernel(int kernelSize)
{
  m_kernelSize = kernelSize;

  makeKernel();
}

K_SharpenKernel::~K_SharpenKernel()
{
  delete[] m_kernel;
}

void K_SharpenKernel::makeKernel()
{
  int centerVal = m_kernelSize/2;

  m_kernel = new float[m_kernelSize*m_kernelSize];

  for (int curX = 0; curX < m_kernelSize; curX++)
  {
    for (int curY = 0; curY < m_kernelSize; curY++)
    {
      m_kernel[curX+(m_kernelSize*curY)]=-1;
    }
  }

  m_kernel[centerVal+(m_kernelSize*centerVal)] = m_kernelSize*m_kernelSize*3;
}
