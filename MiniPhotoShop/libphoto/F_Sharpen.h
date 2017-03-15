#ifndef F_SHARPEN_H
#define F_SHARPEN_H

#include "Filter.h"

class F_Sharpen : public Filter
{
public:
  F_Sharpen(float parameter);
  virtual ~F_Sharpen();

  void changeKernel(int kernelSize);
  void applyFilter(PixelBuffer *canvas);
protected:
  ColorData getColor(int canvasX, int canvasY);
};

#endif
