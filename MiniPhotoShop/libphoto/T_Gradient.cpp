#include "Tool.h"
#include "T_Gradient.h"
#include "M_GradientRectangleMask.h"

T_Gradient::T_Gradient()
{
}
T_Gradient::T_Gradient(int* bufferHeight, int* bufferWidth)
{
	m_bufferHeight = bufferHeight;
	m_bufferWidth = bufferWidth;

	m_maxFloat = 0.75;
	m_brushBool = true;
	m_stampBool = false;
	m_kernelBool = false;
	m_luminanceBool= false;
	m_needTempCanvas = false;

	m_defaultWidth = 31;
	m_defaultHeight = 51;
	m_defaultMaskSize = 51;

	m_toolSize = 1.0;
	m_width = m_defaultWidth;
	m_height = m_defaultHeight;
	m_maskSize = m_defaultMaskSize;

	m_drawLineLimitFactor=3.5;

	setMaskBehavior(new M_GradientRectangleMask());
	makeMask();
}

T_Gradient::~T_Gradient()
{
}
