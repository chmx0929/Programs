
#include "Tool.h"
#include "PixelBuffer.h"
#include "ColorData.h"
#include "MaskBehavior.h"
#include "F_Blur.h"
#include <stdlib.h>
#include <math.h>

Tool::Tool(){
	m_maskBehavior=0;
}

Tool::~Tool()
{
	delete []m_maskArray;
	delete m_maskBehavior;
	if (m_stampBuffer) {
		delete m_stampBuffer;
	}
	if (m_filter) {
		delete m_filter;
	}
}

//makes a new array of intensities for colors
void Tool::makeMask() {
	m_maskArray = new float[(int) m_width*m_height]; //1-D representation of square array, w size dictated by the largest measurement
	float intensityValue;
	for(int curY=0;curY < m_height; curY++){
		for (int curX=0; curX < m_width; curX++){
			intensityValue=m_maskBehavior->maskPattern(m_maxFloat, m_width, m_height, curX-m_width/2, curY-m_height/2); // gets intensity value related to i,j's position
			setIntensity(curX,curY,intensityValue);
		}
	}
}

void Tool::scaleMask(float scaledSize) {
	delete []m_maskArray;
	m_width = normalizeSize((int) (m_defaultWidth * scaledSize));
	m_height = normalizeSize((int) (m_defaultHeight * scaledSize));
	m_maskSize = normalizeSize((int) (m_defaultMaskSize * scaledSize));
	m_toolSize = scaledSize;
	makeMask();
}

int Tool::normalizeSize(int dimensionSize) {
	if(dimensionSize % 2) {
		return dimensionSize;
	} else {
		return (dimensionSize+1); //rounds up so that dimensions are always odd numbers
	}
}

int Tool::getDefaultMaskSize()
{
	return m_defaultMaskSize;
}

void Tool::setIntensity(int x, int y,float intensityValue) {
	m_maskArray[x+(m_width*y)]=intensityValue;
}
float Tool::getIntensity(int x, int y) {
	return m_maskArray[x+(m_width*y)];
}

void Tool::setMaskBehavior(MaskBehavior* behavior) {
    if (m_maskBehavior != 0)
        delete m_maskBehavior;
    m_maskBehavior = behavior;
}

float Tool::interpretLuminanceContribution(int x, int y, PixelBuffer* canvas) {
	if(m_luminanceBool) return canvas->getPixel(x, y).getLuminance();
	else return 1.0;
}

int Tool::interpretDrawLineLimitFactor() {
	if(m_drawLineLimitFactor<=0.0) return 1;
	else return (int) (m_drawLineLimitFactor * m_maskSize);
}

//draws the tool onto the Canvas
void Tool::draw(int x, int y, ColorData curColor, PixelBuffer* canvas){
	ColorData curPixel, modPixel;
	float intensityValue = 0;
	if (m_filter && m_kernelBool) {
		m_filter->copyCanvas(canvas);
	}
	for(int curY=0; curY< m_height; curY++) {
		for(int curX=0; curX< m_width; curX++) {
			int xVal= x + (curX - m_width/2);
			int yVal= y + (curY - m_height/2);
			if ((xVal >= 0) && (xVal < *m_bufferWidth) && (yVal >= 0) && (yVal < *m_bufferHeight)) {
				if (m_needTempCanvas && !m_kernelBool) {
					curPixel = m_tempCanvas->getPixel(xVal,yVal);
				}
				else {
					curPixel = canvas->getPixel(xVal,yVal);
				}
				if (m_stampBuffer && m_stampBool) {
					modPixel=m_stampBuffer->getPixel(curX, curY);
					intensityValue = m_maxFloat * modPixel.getAlpha();
					canvas->setPixel(xVal,yVal,m_stampBuffer->getPixel(curX, curY)*intensityValue  + curPixel*(1.0-intensityValue));
				}
				else if (m_filter && m_kernelBool) {
					intensityValue = getIntensity(curX, curY) *interpretLuminanceContribution(xVal, yVal, m_tempCanvas);
					modPixel = m_filter->getModifiedColor(xVal, yVal);
					canvas->setPixel(xVal,yVal,modPixel*intensityValue + curPixel*(1.0-intensityValue));
				}
				else if (m_brushBool){
					intensityValue = getIntensity(curX, curY) * interpretLuminanceContribution(xVal, yVal, m_tempCanvas);
					canvas->setPixel(xVal,yVal,curColor*intensityValue + curPixel*(1.0-intensityValue));
				}
				else {
					break;
				}
			}
		}
	}
	if (m_filter && m_kernelBool) {
		m_filter->freeTempCanvas();
	}
}

//interpolates the points between the previous x and y with the current x and y
//then draw to the Canvas to draw a more complete line
void Tool::drawLine(int orig_x, int orig_y, int cur_x, int cur_y, ColorData curColor, PixelBuffer* canvas)
{
	int xVal = abs(orig_x - cur_x);
 	int yVal = abs(orig_y - cur_y);
 	int n = (int)fmax(xVal, yVal);

  for(int i = 1; i <= n; i+= interpretDrawLineLimitFactor())
  {
  	draw((orig_x + round((cur_x-orig_x)*i/n)),
  		 (orig_y + round((cur_y-orig_y)*i/n)),
  		 curColor, canvas);
  }
}

void Tool::copyCanvas(PixelBuffer* canvas)
{
	m_tempCanvas = new PixelBuffer(*m_bufferWidth, *m_bufferHeight, canvas->getBackgroundColor());

	m_tempCanvas->copyPixelBuffer(canvas, m_tempCanvas);
}


void Tool::freeTempCanvas()
{
	free(m_tempCanvas);
}


void Tool::setStampBuffer(PixelBuffer* stamp) {
}
