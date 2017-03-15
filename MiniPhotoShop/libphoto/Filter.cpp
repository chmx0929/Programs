#include "Filter.h"
#include "PixelBuffer.h"
#include "ColorData.h"
#include <stdlib.h>

Filter::Filter()
{

}

Filter::~Filter()
{

}


void Filter::setIntParameter(const int parameter) {
  m_filterParameter.amountI = parameter;
}

void Filter::setFloatParameter(const float parameter) {
  m_filterParameter.amountF = parameter;
}

void Filter::setFloatSecondaryParameter(const float parameter) {
  m_filterParameter.amountF2 = parameter;
}

void Filter::setColors(const float red, const float green, const float blue){
  m_filterParameter.red = red;
  m_filterParameter.green = green;
  m_filterParameter.blue = blue;

}

void Filter::setWallpaper(PixelBuffer* wallpaper) {
  m_filterParameter.wallpaper=wallpaper;
}

void Filter::copyCanvas(PixelBuffer* canvas)
{
  m_tempCanvas = new PixelBuffer(canvas->getWidth(), canvas->getHeight(), canvas->getBackgroundColor());

	m_tempCanvas->copyPixelBuffer(canvas, m_tempCanvas);
}

void Filter::freeTempCanvas()
{
	free(m_tempCanvas);
}


void Filter::changeKernel(int kernelSize)
{
  if (kernelSize%2 == 0)
  {
    kernelSize += 1;
  }

  m_kernelSize = kernelSize;
}

bool Filter::paramHasChanged()
{
  if ((m_filterParameter.amountI == m_filterParameterTemp.amountI) &&\
      (m_filterParameter.amountF == m_filterParameterTemp.amountF) &&\
      (m_filterParameter.amountF2 == m_filterParameterTemp.amountF2) &&\
      (m_filterParameter.red == m_filterParameterTemp.red) &&\
      (m_filterParameter.green == m_filterParameterTemp.green) &&\
      (m_filterParameter.blue == m_filterParameterTemp.blue) &&\
      (m_filterParameter.wallpaper == m_filterParameterTemp.wallpaper)) {
    return false;
  }  
  else {
    m_filterParameterTemp=m_filterParameter;
    return true;
  }
}

ColorData Filter::getModifiedColor(int x, int y) // virtual, used for blur tool
 { 
    return ColorData(0,0,0);
}
