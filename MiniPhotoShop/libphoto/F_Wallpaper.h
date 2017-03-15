#ifndef F_WALLPAPER_H
#define F_WALLPAPER_H

#include "Filter.h"

/**
* Wallpaper is the basic filter on top of whitch chroma key was designed. It uses modulo arithmatic to tile a pixel buffer, saved to the stamp, across the canvas
*/
class F_Wallpaper : public Filter
{
public:
  F_Wallpaper();
  virtual ~F_Wallpaper();

  void applyFilter(PixelBuffer *canvas);

protected:

};

#endif
