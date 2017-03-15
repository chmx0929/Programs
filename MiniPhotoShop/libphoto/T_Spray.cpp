#include "Tool.h"
#include "T_Spray.h"
#include "M_FalloffEllipseMask.h"

T_Spray::T_Spray()
{
}
T_Spray::T_Spray(int* bufferHeight, int* bufferWidth)
{
	m_bufferHeight = bufferHeight;
	m_bufferWidth = bufferWidth;

	m_maxFloat = 0.2;
	m_brushBool = true;
	m_stampBool = false;
	m_kernelBool = false;
	m_luminanceBool= false;
	m_needTempCanvas = false;

	m_defaultWidth = 41;
	m_defaultHeight = 41;
	m_defaultMaskSize= 41;

	m_toolSize = 1.0;
	m_width = m_defaultWidth;
	m_height = m_defaultHeight;
	m_maskSize = m_defaultMaskSize;

	m_drawLineLimitFactor=2.5;

	setMaskBehavior(new M_FalloffEllipseMask());
	makeMask();

}

T_Spray::~T_Spray()
{
}
