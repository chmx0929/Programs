//
//  FlashPhotoApp.h
//  Originally created by the CSci-3081W TAs.
//

#ifndef FLASHPHOTOAPP_H
#define FLASHPHOTOAPP_H

#include "BaseGfxApp.h"

class ColorData;
class PixelBuffer;
class PixelBufferStack;
class Tool;
class Filter;

class FlashPhotoApp : public BaseGfxApp {
public:

    FlashPhotoApp(int argc, char* argv[], int width, int height, ColorData backgroundColor);
    virtual ~FlashPhotoApp();

    void mouseDragged(int x, int y) ;
    void mouseMoved(int x, int y);
    void leftMouseDown(int x, int y);
    void leftMouseUp(int x, int y);
    void display();
    void gluiControl(int controlID);

protected:

    Tool* tools[10];
    Filter *threshold;
    Filter *quantize;
    Filter *saturate;
    Filter *blur;
    Filter *motionblur;
    Filter *channels;
    Filter *edgedetect;
    Filter *sharpen;
    Filter *dither;
    Filter *wallpaper;
    Filter *chromakey;

private:

    // GLUI INTERFACE ELEMENTS
    enum UIControlType {
        UI_TOOLTYPE,
        UI_COLOR_R,
        UI_COLOR_G,
        UI_COLOR_B,
        UI_PRESET_RED,
        UI_PRESET_ORANGE,
        UI_PRESET_YELLOW,
        UI_PRESET_GREEN,
        UI_PRESET_BLUE,
        UI_PRESET_PURPLE,
        UI_PRESET_WHITE,
        UI_PRESET_BLACK,
        UI_TOOL_SIZE,
        UI_FILE_BROWSER,
        UI_LOAD_CANVAS_BUTTON,
        UI_LOAD_STAMP_BUTTON,
        UI_SAVE_CANVAS_BUTTON,
        UI_FILE_NAME,
        UI_APPLY_BLUR,
        UI_APPLY_SHARP,
        UI_APPLY_EDGE,
        UI_APPLY_WALLPAPER,
        UI_APPLY_CHROMAKEY,
        UI_APPLY_THRESHOLD,
        UI_APPLY_DITHER,
        UI_APPLY_SATURATE,
        UI_APPLY_CHANNEL,
        UI_APPLY_QUANTIZE,
        UI_APPLY_MOTION_BLUR,
        UI_UNDO,
        UI_REDO,
        UI_QUIT
    };

    void buttonEnabled(GLUI_Button * button, bool enabled);
    void undoEnabled(bool enabled);
    void redoEnabled(bool enabled);
    void saveCanvasEnabled(bool enabled);
    void loadCanvasEnabled(bool enabled);
    void loadStampEnabled(bool enabled);
    void wallpaperEnabled(bool enabled);
    void chromakeyEnabled(bool enabled);
    void updateColors();

    void loadImageToCanvas();
    void loadImageToStamp();
    void saveCanvasToFile();

    void applyFilterBlur();
    void applyFilterSharpen();
    void applyFilterMotionBlur();
    void applyFilterEdgeDetect();
    void applyFilterThreshold();
    void applyFilterChannel();
    void applyFilterSaturate();
    void applyFilterQuantize();
    void applyFilterSpecial();
    void applyFilterWallpaper();
    void applyFilterChromaKey();

    void undoOperation();
    void redoOperation();
    void updateUndoRedoButtons();

	void setImageFile(const std::string & filepath);
	void updateStampButtons();

    void initGlui();
    void initGraphics();
    void initializeBuffers(ColorData initialColor, int width, int height);

    enum UIMotionBlurDirections {
        DIR_N_S,
        DIR_E_W,
        DIR_NE_SW,
        DIR_NW_SE
    };

    struct {
        float channel_colorRed;
        float channel_colorGreen;
        float channel_colorBlue;
        float saturation_amount;
        float threshold_amount;
        float blur_amount;
        float sharpen_amount;
        float motionBlur_amount;
        float chromakey_fudge_factor;
        float chromakey_interpolation_factor;
        int motionBlur_direction;
        int quantize_bins;
        int dither_degree;
    } m_filterParameters;

    struct {
        GLUI_FileBrowser* fileBrowser;
        GLUI_Button *loadCanvasButton;
        GLUI_Button *loadStampButton;
        GLUI_Button *saveCanvasButton;
        GLUI_Button *redoButton;
        GLUI_Button *undoButton;
        GLUI_Button *wallpaperButton;
        GLUI_Button *chromakeyButton;
        GLUI_StaticText * currentFileLabel;
        GLUI_EditText* fileNameBox;
        GLUI_StaticText * saveFileLabel;

        GLUI_Spinner *spinnerRed;
        GLUI_Spinner *spinnerGreen;
        GLUI_Spinner *spinnerBlue;

    } m_gluiControlHooks;

    // This is the pointer to the buffer where the display PixelBuffer is stored
    PixelBuffer* m_displayBuffer;
    PixelBuffer* m_stampBuffer;
    PixelBufferStack* m_undoRedoStack;

    // These are used to store the selections from the GLUI user interface
    int m_curTool;
    float m_curColorRed, m_curColorGreen, m_curColorBlue;
    std::string m_fileName;
    float m_curToolSize;
  	float m_oldToolSize;
  	GLUI_Spinner *m_toolSize;

  	int prev_x;
  	int prev_y;

};


#endif
