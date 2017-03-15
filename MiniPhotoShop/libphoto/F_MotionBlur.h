#ifndef F_MOTIONBLUR_H
#define F_MOTIONBLUR_H

#include "Filter.h"

class PixelBuffer;
class ColorData;

class F_MotionBlur : public Filter
{
public:
  F_MotionBlur(float parameter, int direction);
  virtual ~F_MotionBlur();
  /*
    enum UIMotionBlurDirections {
      DIR_N_S,
      DIR_E_W,
      DIR_NE_SW,
      DIR_NW_SE
  };
  */

  void changeKernel(int kernelSize);
  void applyFilter(PixelBuffer *canvas);

protected:
  ///This function is used as a helper function so we can use getModifiedColor() for applyFilter()
  ColorData getBlurredColor(int canvasX, int canvasY);
};

#endif
