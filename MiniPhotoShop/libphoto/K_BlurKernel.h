#ifndef K_BLURKERNEL_H
#define K_BLURKERNEL_H

#include "Kernel.h"

class K_BlurKernel : public Kernel
{
public:
  K_BlurKernel(int kernelSize);
  virtual ~K_BlurKernel();

  void makeKernel();
protected:

};

#endif
