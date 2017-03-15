#ifndef F_CHANNELS_H
#define F_CHANNELS_H

#include "Filter.h"

class F_Channels : public Filter
{
public:
  F_Channels(float red, float green, float blue);
  virtual ~F_Channels();

  void applyFilter(PixelBuffer *canvas);
protected:
};

#endif
