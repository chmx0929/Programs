#ifndef F_BLUR_H
#define F_BLUR_H

#include "Filter.h"

class PixelBuffer;
class ColorData;

class F_Blur : public Filter
{
public:
  F_Blur(float parameter);
  virtual ~F_Blur();

  void changeKernel(int kernelSize);
  void applyFilter(PixelBuffer *canvas);

  ///This function is needed so we can use a filter as a brush tool.
  ColorData getModifiedColor(int x, int y);

protected:
  ColorData getBlurredColor(int canvasX, int canvasY);
};

#endif
