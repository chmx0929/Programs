#ifndef F_EDGEDETECT_H
#define F_EDGEDETECT_H

#include "Filter.h"

class F_EdgeDetect : public Filter
{
public:
  F_EdgeDetect();
  virtual ~F_EdgeDetect();

  void applyFilter(PixelBuffer *canvas);
protected:
  ColorData getColor(int canvasX, int canvasY);
};

#endif
