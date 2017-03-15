#include "Tool.h"
#include "T_Highlighter.h"
#include "M_FlatRectangleMask.h"

T_Highlighter::T_Highlighter()
{
}
T_Highlighter::T_Highlighter(int* bufferHeight, int* bufferWidth)
{
	m_bufferHeight = bufferHeight;
	m_bufferWidth = bufferWidth;

	m_maxFloat = 0.4;
	m_brushBool = true;
	m_stampBool = false;
	m_kernelBool = false;
	m_luminanceBool= true;
	m_needTempCanvas = true;

	m_defaultWidth = 5;
	m_defaultHeight = 15;
	m_defaultMaskSize = 15;

	m_toolSize = 1.0;
	m_width = m_defaultWidth;
	m_height = m_defaultHeight;
	m_maskSize = m_defaultMaskSize;

	m_drawLineLimitFactor=0.0;

	setMaskBehavior(new M_FlatRectangleMask());
	makeMask();
}

T_Highlighter::~T_Highlighter()
{
}
