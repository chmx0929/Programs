#include "Tool.h"
#include "T_Halo.h"
#include "M_HaloEllipseMask.h"

T_Halo::T_Halo()
{
}
T_Halo::T_Halo(int* bufferHeight, int* bufferWidth)
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
	m_defaultHeight = 13;
	m_defaultMaskSize= 61;

	m_toolSize = 1.0;
	m_width = m_defaultWidth;
	m_height = m_defaultHeight;
	m_maskSize = m_defaultMaskSize;

	m_drawLineLimitFactor=2.75;

	setMaskBehavior(new M_HaloEllipseMask());
	makeMask();

}

T_Halo::~T_Halo()
{
}
