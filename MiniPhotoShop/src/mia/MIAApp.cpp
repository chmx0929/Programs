#include "MIAApp.h"
#include "libphoto.h"
#include <dirent.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

MIAApp::MIAApp(int argc, char* argv[], int width, int height, ColorData backgroundColor) : BaseGfxApp(argc, argv, width, height, 50, 50, GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH, true, width+51, 50)
{
    // Set the name of the window
    setCaption("Medical Image Analysis (MIA)");

    // Initialize Interface
    initializeBuffers(backgroundColor, width, height);

    initGlui();
    initGraphics();

    tools[0] = new T_Pen(&m_height, &m_width);
    tools[1] = new T_Stamp(&m_height, &m_width);

    m_arrowBuffer = ImportExporter::importImage("./src/mia/marker.png", m_displayBuffer);
    tools[1]->setStampBuffer(m_arrowBuffer);

    grayscale = new F_Saturate(0.0);
    sharpen = new F_Sharpen(m_filterParameters.sharpen_amount);
    channels = new F_Channels(m_filterParameters.multiply_colorRed, m_filterParameters.multiply_colorGreen, m_filterParameters.multiply_colorBlue);
    edgedetect = new F_EdgeDetect();
    threshold = new F_Threshold(m_filterParameters.threshold_amount);
    quantize = new F_Quantize(m_filterParameters.quantize_bins);
    blur = new F_Blur(m_filterParameters.blur_amount);
    saturate = new F_Saturate(m_filterParameters.saturate_amount);

    oldRed = m_filterParameters.multiply_colorRed;
    oldGreen = m_filterParameters.multiply_colorGreen;
    oldBlue = m_filterParameters.multiply_colorBlue;
    if(argc != 1){
        runCommandLine(argc, argv);
    }
}

void MIAApp::display()
{
    drawPixels(0, 0, m_width, m_height, m_displayBuffer->getData());
}

MIAApp::~MIAApp()
{
    if (m_displayBuffer) {
        delete m_displayBuffer;
    }
    if (m_arrowBuffer) {
        delete m_arrowBuffer;
    }

    delete tools[0];
    delete tools[1];

    delete grayscale;
    delete sharpen;
    delete channels;
    delete edgedetect;
    delete threshold;
    delete quantize;
    delete blur;
    delete saturate;
    delete m_undoRedoStack;
}


void MIAApp::mouseDragged(int x, int y)
{
  tools[m_curTool]->drawLine(prev_x, m_height-prev_y, x, m_height-y,
             ColorData(1.0,0.0,0.0),m_displayBuffer);
  prev_x = x;
  prev_y = y;
}

void MIAApp::mouseMoved(int x, int y)
{

}

void MIAApp::leftMouseDown(int x, int y)
{
  tools[m_curTool]->copyCanvas(m_displayBuffer);
  tools[m_curTool]->draw(x,m_height-y,ColorData(1.0,0.0,0.0),m_displayBuffer);

  prev_x = x;
  prev_y = y;
  std::cout << "mousePressed " << x << " " << y << std::endl;
}

void MIAApp::leftMouseUp(int x, int y)
{
  tools[m_curTool]->freeTempCanvas();
  m_undoRedoStack->pushBuffer(m_displayBuffer, PixelBufferStack::BRUSH_APPLY, m_fileName);
  updateUndoRedoButtons();
  std::cout << "mouseReleased " << x << " " << y << std::endl;
}

void MIAApp::initializeBuffers(ColorData backgroundColor, int width, int height) {
    m_displayBuffer = new PixelBuffer(width, height, backgroundColor);
    m_undoRedoStack = new PixelBufferStack(m_displayBuffer);
}

void MIAApp::updateUndoRedoButtons() {
    if (m_undoRedoStack->checkUpStack()) {
        undoEnabled(true);
    }
    else{
        undoEnabled(false);
    }
    if (m_undoRedoStack->checkDownStack()) {
        redoEnabled(true);
    }
    else{
        redoEnabled(false);
    }
}

void MIAApp::initGlui()
{
    // Select first tool (this activates the first radio button in glui)
    m_curTool = 0;



    new GLUI_Column(m_glui, false);
    GLUI_Panel *toolPanel = new GLUI_Panel(m_glui, "Tool Type");
    {
        GLUI_RadioGroup *radio = new GLUI_RadioGroup(toolPanel, &m_curTool, UI_TOOLTYPE, s_gluicallback);
        // Create interface buttons for different tools:
        new GLUI_RadioButton(radio, "Pen");
        new GLUI_RadioButton(radio, "Arrow");

    }


    GLUI_Panel *filterPanel = new GLUI_Panel(m_glui, "Filters");
    {
        GLUI_Panel *sharpenPanel = new GLUI_Panel(filterPanel, "Sharpen");
        {
            GLUI_Spinner * filterSharpAmount = new GLUI_Spinner(sharpenPanel, "Amount:", &m_filterParameters.sharpen_amount);
            filterSharpAmount->set_int_limits(1, 10);
            filterSharpAmount->set_int_val(1);
            filterSharpAmount->set_speed(0.1);

            new GLUI_Button(sharpenPanel, "Apply", UI_APPLY_SHARP, s_gluicallback);
        }
        GLUI_Panel *edgeDetPanel = new GLUI_Panel(filterPanel, "Edge Detect");

        {
            new GLUI_Button(edgeDetPanel, "Apply", UI_APPLY_EDGE, s_gluicallback);
        }
        GLUI_Panel *thresPanel = new GLUI_Panel(filterPanel, "Threshold");
        {
            GLUI_Spinner * filterThresholdAmount = new GLUI_Spinner(thresPanel, "Level:", &m_filterParameters.threshold_amount);
            filterThresholdAmount->set_float_limits(0, 1);
            filterThresholdAmount->set_float_val(0.5);

            new GLUI_Button(thresPanel, "Apply", UI_APPLY_THRESHOLD, s_gluicallback);
        }

        GLUI_Panel *multiplyPanel = new GLUI_Panel(filterPanel, "Multiply RGB");
        {
            GLUI_Spinner * filterChannelRed = new GLUI_Spinner(multiplyPanel, "R:", &m_filterParameters.multiply_colorRed);
            GLUI_Spinner * filterChannelGreen = new GLUI_Spinner(multiplyPanel, "G:", &m_filterParameters.multiply_colorGreen);
            GLUI_Spinner * filterChannelBlue = new GLUI_Spinner(multiplyPanel, "B:", &m_filterParameters.multiply_colorBlue);

            filterChannelRed->set_float_limits(0, 10);
            filterChannelRed->set_float_val(1);
            filterChannelGreen->set_float_limits(0, 10);
            filterChannelGreen->set_float_val(1);
            filterChannelBlue->set_float_limits(0, 10);
            filterChannelBlue->set_float_val(1);

            new GLUI_Button(multiplyPanel, "Apply", UI_APPLY_MULTIPLY_RGB, s_gluicallback);
        }

        GLUI_Panel *quantPanel = new GLUI_Panel(filterPanel, "Quantize");
        {
            GLUI_Spinner * filterQuantizeBins = new GLUI_Spinner(quantPanel, "Bins:", &m_filterParameters.quantize_bins);
            filterQuantizeBins->set_int_limits(2, 256);
            filterQuantizeBins->set_int_val(8);
            filterQuantizeBins->set_speed(0.1);

            new GLUI_Button(quantPanel, "Apply", UI_APPLY_QUANTIZE, s_gluicallback);
        }

        GLUI_Panel *grayPanel = new GLUI_Panel(filterPanel, "Grayscale");
        {

            new GLUI_Button(grayPanel, "Apply", UI_APPLY_GRAYSCALE, s_gluicallback);
        }



        // UNDO,REDO,QUIT
        {
            m_gluiControlHooks.undoButton = new GLUI_Button(m_glui, "Undo", UI_UNDO, s_gluicallback);
            undoEnabled(false);
            m_gluiControlHooks.redoButton  = new GLUI_Button(m_glui, "Redo", UI_REDO, s_gluicallback);
            redoEnabled(false);

            new GLUI_Separator(m_glui);
            new GLUI_Button(m_glui, "Quit", UI_QUIT, (GLUI_Update_CB)exit);
        }
    }

    new GLUI_Column(m_glui, true);

    GLUI_Panel *imagePanel = new GLUI_Panel(m_glui, "Image I/O");
    {
        m_gluiControlHooks.fileBrowser = new GLUI_FileBrowser(imagePanel, "Choose Image", false, UI_FILE_BROWSER, s_gluicallback);

        m_gluiControlHooks.fileBrowser->set_h(400);

        m_gluiControlHooks.fileNameBox = new     GLUI_EditText( imagePanel , "Image:", m_fileName, UI_FILE_NAME, s_gluicallback );
        m_gluiControlHooks.fileNameBox->set_w(200);

        new GLUI_Separator(imagePanel);

        m_gluiControlHooks.currentFileLabel = new GLUI_StaticText(imagePanel, "Will load image: none");
        m_gluiControlHooks.loadCanvasButton = new GLUI_Button(imagePanel, "Load Canvas", UI_LOAD_CANVAS_BUTTON, s_gluicallback);

        new GLUI_Separator(imagePanel);

        m_gluiControlHooks.saveFileLabel = new GLUI_StaticText(imagePanel, "Will save image: none");

        m_gluiControlHooks.saveCanvasButton = new GLUI_Button(imagePanel, "Save Canvas", UI_SAVE_CANVAS_BUTTON, s_gluicallback);


        m_gluiControlHooks.previousImageButton = new GLUI_Button(imagePanel, "Previous Image", UI_PREVIOUS_IMAGE_BUTTON, s_gluicallback);
        m_gluiControlHooks.nextImageButton = new GLUI_Button(imagePanel, "Next Image", UI_NEXT_IMAGE_BUTTON, s_gluicallback);


        loadCanvasEnabled(false);
        saveCanvasEnabled(false);
        nextImageEnabled(false);
        previousImageEnabled(false);
    }
    return;
}

void MIAApp::gluiControl(int controlID)
{

    switch (controlID) {
        case UI_APPLY_SHARP:
            applyFilterSharpen();
            break;
        case UI_APPLY_EDGE:
            applyFilterEdgeDetect();
            break;
        case UI_APPLY_THRESHOLD:
            applyFilterThreshold();
            break;
        case UI_APPLY_GRAYSCALE:
            applyFilterGrayScale();
            break;
        case UI_APPLY_MULTIPLY_RGB:
            applyFilterMultiplyRGB();
            break;
        case UI_APPLY_QUANTIZE:
            applyFilterQuantize();
            break;
        case UI_FILE_BROWSER:
            setImageFile(m_gluiControlHooks.fileBrowser->get_file());
            break;
        case UI_LOAD_CANVAS_BUTTON:
            loadImageToCanvas();
            break;
        case UI_SAVE_CANVAS_BUTTON:
            saveCanvasToFile();
            // Reload the current directory:
            m_gluiControlHooks.fileBrowser->fbreaddir(".");
            break;
        case UI_NEXT_IMAGE_BUTTON:
            loadNextImage();
            break;
        case UI_PREVIOUS_IMAGE_BUTTON:
            loadPreviousImage();
            break;
        case UI_FILE_NAME:
            setImageFile(m_fileName);
            break;
        case UI_UNDO:
            undoOperation();
            break;
        case UI_REDO:
            redoOperation();
            break;
        default:
            break;
    }

    // Forces canvas to update changes made in this function
    m_glui->post_update_main_gfx();
}

// **********************
// *** GLUI CALLBACKS ***

// Edit these functions to provide instructions
// for how MIAApp should respond to the
// button presses.

void MIAApp::loadImageToCanvas()
{
    cout << "Load Canvas has been clicked for file " << m_fileName << endl;
    PixelBuffer* temp_buff;
    if(ImportExporter::isValidImageFile(m_fileName)) {
        temp_buff=ImportExporter::importImage(m_fileName, m_displayBuffer);
        if (m_undoRedoStack->getCurrentLastAction() != PixelBufferStack::IMAGE_LOAD || !PixelBuffer::comparePixelBuffer(m_displayBuffer, temp_buff)) {
            delete m_displayBuffer;
            m_displayBuffer = temp_buff;
            setWindowDimensions(m_displayBuffer->getWidth(),m_displayBuffer->getHeight());
            m_undoRedoStack->pushBuffer(m_displayBuffer, PixelBufferStack::IMAGE_LOAD , m_fileName);
            updateUndoRedoButtons();
        } else {
            cout << "Loading image would not change canvas" << endl;
        }
    } else {
        cout << "Image could not be loaded" << endl;
    }
    // Determining whether there are next or previous images
    m_nextFileName = getImageNamePlusSeqOffset(m_fileName, 1);
    m_prevFileName = getImageNamePlusSeqOffset(m_fileName, -1);

    nextImageEnabled(ImportExporter::isValidImageFile(m_nextFileName));
    previousImageEnabled(ImportExporter::isValidImageFile(m_prevFileName));
}

void MIAApp::saveCanvasToFile()
{
    cout << "Save Canvas been clicked for file " << m_fileName << endl;
    ImportExporter::exportImage(m_fileName, m_displayBuffer);
}

void MIAApp::applyFilterThreshold()
{
    cout << "Apply has been clicked for Threshold has been clicked with amount =" << m_filterParameters.threshold_amount << endl;

    threshold->setFloatParameter(m_filterParameters.threshold_amount);
    if(m_undoRedoStack->getCurrentLastAction() != PixelBufferStack::APPLY_THRESHOLD || threshold->paramHasChanged()){
        threshold->applyFilter(m_displayBuffer);
        m_undoRedoStack->pushBuffer(m_displayBuffer, PixelBufferStack::APPLY_THRESHOLD, m_fileName);
        updateUndoRedoButtons();
        cout << "Applied Threshold" << endl;
    } else {
        cout << "Action would not change canvas" << endl;
    }
}

void MIAApp::applyFilterSaturate()
{
    cout << "Apply has been clicked for Saturate with amount = " << m_filterParameters.saturate_amount << endl;
    //At this time there is no limit to filtersaturate applies pushed to the pixel buffer stack
    saturate->setFloatParameter(m_filterParameters.saturate_amount);
    saturate->applyFilter(m_displayBuffer);
    m_undoRedoStack->pushBuffer(m_displayBuffer, PixelBufferStack::APPLY_SATURATE, m_fileName);
    updateUndoRedoButtons();
    cout << "Applied Saturation" << endl;
}

void MIAApp::applyFilterBlur()
{
    cout << "Apply has been clicked for Blur with amount = " << m_filterParameters.blur_amount << endl;
    blur->setFloatParameter(m_filterParameters.blur_amount);
    if(blur->paramHasChanged())
    {
        blur->changeKernel((int) m_filterParameters.blur_amount);
    }
    //At this time there is no limit to filter blur applies pushed to the pixel buffer stack
    blur->applyFilter(m_displayBuffer);
    m_undoRedoStack->pushBuffer(m_displayBuffer, PixelBufferStack::APPLY_BLUR, m_fileName);
    updateUndoRedoButtons();
    cout << "Applied Blur" << endl;
}

void MIAApp::applyFilterMultiplyRGB()
{
    cout << "Apply has been clicked for Multiply RGB with red = " << m_filterParameters.multiply_colorRed
    << ", green = " << m_filterParameters.multiply_colorGreen
    << ", blue = " << m_filterParameters.multiply_colorBlue << endl;

    channels->setColors(m_filterParameters.multiply_colorRed,m_filterParameters.multiply_colorGreen,m_filterParameters.multiply_colorBlue);
    channels->applyFilter(m_displayBuffer);
    m_undoRedoStack->pushBuffer(m_displayBuffer, PixelBufferStack::APPLY_CHANNEL, m_fileName); //this is the action code for filter
    updateUndoRedoButtons();
    cout << "Applied MultiplyRGB" << endl;
}

void MIAApp::applyFilterGrayScale()
{
    cout << "Apply has been clicked for Grayscale" << endl;
    if(m_undoRedoStack->getCurrentLastAction() != PixelBufferStack::APPLY_SATURATE) {
        grayscale->applyFilter(m_displayBuffer);
        m_undoRedoStack->pushBuffer(m_displayBuffer, PixelBufferStack::APPLY_SATURATE, m_fileName);
        updateUndoRedoButtons();
    }  else {
        cout << "Action would not change canvas" << endl;
    }
}


void MIAApp::applyFilterSharpen()
{
    cout << "Apply has been clicked for Sharpen with amount = " << m_filterParameters.sharpen_amount << endl;
    sharpen->setFloatParameter(m_filterParameters.sharpen_amount);
    if(sharpen->paramHasChanged())
    {
        sharpen->changeKernel((int) m_filterParameters.sharpen_amount);
    }
    //At this time there is no limit to filter Sharpen applies pushed to the pixel buffer stack
    sharpen->applyFilter(m_displayBuffer);
    m_undoRedoStack->pushBuffer(m_displayBuffer, PixelBufferStack::APPLY_SHARP, m_fileName);
    cout << "Applied Sharpen" << endl;
}

void MIAApp::applyFilterEdgeDetect() {
    cout << "Apply has been clicked for Edge Detect" << endl;
    //At this time there is no limit to filter edge detect applies pushed to the pixel buffer stack
    edgedetect->applyFilter(m_displayBuffer);
    m_undoRedoStack->pushBuffer(m_displayBuffer, PixelBufferStack::APPLY_EDGE, m_fileName);
    updateUndoRedoButtons();

    cout << "Applied EdgeDetect" << endl;
}

void MIAApp::applyFilterQuantize() {
    cout << "Apply has been clicked for Quantize with bins = " << m_filterParameters.quantize_bins << endl;
    quantize->setIntParameter(m_filterParameters.quantize_bins);
    if(quantize->paramHasChanged() || m_undoRedoStack->getCurrentLastAction() != PixelBufferStack::APPLY_QUANTIZE)
    {
        quantize->applyFilter(m_displayBuffer);
        m_undoRedoStack->pushBuffer(m_displayBuffer, PixelBufferStack::APPLY_QUANTIZE, m_fileName);
        updateUndoRedoButtons();
        cout << "Applied Quantize" << endl;
    } else {
        cout << "Action would not change canvas" << endl;
    }
}


void MIAApp::undoOperation()
{
    cout << "Undoing..." << endl;
    PixelBuffer* transitionBuffer;
    if(m_undoRedoStack->checkUpStack()) {
        m_undoRedoStack->climbStack();
        setImageFile(m_undoRedoStack->getCurrentFileName()); //sets file name accordingly
        transitionBuffer = m_undoRedoStack->getCurrentBuffer();
        if(m_displayBuffer->getWidth() != transitionBuffer->getWidth() || m_displayBuffer->getHeight() != transitionBuffer->getHeight()) {
            delete m_displayBuffer;
            m_displayBuffer = new PixelBuffer(transitionBuffer->getWidth(),transitionBuffer->getHeight(),transitionBuffer->getBackgroundColor());
            setWindowDimensions(m_displayBuffer->getWidth(),m_displayBuffer->getHeight());
        }
        PixelBuffer::copyPixelBuffer(transitionBuffer,m_displayBuffer);
    }
    updateUndoRedoButtons();
}

void MIAApp::redoOperation()
{
    cout << "Redoing..." << endl;
    PixelBuffer* transitionBuffer;
    if(m_undoRedoStack->checkDownStack()) {
        m_undoRedoStack->descendStack();
        setImageFile(m_undoRedoStack->getCurrentFileName());
        transitionBuffer = m_undoRedoStack->getCurrentBuffer();
        if(m_displayBuffer->getWidth() != transitionBuffer->getWidth() || m_displayBuffer->getHeight() != transitionBuffer->getHeight()) {
            delete m_displayBuffer;
            m_displayBuffer = new PixelBuffer(transitionBuffer->getWidth(),transitionBuffer->getHeight(),transitionBuffer->getBackgroundColor());
            setWindowDimensions(m_displayBuffer->getWidth(),m_displayBuffer->getHeight());
        }
        PixelBuffer::copyPixelBuffer(transitionBuffer,m_displayBuffer);
    }
    updateUndoRedoButtons();
}
// ** END OF CALLBACKS **
// **********************


// **********************
// Provided code for managing the
// GLUI interface.

void MIAApp::buttonEnabled(GLUI_Button * button, bool enabled) {
    if(enabled) button->enable();
    else button->disable();
    button->redraw();
}

void MIAApp::redoEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.redoButton, enabled);
}

void MIAApp::undoEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.undoButton, enabled);
}

void MIAApp::saveCanvasEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.saveCanvasButton, enabled);
}

void MIAApp::loadCanvasEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.loadCanvasButton, enabled);
}

void MIAApp::previousImageEnabled(bool enabled) {
    buttonEnabled(m_gluiControlHooks.previousImageButton, enabled);
}

void MIAApp::nextImageEnabled(bool enabled) {
    buttonEnabled(m_gluiControlHooks.nextImageButton, enabled);
}

void MIAApp::loadNextImage()
{
    setImageFile(m_nextFileName);
    loadImageToCanvas();
}

void MIAApp::loadPreviousImage()
{
    setImageFile(m_prevFileName);
    loadImageToCanvas();
}

std::string MIAApp::getImageNamePlusSeqOffset(const std::string & currentFileName, int offset)
{

    int digitCount = 3;

    std::string extension, name, number;
    size_t dotPos = currentFileName.find_last_of(".");
    if (dotPos ==  std::string::npos || dotPos == 0) {
        return "";
    }

    extension = currentFileName.substr(dotPos+1);
    name = currentFileName.substr(0,dotPos);
    if (name.length() < digitCount) {
        return "";
    }

    number = name.substr(name.length()-digitCount);
    name = name.substr(0,name.length()-digitCount);
    int num;
    std::istringstream ( number ) >> num;
    int output_num = num +offset;
    if (output_num < 0) {
        return "";
    }
    std::stringstream ss;
    ss << output_num;
    std::string output_number;
    ss >> output_number;

    // Append zero chars
    size_t str_length = output_number.length();
    for (int i = 0; i < digitCount - str_length; i++)
        output_number = "0" + output_number;

    return (name + output_number + "." + extension);
}


void MIAApp::setImageFile(const std::string & fileName)
{

    // If no file is selected or typed,
    // don't allow file to be saved. If
    // there is a file name, then allow
    // file to be saved to that name.
    std::string imageFile;
    if (!ImportExporter::hasSupportedExtension(fileName)) {
        imageFile = m_fileName;
        m_gluiControlHooks.saveFileLabel->set_text("Will save image: none");
        saveCanvasEnabled(false);
    } else {
        imageFile = fileName;
        m_gluiControlHooks.saveFileLabel->set_text((std::string("Will save image: ") + imageFile).c_str());
        saveCanvasEnabled(true);
    }
    // If the file specified cannot be opened,
    // then disable stamp and canvas loading.
    if (ImportExporter::isValidImageFile(imageFile)) {
        loadCanvasEnabled(true);

        m_gluiControlHooks.currentFileLabel->set_text((std::string("Will load: ") + imageFile).c_str());
        m_gluiControlHooks.fileNameBox->set_text(imageFile);

    } else {
        loadCanvasEnabled(false);

        m_gluiControlHooks.currentFileLabel->set_text("Will load: none");
    }
}

void MIAApp::initGraphics() {
	// Initialize OpenGL for 2D graphics as used in the BrushWork app
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0, m_width, 0, m_height);
	glViewport(0, 0, m_width, m_height);
}

int MIAApp::comparePixelBuffer(const PixelBuffer * le_buff, const PixelBuffer * re_buff) {
	int le_width, le_height, re_width, re_height;
	le_width = le_buff->getWidth();
	le_height = le_buff->getHeight();
	re_width = re_buff->getWidth();
	re_height = re_buff->getHeight();

	if((le_width != re_width) || (le_height != re_height)) {
		return 0;
	}
	for (int i = 0; i < le_width; ++i)
	{
		for (int j = 0; j < le_height; ++j)
		{
			if(le_buff->getPixel(i, j) != re_buff->getPixel(i,j)) {
				return 0;
			}
		}

	}
	return 1;
}


bool MIAApp::isValid(int argc, char* argv[]){
    return true;
}

bool MIAApp::hasSuffix(const std::string & str, const std::string & suffix){
    return str.find(suffix,str.length()-suffix.length()) != std::string::npos;
}

bool MIAApp::isValidImageFileName(const std::string & name) {
    if (hasSuffix(name, ".png")
        || hasSuffix(name, ".jpg")
        || hasSuffix(name, ".jpeg")
        )
        return true;
    else
        return false;
}

bool MIAApp::isValidImageFile(const std::string & name) {
    FILE *file;
    bool isValid = false;
    if (isValidImageFileName(name)) {
        if ((file = fopen( name.c_str(), "r"))) {
            isValid = true;
            fclose(file);
        }
    }
    return isValid;
}

void MIAApp::runCommandLine(int argc, char* argv[]){
    bool isInput = true;
    for(int i=1;i<argc;i++){
        string command = argv[i];
        //Help Command
        if(argc==2&&command=="-h"){
            cout<<"Complete list of command-line arguments:"<<endl;
            cout<<"-sharpen <integer>"<<endl;
            cout<<"-edgedetect"<<endl;
            cout<<"-thresh <float>"<<endl;
            cout<<"-quantize <int>"<<endl;
            cout<<"-blur <float>"<<endl;
            cout<<"-saturate <float>"<<endl;
            cout<<"-multrgb <float>,<float>,<float>"<<endl;
            cout<<"-compare"<<endl;
        }
        //Command and there exists a image
        else if(command[0]=='-'&&isInput==false){
            if("-sharpen" == command){
                m_filterParameters.sharpen_amount = atoi(argv[i+1]);
                applyFilterSharpen();
                i+=1;
            }
            if("-edgedetect"==command){
                applyFilterEdgeDetect();
            }
            if("-thresh"==command){
                m_filterParameters.threshold_amount = atof(argv[i+1]);
                applyFilterThreshold();
                i+=1;
            }
            if("-quantize"==command){
                m_filterParameters.quantize_bins = atoi(argv[i+1]);
                applyFilterQuantize();
                i+=1;
            }
            if("-blur"==command){
                m_filterParameters.blur_amount = atof(argv[i+1]);
                applyFilterBlur();
                i+=1;
            }
            if("-saturate"==command){
                m_filterParameters.saturate_amount = atof(argv[i+1]);
                applyFilterSaturate();
                i+=1;
            }
            if("-multrgb"==command){
                m_filterParameters.multiply_colorRed = atof(argv[i+1]);
                m_filterParameters.multiply_colorGreen = atof(argv[i+2]);
                m_filterParameters.multiply_colorBlue = atof(argv[i+3]);
                applyFilterMultiplyRGB();
                i = i + 3;
            }
            if("-compare"==command){

            }
        }
        //File or folder name
        else if(command[0]!='-'){
            if(isInput){
                isInput = false;
                //laod images
                if(isValidImageFileName(command)){
                    m_fileName = command;
                    loadImageToCanvas();
                }
                //laod from directory
                else{
                    m_directory = command;
                    DIR *dir;
                    struct dirent *ent;
                    if ((dir = opendir (argv[i])) != NULL) {
                        while ((ent = readdir (dir)) != NULL) {
                            if(hasSuffix(ent->d_name,".png") || hasSuffix(ent->d_name,".jpg")){
                                char* infile = new char[command.length()+std::strlen(ent->d_name)+2];
                                strcpy (infile, command.c_str());
                                strcat (infile,"/");
                                strcat (infile,ent->d_name);
                                argv[i] = infile;
                                runCommandLine(argc,argv);
                            }
                        }
                        closedir (dir);
                    }
                    else{
                        /* could not open directory */
                        perror ("could not open directory");
                    }
                    return;
                }
            }
            //output
            else {
                isInput = true;
                //save images
                if(hasSuffix(command,".png") || hasSuffix(command,".jpg")){
                    m_fileName = command;
                }
                //save to directory
                else{
                    m_fileName.replace(0,m_directory.length(),command);
                }
                saveCanvasToFile();
            }
        }
    }
}
