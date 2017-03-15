#include "Tool.h"
#include "T_Eraser.h"
#include "M_FlatEllipseMask.h"

T_Eraser::T_Eraser()
{
}
T_Eraser::T_Eraser(int* bufferHeight, int* bufferWidth)
{
	m_bufferHeight = bufferHeight;
	m_bufferWidth = bufferWidth;

	m_maxFloat = 1.0;
	m_brushBool = true;
	m_stampBool = false;
	m_kernelBool = false;
	m_luminanceBool= false;
	m_needTempCanvas = false;

	m_defaultWidth = 21;
	m_defaultHeight = 21;
	m_defaultMaskSize= 21;

	m_toolSize = 1.0;
	m_width = m_defaultWidth;
	m_height = m_defaultHeight;
	m_maskSize = m_defaultMaskSize;

	m_drawLineLimitFactor=0.0; // zero means no limitation

	setMaskBehavior(new M_FlatEllipseMask());
	makeMask();
}

T_Eraser::~T_Eraser()
{
}
