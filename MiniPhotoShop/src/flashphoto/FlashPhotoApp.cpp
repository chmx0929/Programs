#include <cmath>
#include <iostream>
#include "FlashPhotoApp.h"
#include "libphoto.h"

using std::cout;
using std::endl;

FlashPhotoApp::FlashPhotoApp(int argc, char* argv[], int width, int height, ColorData backgroundColor) : BaseGfxApp(argc, argv, width, height, 50, 50, GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH, true, width+51, 50)
{
    // Set the name of the window
    setCaption("FlashPhoto");

    // Initialize Interface
    initializeBuffers(backgroundColor, width, height);
    m_stampBuffer=0;

    initGlui();
    initGraphics();

    tools[0] = new T_Pen(&m_height, &m_width);    // Why use address instead of height() and width()?
  	tools[2] = new T_Eraser(&m_height, &m_width);
  	tools[3] = new T_Spray(&m_height, &m_width);
  	tools[4] = new T_CalligraphyPen(&m_height, &m_width);
  	tools[5] = new T_Highlighter(&m_height, &m_width);
  	tools[6] = new T_Halo(&m_height, &m_width);
  	tools[7] = new T_Gradient(&m_height, &m_width);
    tools[8] = new T_BlurTool(&m_height, &m_width);
    tools[9] = new T_Stamp(&m_height, &m_width);

    threshold = new F_Threshold(m_filterParameters.threshold_amount);
    quantize = new F_Quantize(m_filterParameters.quantize_bins);
    saturate = new F_Saturate(m_filterParameters.saturation_amount);
    blur = new F_Blur(m_filterParameters.blur_amount);
    motionblur = new F_MotionBlur(m_filterParameters.motionBlur_amount, m_filterParameters.motionBlur_direction);
    channels = new F_Channels(m_filterParameters.channel_colorRed, m_filterParameters.channel_colorGreen, m_filterParameters.channel_colorBlue);
    edgedetect = new F_EdgeDetect();
    sharpen = new F_Sharpen(m_filterParameters.sharpen_amount);
    dither = new F_Dither(m_filterParameters.dither_degree);
    wallpaper = new F_Wallpaper();
    chromakey = new F_ChromaKey(m_filterParameters.chromakey_fudge_factor, m_filterParameters.chromakey_interpolation_factor, m_curColorRed, m_curColorGreen, m_curColorBlue);

    if(argc != 1){
        std::string name(argv[1]); 
        m_fileName = name;
        loadImageToCanvas();
        std::string command(argv[2]);
        if("-eraser" == command){
            m_curTool = 2;
            leftMouseDown(atoi(argv[3]), atoi(argv[4]));
            leftMouseDown(atoi(argv[5]), atoi(argv[6]));
            tools[m_curTool]->drawLine(atoi(argv[3]), atoi(argv[4]),atoi(argv[5]), atoi(argv[6]),m_displayBuffer->getBackgroundColor(),m_displayBuffer);
        }
        else{
            if("-pen" == command){
               m_curTool = 0;
                leftMouseDown(atoi(argv[3]), atoi(argv[4]));
                leftMouseDown(atoi(argv[5]), atoi(argv[6]));
                tools[m_curTool]->drawLine(atoi(argv[3]), atoi(argv[4]),atoi(argv[5]), atoi(argv[6]), ColorData(1,0,0),m_displayBuffer);
            }
            if("-spray" == command){
                m_curTool = 3;
                leftMouseDown(atoi(argv[3]), atoi(argv[4]));
                leftMouseDown(atoi(argv[5]), atoi(argv[6]));
                tools[m_curTool]->drawLine(atoi(argv[3]), atoi(argv[4]),atoi(argv[5]), atoi(argv[6]), ColorData(1,0,0),m_displayBuffer);
            }
            if("-calligraphyPen" == command){
                m_curTool = 4;
                leftMouseDown(atoi(argv[3]), atoi(argv[4]));
                leftMouseDown(atoi(argv[5]), atoi(argv[6]));
                tools[m_curTool]->drawLine(atoi(argv[3]), atoi(argv[4]),atoi(argv[5]), atoi(argv[6]), ColorData(1,0,0),m_displayBuffer);
            }
            if("-highlighter" == command){
                m_curTool = 5;
                leftMouseDown(atoi(argv[3]), atoi(argv[4]));
                leftMouseDown(atoi(argv[5]), atoi(argv[6]));
                tools[m_curTool]->drawLine(atoi(argv[3]), atoi(argv[4]),atoi(argv[5]), atoi(argv[6]), ColorData(1,0,0),m_displayBuffer);
            }
            if("-halo" == command){
                m_curTool = 6;
                leftMouseDown(atoi(argv[3]), atoi(argv[4]));
                leftMouseDown(atoi(argv[5]), atoi(argv[6]));
                tools[m_curTool]->drawLine(atoi(argv[3]), atoi(argv[4]),atoi(argv[5]), atoi(argv[6]), ColorData(1,0,0),m_displayBuffer);
            }
            if("-gradient" == command){
                m_curTool = 7;
                leftMouseDown(atoi(argv[3]), atoi(argv[4]));
                leftMouseDown(atoi(argv[5]), atoi(argv[6]));
                tools[m_curTool]->drawLine(atoi(argv[3]), atoi(argv[4]),atoi(argv[5]), atoi(argv[6]), ColorData(1,0,0),m_displayBuffer);
            }
            if("-blurTool" == command){
                m_curTool = 8;
                leftMouseDown(atoi(argv[3]), atoi(argv[4]));
                leftMouseDown(atoi(argv[5]), atoi(argv[6]));
                tools[m_curTool]->drawLine(atoi(argv[3]), atoi(argv[4]),atoi(argv[5]), atoi(argv[6]), ColorData(1,0,0),m_displayBuffer);
            }
            if("-stamp" == command){
                m_curTool = 9;
                leftMouseDown(atoi(argv[3]), atoi(argv[4]));
                leftMouseDown(atoi(argv[5]), atoi(argv[6]));
                tools[m_curTool]->drawLine(atoi(argv[3]), atoi(argv[4]),atoi(argv[5]), atoi(argv[6]), ColorData(1,0,0),m_displayBuffer);
            }
            if("-threshold" == command){
                m_filterParameters.threshold_amount = atof(argv[3]);
                applyFilterThreshold();
            }
            if("-quantize" == command){
                m_filterParameters.quantize_bins = atoi(argv[3]);
                applyFilterQuantize();
            }
            if("-saturate" == command){
                m_filterParameters.saturation_amount = atof(argv[3]);
                applyFilterSaturate();
            }
            if("-blur" == command){
                m_filterParameters.blur_amount = atof(argv[3]);
                applyFilterBlur();
            }
            if("-motionblur" == command){
                m_filterParameters.motionBlur_amount = atof(argv[3]);
                m_filterParameters.motionBlur_direction = atoi(argv[4]);
                applyFilterMotionBlur();
            }
            if("-channels" == command){
                m_filterParameters.channel_colorRed = atof(argv[3]);
                m_filterParameters.channel_colorGreen = atof(argv[4]);
                m_filterParameters.channel_colorBlue = atof(argv[5]);
                applyFilterChannel();
            }
            if("-edgedetect" == command){
                applyFilterEdgeDetect();
            }
            if("-sharpen" == command){
                m_filterParameters.sharpen_amount = atof(argv[3]);
                applyFilterSharpen();
            }
            if("-dither" == command){
                m_filterParameters.dither_degree = atoi(argv[3]);
                applyFilterSpecial();
            }
            if("-wallpaper" == command){
                applyFilterWallpaper();
            }
            if("-chromakey" == command){
                m_filterParameters.chromakey_fudge_factor = atof(argv[3]);
                m_filterParameters.chromakey_interpolation_factor = atof(argv[4]);
                applyFilterChromaKey();
            }
        }
        m_fileName = argv[2];
        m_fileName = "./tests/FlashPhotoGeneratedImages/" + m_fileName.substr(1,m_fileName.length())+".jpg";
        saveCanvasToFile();
    }
}

void FlashPhotoApp::display()
{
    drawPixels(0, 0, m_width, m_height, m_displayBuffer->getData());
}

FlashPhotoApp::~FlashPhotoApp()
{
    if (m_displayBuffer) {
        delete m_displayBuffer;
        delete tools[0];
        delete tools[2];
        delete tools[3];
        delete tools[4];
        delete tools[5];
        delete tools[6];
        delete tools[7];
        delete tools[8];
        delete tools[9];

        delete threshold;
        delete quantize;
        delete saturate;
        delete blur;
        delete motionblur;
        delete channels;
        delete edgedetect;
        delete sharpen;
        delete dither;
        delete wallpaper;
        delete chromakey;
        if (m_stampBuffer) {
            delete m_stampBuffer;
        }
        delete m_undoRedoStack;
    }
}

void FlashPhotoApp::mouseDragged(int x, int y)
{
  // Draw line between previous xy and current xy, connecting dissected points together.
	// Call function drawLine in Tool.cpp file

	switch (m_curTool)
	{
		case 1:
			m_curColorRed = m_displayBuffer->getPixel(x, m_height-y).getRed();
			m_curColorGreen = m_displayBuffer->getPixel(x, m_height-y).getGreen();
			m_curColorBlue = m_displayBuffer->getPixel(x, m_height-y).getBlue();
			m_gluiControlHooks.spinnerRed->set_float_val(m_curColorRed);
			m_gluiControlHooks.spinnerGreen->set_float_val(m_curColorGreen);
			m_gluiControlHooks.spinnerBlue->set_float_val(m_curColorBlue);
			break;
		case 2:
			tools[2]->drawLine(prev_x, m_height-prev_y, x, m_height-y,
							   m_displayBuffer->getBackgroundColor(),m_displayBuffer);
			break;
		default:
			tools[m_curTool]->drawLine(prev_x, m_height-prev_y, x, m_height-y,
							   ColorData(m_curColorRed,m_curColorGreen,m_curColorBlue),m_displayBuffer);
	}

	//assign current xy value to previous xy
	prev_x = x;
	prev_y = y;
}

void FlashPhotoApp::mouseMoved(int x, int y)
{

}

void FlashPhotoApp::leftMouseDown(int x, int y)
{
  //draw onto the Canvas
	switch (m_curTool){
		case 1:
			m_curColorRed = m_displayBuffer->getPixel(x, m_height-y).getRed();
			m_curColorGreen = m_displayBuffer->getPixel(x, m_height-y).getGreen();
			m_curColorBlue = m_displayBuffer->getPixel(x, m_height-y).getBlue();
			m_gluiControlHooks.spinnerRed->set_float_val(m_curColorRed);
			m_gluiControlHooks.spinnerGreen->set_float_val(m_curColorGreen);
			m_gluiControlHooks.spinnerBlue->set_float_val(m_curColorBlue);
			break;
		case 2:
            tools[m_curTool]->copyCanvas(m_displayBuffer);
			tools[2]->draw(x,m_height-y,m_displayBuffer->getBackgroundColor(),m_displayBuffer);
			break;
		default:
            tools[m_curTool]->copyCanvas(m_displayBuffer);
			         tools[m_curTool]->draw(x,m_height-y,ColorData(m_curColorRed,m_curColorGreen,m_curColorBlue),m_displayBuffer);
	}

	// Store the initial x and y value, to draw lines between points.
	prev_x = x;
	prev_y = y;
    std::cout << "mousePressed " << x << " " << y << std::endl;
}

void FlashPhotoApp::leftMouseUp(int x, int y)
{
    switch(m_curTool)
    {
    case 1:
        break;
    default:
      tools[m_curTool]->freeTempCanvas();
    }

    if (m_curTool != 1)
    {
      m_undoRedoStack->pushBuffer(m_displayBuffer,PixelBufferStack::BRUSH_APPLY, m_fileName); 
      updateUndoRedoButtons();
    }

}

void FlashPhotoApp::initializeBuffers(ColorData backgroundColor, int width, int height) {

    m_displayBuffer = new PixelBuffer(width, height, backgroundColor);
    m_undoRedoStack = new PixelBufferStack(m_displayBuffer);
    // We don't update the undo redo buttons since they are not yet initialized

}

void FlashPhotoApp::updateUndoRedoButtons() {
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

void FlashPhotoApp::updateStampButtons() {
    if (m_stampBuffer) {
        wallpaperEnabled(true);
        chromakeyEnabled(true);
    } else {
        wallpaperEnabled(false);
        chromakeyEnabled(false);
    }
}

void FlashPhotoApp::initGlui()
{
    // Select first tool (this activates the first radio button in glui)
    m_curTool = 0;
    m_oldToolSize = 1.0;

    GLUI_Panel *toolPanel = new GLUI_Panel(m_glui, "Tool Type");
    {
        GLUI_RadioGroup *radio = new GLUI_RadioGroup(toolPanel, &m_curTool, UI_TOOLTYPE, s_gluicallback);
        // Create interface buttons for different tools:
        new GLUI_RadioButton(radio, "Pen");
      	new GLUI_RadioButton(radio, "Pipet");
      	new GLUI_RadioButton(radio, "Eraser");
      	new GLUI_RadioButton(radio, "Spray Can");
      	new GLUI_RadioButton(radio, "Caligraphy Pen");
      	new GLUI_RadioButton(radio, "Highlighter");
      	new GLUI_RadioButton(radio, "Halo");
      	new GLUI_RadioButton(radio, "Gradient");
        new GLUI_RadioButton(radio, "Blur Tool");
        new GLUI_RadioButton(radio, "Stamp");

        // New Spinner: toolSize
      	// makes the tool bigger or smaller
      	m_toolSize = new GLUI_Spinner(toolPanel, "Tool Size:", &m_curToolSize, UI_TOOL_SIZE, s_gluicallback);
      	m_toolSize->set_float_limits(.5, 5.0);
      	m_toolSize->set_float_val(1.0);
    }

    GLUI_Panel *colorPanel = new GLUI_Panel(m_glui, "Tool Color");
    {
        m_curColorRed = 0;
        m_gluiControlHooks.spinnerRed  = new GLUI_Spinner(colorPanel, "Red:", &m_curColorRed, UI_COLOR_R, s_gluicallback);
        m_gluiControlHooks.spinnerRed->set_float_limits(0, 1.0);

        m_curColorGreen = 0;
        m_gluiControlHooks.spinnerGreen  = new GLUI_Spinner(colorPanel, "Green:", &m_curColorGreen, UI_COLOR_G, s_gluicallback);
        m_gluiControlHooks.spinnerGreen->set_float_limits(0, 1.0);

        m_curColorBlue = 0;
        m_gluiControlHooks.spinnerBlue  = new GLUI_Spinner(colorPanel, "Blue:", &m_curColorBlue, UI_COLOR_B, s_gluicallback);
        m_gluiControlHooks.spinnerBlue->set_float_limits(0, 1.0);

        new GLUI_Button(colorPanel, "Red", UI_PRESET_RED, s_gluicallback);
        new GLUI_Button(colorPanel, "Orange", UI_PRESET_ORANGE, s_gluicallback);
        new GLUI_Button(colorPanel, "Yellow", UI_PRESET_YELLOW, s_gluicallback);
        new GLUI_Button(colorPanel, "Green", UI_PRESET_GREEN, s_gluicallback);
        new GLUI_Button(colorPanel, "Blue", UI_PRESET_BLUE, s_gluicallback);
        new GLUI_Button(colorPanel, "Purple", UI_PRESET_PURPLE, s_gluicallback);
        new GLUI_Button(colorPanel, "White", UI_PRESET_WHITE, s_gluicallback);
        new GLUI_Button(colorPanel, "Black", UI_PRESET_BLACK, s_gluicallback);
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

    new GLUI_Column(m_glui, true);
    GLUI_Panel *filterPanel = new GLUI_Panel(m_glui, "Filters");
    {
        GLUI_Panel *blurPanel = new GLUI_Panel(filterPanel, "Blur");
        {
            GLUI_Spinner * filterBlurAmount = new GLUI_Spinner(blurPanel, "Amount:", &m_filterParameters.blur_amount);
            filterBlurAmount->set_int_limits(0, 20);

            filterBlurAmount->set_int_val(5);

            new GLUI_Button(blurPanel, "Apply", UI_APPLY_BLUR, s_gluicallback);
        }

        GLUI_Panel *motionBlurPanel = new GLUI_Panel(filterPanel, "MotionBlur");
        {
            GLUI_Spinner * filterMotionBlurAmount = new GLUI_Spinner(motionBlurPanel, "Amount:", &m_filterParameters.motionBlur_amount);
            filterMotionBlurAmount->set_int_limits(0, 100);

            filterMotionBlurAmount->set_int_val(5);

            m_filterParameters.motionBlur_direction = 0;
            GLUI_RadioGroup *dirBlur = new GLUI_RadioGroup(motionBlurPanel, &m_filterParameters.motionBlur_direction);
            new GLUI_RadioButton(dirBlur, "North/South");
            new GLUI_RadioButton(dirBlur, "East/West");
            new GLUI_RadioButton(dirBlur, "NorthEast/SouthWest");
            new GLUI_RadioButton(dirBlur, "NorthWest/SouthEast");

            new GLUI_Button(motionBlurPanel, "Apply", UI_APPLY_MOTION_BLUR, s_gluicallback);
        }
        GLUI_Panel *sharpenPanel = new GLUI_Panel(filterPanel, "Sharpen");
        {
            GLUI_Spinner * filterSharpAmount = new GLUI_Spinner(sharpenPanel, "Amount:", &m_filterParameters.sharpen_amount);
            filterSharpAmount->set_int_limits(0, 100);

            filterSharpAmount->set_int_val(5);

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
        GLUI_Panel *wallpaperPanel = new GLUI_Panel(filterPanel, "Stamp Wallpaper");

        {
             m_gluiControlHooks.wallpaperButton  = new GLUI_Button(wallpaperPanel, "Apply", UI_APPLY_WALLPAPER, s_gluicallback);
             wallpaperEnabled(false);
        }
        GLUI_Panel *chromakeyPanel = new GLUI_Panel(filterPanel, "Chroma Key");

        {
            GLUI_Spinner * filterchromakeyAmount = new GLUI_Spinner(chromakeyPanel, "Fudge Factor:", &m_filterParameters.chromakey_fudge_factor);
            filterchromakeyAmount->set_float_limits(0, 1);
            filterchromakeyAmount->set_float_val(0.15);
            GLUI_Spinner * filterchromakeyAmount2 = new GLUI_Spinner(chromakeyPanel, "Interpolation Factor:", &m_filterParameters.chromakey_interpolation_factor);
            filterchromakeyAmount2->set_float_limits(0, 1);
            filterchromakeyAmount2->set_float_val(0.05);
             m_gluiControlHooks.chromakeyButton  = new GLUI_Button(chromakeyPanel, "Apply", UI_APPLY_CHROMAKEY, s_gluicallback);
             chromakeyEnabled(false);
        }

		new GLUI_Column(filterPanel, false);

        GLUI_Panel *saturPanel = new GLUI_Panel(filterPanel, "Saturation");
        {
            GLUI_Spinner * filterSaturationAmount = new GLUI_Spinner(saturPanel, "Amount:", &m_filterParameters.saturation_amount);
            filterSaturationAmount->set_float_limits(-10, 10);
            filterSaturationAmount->set_float_val(1);

            new GLUI_Button(saturPanel, "Apply", UI_APPLY_SATURATE, s_gluicallback);
        }

        GLUI_Panel *channelPanel = new GLUI_Panel(filterPanel, "Channels");
        {
            GLUI_Spinner * filterChannelRed = new GLUI_Spinner(channelPanel, "Red:", &m_filterParameters.channel_colorRed);
            GLUI_Spinner * filterChannelGreen = new GLUI_Spinner(channelPanel, "Green:", &m_filterParameters.channel_colorGreen);
            GLUI_Spinner * filterChannelBlue = new GLUI_Spinner(channelPanel, "Blue:", &m_filterParameters.channel_colorBlue);

            filterChannelRed->set_float_limits(0, 10);
            filterChannelRed->set_float_val(1);
            filterChannelGreen->set_float_limits(0, 10);
            filterChannelGreen->set_float_val(1);
            filterChannelBlue->set_float_limits(0, 10);
            filterChannelBlue->set_float_val(1);

            new GLUI_Button(channelPanel, "Apply", UI_APPLY_CHANNEL, s_gluicallback);
        }

        GLUI_Panel *quantPanel = new GLUI_Panel(filterPanel, "Quantize");
        {
            GLUI_Spinner * filterQuantizeBins = new GLUI_Spinner(quantPanel, "Bins:", &m_filterParameters.quantize_bins);
            filterQuantizeBins->set_int_limits(2, 256);
            filterQuantizeBins->set_int_val(8);
            filterQuantizeBins->set_speed(0.1);

            new GLUI_Button(quantPanel, "Apply", UI_APPLY_QUANTIZE, s_gluicallback);
        }

        GLUI_Panel *specialFilterPanel = new GLUI_Panel(filterPanel, "Dithering"); // YOUR SPECIAL FILTER PANEL
        {
            GLUI_Spinner * filterDitherDegree = new GLUI_Spinner(specialFilterPanel, "Degree:", &m_filterParameters.dither_degree);
            filterDitherDegree->set_int_limits(1, 100);
            filterDitherDegree->set_int_val(5);
            filterDitherDegree->set_speed(0.1);

            new GLUI_Button(specialFilterPanel, "Apply", UI_APPLY_DITHER, s_gluicallback);
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
        m_gluiControlHooks.loadStampButton = new GLUI_Button(imagePanel, "Load Stamp", UI_LOAD_STAMP_BUTTON, s_gluicallback);

        new GLUI_Separator(imagePanel);

        m_gluiControlHooks.saveFileLabel = new GLUI_StaticText(imagePanel, "Will save image: none");

        m_gluiControlHooks.saveCanvasButton = new GLUI_Button(imagePanel, "Save Canvas", UI_SAVE_CANVAS_BUTTON, s_gluicallback);

        loadCanvasEnabled(false);
        loadStampEnabled(false);
        saveCanvasEnabled(false);
    }
    return;
}

void FlashPhotoApp::gluiControl(int controlID)
{

    switch (controlID) {
        case UI_PRESET_RED:
            m_curColorRed = 1;
            m_curColorGreen = 0;
            m_curColorBlue = 0;
            updateColors();
            break;
        case UI_PRESET_ORANGE:
            m_curColorRed = 1;
            m_curColorGreen = 0.5;
            m_curColorBlue = 0;
            updateColors();
            break;
        case UI_PRESET_YELLOW:
            m_curColorRed = 1;
            m_curColorGreen = 1;
            m_curColorBlue = 0;
            updateColors();
            break;
        case UI_PRESET_GREEN:
            m_curColorRed = 0;
            m_curColorGreen = 1;
            m_curColorBlue = 0;
            updateColors();
            break;
        case UI_PRESET_BLUE:
            m_curColorRed = 0;
            m_curColorGreen = 0;
            m_curColorBlue = 1;
            updateColors();
            break;
        case UI_PRESET_PURPLE:
            m_curColorRed = 0.5;
            m_curColorGreen = 0;
            m_curColorBlue = 1;
            updateColors();
            break;
        case UI_PRESET_WHITE:
            m_curColorRed = 1;
            m_curColorGreen = 1;
            m_curColorBlue = 1;
            updateColors();
            break;
        case UI_PRESET_BLACK:
            m_curColorRed = 0;
            m_curColorGreen = 0;
            m_curColorBlue = 0;
            updateColors();
            break;
        case UI_APPLY_BLUR:
            applyFilterBlur();
            break;
        case UI_APPLY_SHARP:
            applyFilterSharpen();
            break;
        case UI_APPLY_MOTION_BLUR:
            applyFilterMotionBlur();
            break;
        case UI_APPLY_EDGE:
            applyFilterEdgeDetect();
            break;
        case UI_APPLY_THRESHOLD:
            applyFilterThreshold();
            break;
        case UI_APPLY_WALLPAPER:
                applyFilterWallpaper();
            break;
        case UI_APPLY_CHROMAKEY:
            applyFilterChromaKey();
            break;
        case UI_APPLY_SATURATE:
            applyFilterSaturate();
            break;
        case UI_APPLY_CHANNEL:
            applyFilterChannel();
            break;
        case UI_APPLY_QUANTIZE:
            applyFilterQuantize();
            break;
        case UI_APPLY_DITHER:
            applyFilterSpecial();
            break;
        case UI_FILE_BROWSER:
            setImageFile(m_gluiControlHooks.fileBrowser->get_file());
            break;
        case UI_LOAD_CANVAS_BUTTON:
            loadImageToCanvas();
            break;
        case UI_LOAD_STAMP_BUTTON:
            loadImageToStamp();
            break;
        case UI_SAVE_CANVAS_BUTTON:
            saveCanvasToFile();
            // Reload the current directory:
            m_gluiControlHooks.fileBrowser->fbreaddir(".");
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

    //could use a loop here
  	//change the sizes of the tools
  	if (m_oldToolSize != m_curToolSize)
  	{
  		tools[0]->scaleMask(m_curToolSize);
  		tools[2]->scaleMask(m_curToolSize);
  		tools[3]->scaleMask(m_curToolSize);
  		tools[4]->scaleMask(m_curToolSize);
  		tools[5]->scaleMask(m_curToolSize);
  		tools[6]->scaleMask(m_curToolSize);
  		tools[7]->scaleMask(m_curToolSize);
      tools[8]->scaleMask(m_curToolSize);
      m_oldToolSize = m_curToolSize;
  	}


    // Forces canvas to update changes made in this function
    m_glui->post_update_main_gfx();
}

// **********************
// *** GLUI CALLBACKS ***

// Edit these functions to provide instructions
// for how FlashPhotoApp should respond to the
// button presses.

void FlashPhotoApp::loadImageToCanvas()
{
    cout << "Load Canvas has been clicked for file " << m_fileName << endl;
    PixelBuffer* temp_buff;
    if(ImportExporter::isValidImageFile(m_fileName)) {
        temp_buff=ImportExporter::importImage(m_fileName, m_displayBuffer);
        if (m_undoRedoStack->getCurrentLastAction() != PixelBufferStack::IMAGE_LOAD ||\
             m_fileName.compare(m_undoRedoStack->getCurrentFileName()) != 0 || !PixelBuffer::comparePixelBuffer(m_displayBuffer, temp_buff)) {
            delete m_displayBuffer;
            m_displayBuffer = temp_buff;
            setWindowDimensions(m_displayBuffer->getWidth(),m_displayBuffer->getHeight());
            m_undoRedoStack->pushBuffer(m_displayBuffer, PixelBufferStack::IMAGE_LOAD , m_fileName);
            updateUndoRedoButtons();
        } else {
            delete temp_buff;
            cout << "Loading image would not change canvas" << endl;
        }
    } else {
        cout << "Image could not be loaded" << endl;
    }
}

void FlashPhotoApp::loadImageToStamp()
{
    cout << "Load Stamp has been clicked for file " << m_fileName << endl;
    PixelBuffer* temp_buff;
    if(ImportExporter::isValidImageFile(m_fileName)) {
        temp_buff=ImportExporter::importImage(m_fileName, m_displayBuffer);
        if (!PixelBuffer::comparePixelBuffer(m_displayBuffer, temp_buff)) {
            tools[9]->setStampBuffer(temp_buff);
            wallpaper->setWallpaper(temp_buff);
            chromakey->setWallpaper(temp_buff);
            if (m_stampBuffer) {
                delete m_stampBuffer;
            }
            m_stampBuffer = temp_buff;
            updateStampButtons();
        }  else {
            cout << "Loading image would not change canvas" << endl;
        }
    } else {
        cout << "Image could not be loaded" << endl;
    }
}

void FlashPhotoApp::saveCanvasToFile()
{
    cout << "Save Canvas been clicked for file " << m_fileName << endl;
    ImportExporter::exportImage(m_fileName, m_displayBuffer);
}

void FlashPhotoApp::applyFilterThreshold()
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

void FlashPhotoApp::applyFilterChannel()
{
    cout << "Apply has been clicked for Channels with red = " << m_filterParameters.channel_colorRed
    << ", green = " << m_filterParameters.channel_colorGreen
    << ", blue = " << m_filterParameters.channel_colorBlue << endl;
    //At this time there is no limit to filter channel applies pushed to the pixel buffer stack
    channels->setColors(m_filterParameters.channel_colorRed,m_filterParameters.channel_colorGreen,m_filterParameters.channel_colorBlue);
    channels->applyFilter(m_displayBuffer);
    m_undoRedoStack->pushBuffer(m_displayBuffer, PixelBufferStack::APPLY_CHANNEL, m_fileName);
    updateUndoRedoButtons();
    cout << "Applied Channels" << endl;
}

void FlashPhotoApp::applyFilterBlur()
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

void FlashPhotoApp::applyFilterSharpen()
{
    cout << "Apply has been clicked for Sharpen with amount = " << m_filterParameters.sharpen_amount << endl;
    sharpen->setFloatParameter(m_filterParameters.sharpen_amount);
    if(sharpen->paramHasChanged())
    {
        sharpen->changeKernel((int) m_filterParameters.sharpen_amount);
    }
    sharpen->applyFilter(m_displayBuffer);
    //At this time there is no limit to filter Sharpen applies pushed to the pixel buffer stack
    m_undoRedoStack->pushBuffer(m_displayBuffer, PixelBufferStack::APPLY_SHARP,m_fileName);
    updateUndoRedoButtons();
    cout << "Applied Sharpen" << endl;
}

void FlashPhotoApp::applyFilterMotionBlur()
{
    cout << "Apply has been clicked for Sharpen with amount = " << m_filterParameters.motionBlur_amount
    << " and direction " << m_filterParameters.motionBlur_direction << endl;
    motionblur->setIntParameter(m_filterParameters.motionBlur_direction);
    motionblur->setFloatParameter(m_filterParameters.motionBlur_amount);
    if(motionblur->paramHasChanged())
    {
      motionblur->changeKernel((int) m_filterParameters.motionBlur_amount);
    }
    //At this time there is no limit to filter direction blur applies pushed to the pixel buffer stack
    motionblur->applyFilter(m_displayBuffer);
    m_undoRedoStack->pushBuffer(m_displayBuffer, PixelBufferStack::APPLY_MOTION_BLUR, m_fileName); 
    updateUndoRedoButtons();
    cout << "Applied MotionBlur" << endl;
}

void FlashPhotoApp::applyFilterEdgeDetect() {
    cout << "Apply has been clicked for Edge Detect" << endl;
    //At this time there is no limit to filter edge detect applies pushed to the pixel buffer stack
    edgedetect->applyFilter(m_displayBuffer);
    m_undoRedoStack->pushBuffer(m_displayBuffer, PixelBufferStack::APPLY_EDGE, m_fileName); 
    updateUndoRedoButtons();
    cout << "Applied EdgeDetect" << endl;
}

void FlashPhotoApp::applyFilterSaturate()
{
    cout << "Apply has been clicked for Saturate with amount = " << m_filterParameters.saturation_amount << endl;
    //At this time there is no limit to filtersaturate applies pushed to the pixel buffer stack
    saturate->setFloatParameter(m_filterParameters.saturation_amount);
    saturate->applyFilter(m_displayBuffer);
    m_undoRedoStack->pushBuffer(m_displayBuffer, PixelBufferStack::APPLY_SATURATE, m_fileName); 
    updateUndoRedoButtons();
    cout << "Applied Saturation" << endl;
}

void FlashPhotoApp::applyFilterQuantize() {
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

void FlashPhotoApp::applyFilterSpecial() {
    cout << "Apply has been clicked for Special" << endl;
    dither->setFloatParameter((float)m_filterParameters.dither_degree);
    dither->applyFilter(m_displayBuffer);
    //At this time there is no limit to filter dither applies pushed to the pixel buffer stack
    m_undoRedoStack->pushBuffer(m_displayBuffer, PixelBufferStack::APPLY_DITHER, m_fileName); 
    updateUndoRedoButtons();
    cout << "Applied Dithering" << endl;
}

void FlashPhotoApp::applyFilterWallpaper() {
    cout << "Apply has been clicked for Wallpaper" << endl;
    if(wallpaper->paramHasChanged() || m_undoRedoStack->getCurrentLastAction() != PixelBufferStack::APPLY_WALLPAPER) {
        wallpaper->applyFilter(m_displayBuffer);
        m_undoRedoStack->pushBuffer(m_displayBuffer, PixelBufferStack::APPLY_WALLPAPER,m_fileName); //this is the action code for Wallpaper
        updateUndoRedoButtons();
        cout << "Applied Wallpaper" << endl;
    } else {
        cout << "Action would not change canvas" << endl;
    }
}

void FlashPhotoApp::applyFilterChromaKey() {
    cout << "Apply has been clicked for Chroma Key" << endl;
    chromakey->setFloatParameter(m_filterParameters.chromakey_fudge_factor);
    chromakey->setFloatSecondaryParameter(m_filterParameters.chromakey_interpolation_factor);
    chromakey->setColors(m_curColorRed, m_curColorGreen, m_curColorBlue);
    if(chromakey->paramHasChanged() || m_undoRedoStack->getCurrentLastAction() != PixelBufferStack::APPLY_CHROMAKEY) {
        chromakey->applyFilter(m_displayBuffer);
        m_undoRedoStack->pushBuffer(m_displayBuffer, PixelBufferStack::APPLY_CHROMAKEY, m_fileName); //this is the action code for Chromakey
        updateUndoRedoButtons();
        cout << "Applied Chroma Key" << endl;
    }  else {
        cout << "Action would not change canvas" << endl;
    }
}


void FlashPhotoApp::undoOperation()
{
    cout << "Undoing..." << endl;
    PixelBuffer* transitionBuffer;
    if(m_undoRedoStack->checkUpStack()) {
        m_undoRedoStack->climbStack();
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

void FlashPhotoApp::redoOperation()
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

void FlashPhotoApp::buttonEnabled(GLUI_Button * button, bool enabled) {
    if(enabled) button->enable();
    else button->disable();
    button->redraw();
}

void FlashPhotoApp::redoEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.redoButton, enabled);
}

void FlashPhotoApp::undoEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.undoButton, enabled);
}

void FlashPhotoApp::saveCanvasEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.saveCanvasButton, enabled);
}

void FlashPhotoApp::loadStampEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.loadStampButton, enabled);
}

void FlashPhotoApp::loadCanvasEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.loadCanvasButton, enabled);
}

void FlashPhotoApp::wallpaperEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.wallpaperButton, enabled);
}

void FlashPhotoApp::chromakeyEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.chromakeyButton, enabled);
}

void FlashPhotoApp::updateColors() {
    m_gluiControlHooks.spinnerBlue->set_float_val(m_curColorBlue);
    m_gluiControlHooks.spinnerGreen->set_float_val(m_curColorGreen);
    m_gluiControlHooks.spinnerRed->set_float_val(m_curColorRed);
}

//Used to control glui buttons for saving and loading, as well as updating the m_fileName global variable
void FlashPhotoApp::setImageFile(const std::string & fileName)
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
        loadStampEnabled(true);
        loadCanvasEnabled(true);

        m_gluiControlHooks.currentFileLabel->set_text((std::string("Will load: ") + imageFile).c_str());
        m_gluiControlHooks.fileNameBox->set_text(imageFile);

    } else {
        loadStampEnabled(false);
        loadCanvasEnabled(false);

        m_gluiControlHooks.currentFileLabel->set_text("Will load: none");
    }
}

void FlashPhotoApp::initGraphics() {
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
