#ifndef K_EDGEDETECTKERNEL_H
#define K_EDGEDETECTKERNEL_H

#include "Kernel.h"

class K_EdgeDetectKernel : public Kernel
{
public:
  K_EdgeDetectKernel(int kernelSize);
  virtual ~K_EdgeDetectKernel();

  void makeKernel();
protected:

};

#endif
