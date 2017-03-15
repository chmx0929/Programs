#include "Tool.h"
#include "T_Stamp.h"
#include "PixelBuffer.h"

T_Stamp::T_Stamp()
{
}

T_Stamp::T_Stamp(int* bufferHeight, int* bufferWidth)
{
	m_bufferHeight = bufferHeight;
	m_bufferWidth = bufferWidth;

	m_maxFloat = 1.0;

	m_brushBool = false;
	m_stampBool = true;
	m_kernelBool = false;
	m_luminanceBool= false;
	m_needTempCanvas = false;

	m_defaultWidth = 1; //Trivial values
	m_defaultHeight = 1;
	m_defaultMaskSize= 1;

	m_toolSize = 1.0;
	m_width = m_defaultWidth;
	m_height = m_defaultHeight;
	m_maskSize = m_defaultMaskSize;  // This is for interpolation, not really a mask here

	m_drawLineLimitFactor=128.0;

	// Stamp has no mask!
}

T_Stamp::~T_Stamp()
{
}

void T_Stamp::setStampBuffer(PixelBuffer* stamp) {
	m_stampBuffer=stamp;
	m_width = m_stampBuffer->getWidth();
	m_height = m_stampBuffer->getHeight();
	m_maskSize = m_stampBuffer->getWidth();
}

