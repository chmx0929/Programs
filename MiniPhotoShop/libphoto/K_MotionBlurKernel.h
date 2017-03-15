#ifndef K_MOTIONBLURKERNEL_H
#define K_MOTIONBLURKERNEL_H

#include "Kernel.h"

class K_MotionBlurKernel : public Kernel
{
public:
  K_MotionBlurKernel(int kernelSize, int direction);
  virtual ~K_MotionBlurKernel();

  void makeKernel();
protected:
};

#endif
