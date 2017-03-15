#ifndef F_DITHER_H
#define F_DITHER_H

#include "Filter.h"

class F_Dither : public Filter
{
public:
  F_Dither(int parameter);
  virtual ~F_Dither();

  void applyFilter(PixelBuffer *canvas);
  ColorData find_closest_palette_color(ColorData input, float degree);

protected:

};

#endif
