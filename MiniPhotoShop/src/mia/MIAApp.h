//
//  MIAApp.h
//  Originally created by the CSci-3081W TAs.
//


#ifndef MIAAPP_H
#define MIAAPP_H

#include "BaseGfxApp.h"

class ColorData;
class PixelBuffer;
class PixelBufferStack;
class Tool;
class Filter;

class MIAApp : public BaseGfxApp {
public:

    MIAApp(int argc, char* argv[], int width, int height, ColorData backgroundColor);
    virtual ~MIAApp();

    // Glut overrided function
    void mouseDragged(int x, int y) ;
    void mouseMoved(int x, int y);
    void leftMouseDown(int x, int y);
    void leftMouseUp(int x, int y);
    void display();
    void gluiControl(int controlID);
    void runCommandLine(int argc, char* argv[]);
    bool isValid(int argc, char* argv[]);

protected:

    Tool* tools[2];

    Filter* grayscale;
    Filter* sharpen;
    Filter* channels;
    Filter* edgedetect;
    Filter* threshold;
    Filter* quantize;
    Filter* blur;
    Filter* saturate;

    float oldRed;
    float oldGreen;
    float oldBlue;

    int prev_x;
  	int prev_y;

private:

    // GLUI INTERFACE ELEMENTS
    enum UIControlType {
        UI_TOOLTYPE,
        UI_FILE_BROWSER,
        UI_LOAD_CANVAS_BUTTON,
        UI_SAVE_CANVAS_BUTTON,
        UI_NEXT_IMAGE_BUTTON,
        UI_PREVIOUS_IMAGE_BUTTON,
        UI_FILE_NAME,
        UI_APPLY_SHARP,
        UI_APPLY_EDGE,
        UI_APPLY_THRESHOLD,
        UI_APPLY_GRAYSCALE,
        UI_APPLY_MULTIPLY_RGB,
        UI_APPLY_QUANTIZE,
        UI_UNDO,
        UI_REDO,
        UI_QUIT
    };
    void setImageFile(const std::string & filepath);
    std::string getImageNamePlusSeqOffset(const std::string & currentFileName, int offset);
    void buttonEnabled(GLUI_Button * button, bool enabled);
    void undoEnabled(bool enabled);
    void redoEnabled(bool enabled);
    void saveCanvasEnabled(bool enabled);
    void loadCanvasEnabled(bool enabled);
    void previousImageEnabled(bool enabled);
    void nextImageEnabled(bool enabled);

    void loadImageToCanvas();
    void saveCanvasToFile();
    void loadNextImage();
    void loadPreviousImage();

    void applyFilterSharpen();
    void applyFilterEdgeDetect();
    void applyFilterThreshold();
    void applyFilterMultiplyRGB();
    void applyFilterGrayScale();
    void applyFilterQuantize();
    void applyFilterBlur();
    void applyFilterSaturate();

    void undoOperation();
    void redoOperation();
    void updateUndoRedoButtons();

    void initGlui();
    void initGraphics();
    void initializeBuffers(ColorData initialColor, int width, int height);

    bool isValidImageFileName(const std::string & name);
    bool isValidImageFile(const std::string & name);
    bool hasSuffix(const std::string & str, const std::string & suffix);
    bool isNotNumber(std::string s);


	int comparePixelBuffer(const PixelBuffer * le_buff, const PixelBuffer * re_buff);

    struct {
        float multiply_colorRed;
        float multiply_colorGreen;
        float multiply_colorBlue;
        float threshold_amount;
        float sharpen_amount;
        float blur_amount;
        float saturate_amount;
        int quantize_bins;

    } m_filterParameters;

    struct {
        GLUI_FileBrowser* fileBrowser;
        GLUI_Button *loadCanvasButton;
        GLUI_Button *saveCanvasButton;
        GLUI_Button* nextImageButton;
        GLUI_Button* previousImageButton;
        GLUI_Button *redoButton;
        GLUI_Button *undoButton;

        GLUI_StaticText * currentFileLabel;
        GLUI_EditText* fileNameBox;
        GLUI_StaticText * saveFileLabel;




    } m_gluiControlHooks;

    // This is the pointer to the buffer where the display PixelBuffer is stored
    PixelBuffer* m_displayBuffer;
    PixelBuffer* m_arrowBuffer;
    PixelBufferStack* m_undoRedoStack;

    // These are used to store the selections from the GLUI user interface
    int m_curTool;
    std::string m_fileName;
    std::string m_nextFileName;
    std::string m_prevFileName;
    std::string m_directory;
};


#endif
