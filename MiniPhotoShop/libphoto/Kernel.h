#ifndef KERNEL_H
#define KERNEL_H

/**
The kernel class is required for filters that are categorized as convolution filters
*/
class Kernel
{
public:
  Kernel();
  virtual ~Kernel();

  ///this function must be pure virtual because each filter will be different
  virtual void makeKernel() = 0;
  void setKernelParam(int kernelSize, int direction);
  float getKernelVal(int x, int y);
  void freeKernel();
protected:
  int m_kernelSize;
  ///this member function lets the motionblur know which direction to blur
  int m_direction;
  float* m_kernel;//array of floats
};

#endif
