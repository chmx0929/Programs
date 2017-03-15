#ifndef TOOL_H
#define TOOL_H

class MaskBehavior;
class ColorData;
class PixelBuffer;
class Filter;

/**
This class was used as the template for the rest of the tools
*/
class Tool
{
	public:
		Tool();
		virtual ~Tool();
		void scaleMask(float scaledSize);
		int getDefaultMaskSize();
		float getIntensity(int x, int y);
		float interpretLuminanceContribution(int x, int y, PixelBuffer* canvas);
		int interpretDrawLineLimitFactor();

		void draw(int x, int y, ColorData curColor, PixelBuffer* canvas);
		void drawLine(int orig_x, int orig_y, int cur_x, int cur_y, ColorData curColor, PixelBuffer* canvas);

		void copyCanvas(PixelBuffer* canvas);
		void freeTempCanvas();

		virtual void setStampBuffer(PixelBuffer* stamp);

	private:
		int normalizeSize(int dimensionSize);
		void setIntensity(int x, int y, float intensityValue);


	protected:
		void makeMask();
		void setMaskBehavior(MaskBehavior* behavior);

		///This array holds the floats that show how much the selected color affects the canvas
		float *m_maskArray;
		MaskBehavior *m_maskBehavior;

		float m_maxFloat;

		bool m_brushBool;
		bool m_stampBool;
		///this bool lets the apply function know if it needs to apply a convolution filter to the selected area
		bool m_kernelBool;
		bool m_luminanceBool;
		bool m_needTempCanvas;

		float m_drawLineLimitFactor;

		int m_width;
		int m_height;

		int m_defaultWidth;
		int m_defaultHeight;
		int m_defaultMaskSize;

		///this member function is required to change the tool's size
		float m_toolSize;
		///this member is required to change the size of the mask
		int m_maskSize;

		int* m_bufferHeight;
		int* m_bufferWidth;

		///The temp canvas is for tools that may not need to change the canvas multiple times in one mouse down/drag action, eg: BlurTool and Highlighter
		PixelBuffer* m_tempCanvas;
		PixelBuffer* m_stampBuffer;

		Filter *m_filter;
};

#endif
