#ifndef MIACOMMANDAPP_H
#define MIACOMMANDAPP_H
#include <string>
class ColorData;
class PixelBuffer;
class PixelBufferStack;
class Filter;


/**
MIACommandApp works as an independent application just like its brother MIAApp 
who has a graphical user interface. MIACommandApp will take valid input from 
command line arguments and process the operations behind the scene. To get more 
information on how does a valid command line input will be, simply type ./Mia –h 
in the command line window and the help doc will describe what functionalities 
this command line app provides and how to properly format your command.
*/
class MIACommandApp 
{
public:
    MIACommandApp(int argc, char* argv[]);
    virtual ~MIACommandApp();

    // void gluiControl(int controlID);
    void executeCommand(int argc, char* argv[]);
    int validateCommand(int argc, char* argv[]);

protected:
    Filter* grayscale;
    Filter* sharpen;
    Filter* channels;
    Filter* edgedetect;
    Filter* threshold;
    Filter* quantize;
    Filter* blur;
    Filter* saturate;

private:
    bool isValid(int argc, char* argv[]);
    int validateRest(int argc, char* argv[], int from);
    int isValidImageFile(const std::string & name);
    int isValidDir(const std::string & name);
    int isCommand(const std::string & name);
    int isNum(const std::string & name);
    int isValidImageFileName(const std::string & name);
    bool hasSuffix(const std::string & str, const std::string & suffix);
    int hasCompare(int argc, char* argv[]);
    int hasDifferentSuffix(const std::string & name1, const std::string & name2);
    //void setImageFile(const std::string & filepath);
    //std::string getImageNamePlusSeqOffset(const std::string & currentFileName, int offset);
    // void buttonEnabled(GLUI_Button * button, bool enabled);
    // void undoEnabled(bool enabled);
    // void redoEnabled(bool enabled);
    // void saveCanvasEnabled(bool enabled);
    // void loadCanvasEnabled(bool enabled);
    // void previousImageEnabled(bool enabled);
    // void nextImageEnabled(bool enabled);

    void loadImageToCanvas();
    void saveCanvasToFile();

    void applyFilterSharpen();
    void applyFilterEdgeDetect();
    void applyFilterThreshold();
    void applyFilterMultiplyRGB();
    void applyFilterGrayScale();
    void applyFilterQuantize();
    void applyFilterBlur();
    void applyFilterSaturate();

    int comparePixelBuffer(const PixelBuffer * le_buff, const PixelBuffer * re_buff);

    // void initGlui();
    // void initGraphics();
    // void initializeBuffers(ColorData initialColor, int width, int height);

    // bool isValidImageFileName(const std::string & name);
    // bool isValidImageFile(const std::string & name);
    // bool hasSuffix(const std::string & str, const std::string & suffix);
    // bool isNotNumber(std::string s);


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

    // // This is the pointer to the buffer where the display PixelBuffer is stored
    PixelBuffer* m_displayBuffer;
    PixelBuffer* m_compareBuffer;
    //PixelBuffer* m_arrowBuffer;
    //PixelBufferStack* m_undoRedoStack;

    std::string m_fileName;
    std::string m_directory;
    bool inDir;


};


#endif
