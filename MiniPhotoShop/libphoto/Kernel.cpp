#include "Kernel.h"

Kernel::Kernel()
{

}

Kernel::~Kernel()
{
  delete[] m_kernel;
}

void Kernel::setKernelParam(int kernelSize, int direction)
{
  if (kernelSize%2 == 0)
  {
    kernelSize += 1;
  }
  m_kernelSize = kernelSize;
  m_direction = direction;
}

float Kernel::getKernelVal(int x, int y)
{
  return m_kernel[x+(m_kernelSize*y)];
}

void Kernel::freeKernel()
{
  delete[] m_kernel;
}
