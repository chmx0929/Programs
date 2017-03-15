#ifndef F_QUANTIZE_H
#define F_QUANTIZE_H

#include "Filter.h"

class F_Quantize : public Filter
{
public:
  F_Quantize(int parameter);
  virtual ~F_Quantize();

  void applyFilter(PixelBuffer *canvas);

protected:

};

#endif
