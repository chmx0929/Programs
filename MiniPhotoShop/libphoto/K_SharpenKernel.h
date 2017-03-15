#ifndef K_SHARPENKERNEL_H
#define K_SHARPENKERNEL_H

#include "Kernel.h"

class K_SharpenKernel : public Kernel
{
public:
  K_SharpenKernel(int kernelSize);
  virtual ~K_SharpenKernel();

  void makeKernel();
protected:

};

#endif
