#ifndef FILTER_H
#define FILTER_H


class PixelBuffer;
class ColorData;
class Kernel;

/**
The filters inheriting from this class may have different parameters, therefore
we need to have different functions that can change the parameters when changing the kernel. Not all filters will have a kernel.
*/
class Filter
{
public:
  Filter();
  virtual ~Filter();

  ///applyFilter() has to be virtual because some of the Filters may be convultion filters and will have a different method to apply to the canvas.
  virtual void applyFilter(PixelBuffer *canvas) = 0;

  void setIntParameter(const int parameter);
  void setFloatParameter(const float parameter);
  void setFloatSecondaryParameter(const float parameter);
  ///This sets the parameters required for the Channel filter.
  void setColors(const float red, const float green, const float blue);
  void setWallpaper(PixelBuffer* wallpaper);

  void copyCanvas(PixelBuffer* canvas);
  void freeTempCanvas();

  ///changeKernel() has to be virtual because convolution filters may have different parameters
  virtual void changeKernel(int kernelSize);

  bool paramHasChanged();
  virtual ColorData getModifiedColor(int x, int y);

protected:
  PixelBuffer* m_tempCanvas; //pointer to a PixelBuffer

  ///This points to a kernel
  Kernel *m_kernel;//pointer to a Kernel

  int m_kernelSize;


  /**
  Depending on what filter you may use, you may need a parameter. In this class we have a structure of parameters.
  */
  struct params {
      int amountI;
      float amountF;
      float amountF2;
      float red;
      float green;
      float blue;
      PixelBuffer* wallpaper;
  } m_filterParameter, m_filterParameterTemp;
};

#endif
