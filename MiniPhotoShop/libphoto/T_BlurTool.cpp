#include "Tool.h"
#include "T_BlurTool.h"
#include "M_FalloffEllipseMask.h"
#include "Filter.h"
#include "F_Blur.h"

T_BlurTool::T_BlurTool()
{
}
T_BlurTool::T_BlurTool(int* bufferHeight, int* bufferWidth)
{
	m_bufferHeight = bufferHeight;
	m_bufferWidth = bufferWidth;

	m_maxFloat = 1.0;
	m_brushBool = true;
	m_stampBool = false;
	m_kernelBool = true;
	m_luminanceBool= false;
	m_needTempCanvas = true;

	m_defaultWidth = 31;
	m_defaultHeight =31;
	m_defaultMaskSize= 31;

	m_toolSize = 1.0;
	m_width = m_defaultWidth;
	m_height = m_defaultHeight;
	m_maskSize = m_defaultMaskSize;

	m_drawLineLimitFactor=2.0; // zero means no limitation

	setMaskBehavior(new M_FalloffEllipseMask());
	makeMask();

  m_filter = new F_Blur(5.0);
}

T_BlurTool::~T_BlurTool()
{
}
