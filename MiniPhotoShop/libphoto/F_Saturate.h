#ifndef F_SATURATE_H
#define F_SATURATE_H

#include "Filter.h"

class F_Saturate : public Filter
{
public:
  F_Saturate(float parameter);
  virtual ~F_Saturate();

  void applyFilter(PixelBuffer *canvas);

protected:

};

#endif
