#ifndef F_THRESHOLD_H
#define F_THRESHOLD_H

#include "Filter.h"

class F_Threshold: public Filter
{
public:
  F_Threshold(float parameter);
  virtual ~F_Threshold();

  void applyFilter(PixelBuffer *canvas);

protected:

};

#endif
