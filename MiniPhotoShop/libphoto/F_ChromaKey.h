#ifndef F_CHROMAKEY_H
#define F_CHROMAKEY_H

#include "Filter.h"
/**
* The Chroma key filter is used to select a range of similar colors on the canvas and replace them with a wallpapered version of the saved stamp image.
*
* The mathmatics of selecting a color by chroma value is somewhat involved, but a very good summary can be found on the corresponding wikipedia page.
* In a nutshell, the eucliean chroma distance (using the YCrCb colorspace) between the selected color and the current pixel is used to determine if a pixel
* is affected. The distance is compared with a max distance derived from the fudge factor parameter. If the distance is smaller than the max distance, the pixel is replaced.
*
* To help smooth out the edges, we create an iterpolation factor for colors just beyond the max distance, limited by the interpolation factor. Up to this point
* square roots and divsion are avoided for speed, but to calculate this factor it is unavaiodable. 
*/
class F_ChromaKey : public Filter
{
public:
  F_ChromaKey(float parameter, float secondary_parameter, float red, float green, float blue);
  virtual ~F_ChromaKey();

  void applyFilter(PixelBuffer *canvas);

protected:

};

#endif
