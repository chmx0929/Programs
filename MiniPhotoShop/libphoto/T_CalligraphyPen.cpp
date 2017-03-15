#include "Tool.h"
#include "T_CalligraphyPen.h"
#include "M_FlatRectangleMask.h"

// Mask of Calligraphy Pen will be like:
// 		0 0 1 1 1 0 0
// 		0 0 1 1 1 0 0
// 		0 0 1 1 1 0 0
// 		0 0 1 1 1 0 0
// 		0 0 1 1 1 0 0
// 		0 0 1 1 1 0 0
// 		0 0 1 1 1 0 0


T_CalligraphyPen::T_CalligraphyPen()
{
}

T_CalligraphyPen::T_CalligraphyPen(int* bufferHeight, int* bufferWidth)
{
	m_bufferHeight = bufferHeight;
	m_bufferWidth = bufferWidth;

	m_maxFloat = 1.0;
	m_brushBool = true;
	m_stampBool = false;
	m_kernelBool = false;
	m_luminanceBool= false;
	m_needTempCanvas = false;

	m_defaultWidth = 5;
	m_defaultHeight = 15;
	m_defaultMaskSize= 15;

	m_toolSize = 1.0;
	m_width = m_defaultWidth;
	m_height = m_defaultHeight;
	m_maskSize = m_defaultMaskSize;

	m_drawLineLimitFactor=0.0; // zero means no limitation

	setMaskBehavior(new M_FlatRectangleMask());
	makeMask();

}

T_CalligraphyPen::~T_CalligraphyPen()
{
}
