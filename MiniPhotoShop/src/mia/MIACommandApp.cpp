#include "MIACommandApp.h"
#include "libphoto.h"
#include <iostream>
#include <string>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sstream>
#include <cstdio>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

MIACommandApp::MIACommandApp(int argc, char* argv[])
{
    m_displayBuffer = new PixelBuffer(800, 800, ColorData(1,1,0.95));
    m_compareBuffer = new PixelBuffer(800, 800, ColorData(1,1,0.95));
    sharpen = new F_Sharpen(m_filterParameters.sharpen_amount);
    channels = new F_Channels(m_filterParameters.multiply_colorRed, m_filterParameters.multiply_colorGreen, m_filterParameters.multiply_colorBlue);
    edgedetect = new F_EdgeDetect();
    threshold = new F_Threshold(m_filterParameters.threshold_amount);
    quantize = new F_Quantize(m_filterParameters.quantize_bins);
    blur = new F_Blur(m_filterParameters.blur_amount);
    saturate = new F_Saturate(m_filterParameters.saturate_amount);
    inDir = false;
}

MIACommandApp::~MIACommandApp()
{
    if (m_displayBuffer) {
        delete m_displayBuffer;
    }
    delete grayscale;
    delete sharpen;
    delete channels;
    delete edgedetect;
    delete threshold;
    delete quantize;
    delete blur;
    delete saturate;

}

void MIACommandApp::loadImageToCanvas()
{
    cout << "Load Canvas has been clicked for file " << m_fileName << endl;
    PixelBuffer* temp_buff;
    temp_buff=ImportExporter::importImage(m_fileName, m_displayBuffer);
    m_displayBuffer = temp_buff;
    cout<<"load image done"<<endl;
}

void MIACommandApp::saveCanvasToFile()
{
    cout << "Save Canvas been clicked for file " << m_fileName << endl;
    ImportExporter::exportImage(m_fileName, m_displayBuffer);
}

void MIACommandApp::applyFilterSharpen()
{
    cout << "Apply has been clicked for Sharpen with amount = " << m_filterParameters.sharpen_amount << endl;
    sharpen->setFloatParameter(m_filterParameters.sharpen_amount);
    if(sharpen->paramHasChanged())
    {
        sharpen->changeKernel((int) m_filterParameters.sharpen_amount);
    }
    sharpen->applyFilter(m_displayBuffer);
    cout << "Applied Sharpen" << endl;
}

void MIACommandApp::applyFilterEdgeDetect() {
    cout << "Apply has been clicked for Edge Detect" << endl;
    edgedetect->applyFilter(m_displayBuffer);
    cout << "Applied EdgeDetect" << endl;
}

void MIACommandApp::applyFilterThreshold()
{
    cout << "Apply has been clicked for Threshold has been clicked with amount =" << m_filterParameters.threshold_amount << endl;
    threshold->setFloatParameter(m_filterParameters.threshold_amount);
    threshold->applyFilter(m_displayBuffer);
    cout << "Applied Threshold" << endl;
}

void MIACommandApp::applyFilterMultiplyRGB()
{
    cout << "Apply has been clicked for Multiply RGB with red = " << m_filterParameters.multiply_colorRed
    << ", green = " << m_filterParameters.multiply_colorGreen
    << ", blue = " << m_filterParameters.multiply_colorBlue << endl;

    channels->setColors(m_filterParameters.multiply_colorRed,m_filterParameters.multiply_colorGreen,m_filterParameters.multiply_colorBlue);
    channels->applyFilter(m_displayBuffer);
    cout << "Applied MultiplyRGB" << endl;
}

void MIACommandApp::applyFilterGrayScale()
{
    cout << "Apply has been clicked for Grayscale" << endl;
    grayscale->applyFilter(m_displayBuffer);
}

void MIACommandApp::applyFilterQuantize() {
    cout << "Apply has been clicked for Quantize with bins = " << m_filterParameters.quantize_bins << endl;
    quantize->setIntParameter(m_filterParameters.quantize_bins);
    quantize->applyFilter(m_displayBuffer);

}

void MIACommandApp::applyFilterBlur()
{
    cout << "Apply has been clicked for Blur with amount = " << m_filterParameters.blur_amount << endl;
    blur->setFloatParameter(m_filterParameters.blur_amount);
    if(blur->paramHasChanged())
    {
        blur->changeKernel((int) m_filterParameters.blur_amount);
    }
    blur->applyFilter(m_displayBuffer);
    cout << "Applied Blur" << endl;
}

void MIACommandApp::applyFilterSaturate()
{
    cout << "Apply has been clicked for Saturate with amount = " << m_filterParameters.saturate_amount << endl;
    saturate->setFloatParameter(m_filterParameters.saturate_amount);
    saturate->applyFilter(m_displayBuffer);
    cout << "Applied Saturation" << endl;
}

int MIACommandApp::comparePixelBuffer(const PixelBuffer * le_buff, const PixelBuffer * re_buff) {
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

void MIACommandApp::executeCommand(int argc, char* argv[])
{
    if(validateCommand(argc,argv)||inDir)
    {
        bool isInput =true;
        for (int i=1;i<argc;i++)
        {
            string command = argv[i];
            //Help Command
            if(command=="-h")
            {
                cout<<"Complete list of command-line arguments and functionalities:"<<endl;
                cout<<'\t'<<"-sharpen <integer>"<<endl;
                cout<<'\t'<<"-edgedetect"<<endl;
                cout<<'\t'<<"-thresh <float>"<<endl;
                cout<<'\t'<<"-quantize <int>"<<endl;
                cout<<'\t'<<"-blur <float>"<<endl;
                cout<<'\t'<<"-saturate <float>"<<endl;
                cout<<'\t'<<"-multrgb <float>,<float>,<float>"<<endl;
                cout<<'\t'<<"-compare"<<endl;
                cout<<'\t'<<"./Mia -h    Help document"<<endl;
                cout<<'\t'<<"./Mia in.jpg out.png   Transfer Image type"<<endl;
                cout<<" "<<endl;
                cout<<"Normally, you need to give a vaild image name or a directory"<<endl;
                cout<<"as the first parameter, then follow with a valid command and"<<endl;
                cout<<"its parameter (if need one)."<<endl;
                cout<<" "<<endl;
                cout<<"A valid file name is always required to be saved as the output."<<endl;
                cout<<" "<<endl;
                cout<<"If use '-comapre', remember to put that command as the second"<<endl;
                cout<<"last parameter and give a valid image to be the comparee as the"<<endl;
                cout<<"last parameter."<<endl;
                cout<<" "<<endl;
                cout<<"Examples:"<<endl;
                cout<<'\t'<<"./Mia ./testImages/snaily.jpg ./testImages/snaily.out.png"<<endl;
                cout<<'\t'<<"./Mia ./testImages/snaily.jpg -sharpen 5 ./testImages/snaily.out.jpg"<<endl;
                cout<<'\t'<<"./Mia ./testImages/snaily.jpg -sharpen 5 -edgedetect -thresh 3.0 -compare ./testImages/snaily2.jpg"<<endl;
                break;
            }
            //Command and there exists a image
            else if(command[0]=='-'&&isInput==false)
            {
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
                    applyFilterMultiplyRGB();
                    i+=1;
                }
                if("-compare"==command){
                    int t = comparePixelBuffer(m_displayBuffer,m_compareBuffer);
                    if(t){
                        cout<<"These two are same."<<endl;
                    }
                    else
                    {
                        cout<<"These two are different."<<endl;
                    }
                }
                else
                {
                    //std::cout<<"Invalid Command Line, please refer to ./Mia -h for more help. Meow~"<<endl;
                }
            }

            //File or folder name
            else if(command[0]!='-')
            {
                if(isInput)
                {
                    isInput = false;
                    //laod images
                    if(isValidImageFileName(command))
                    {
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
                                    char* infile = new char[command.length()+strlen(ent->d_name)+2];
                                    strcpy (infile, command.c_str());
                                    strcat (infile,"/");
                                    strcat (infile,ent->d_name);
                                    argv[i] = infile;
                                    inDir = true;
                                    executeCommand(argc,argv);
                                }
                            }
                            closedir (dir);
                        }
                        else{
                            /* could not open directory */
                            perror ("Could not open directory");
                        }
                        return;
                    }
                }
                //output
                else
                {
                    isInput = true;
                    string s = argv[argc-2];
                    if(s!="-compare")
                    {
                        //save images
                        if(hasSuffix(command,".png") || hasSuffix(command,".jpg"))
                        {
                            m_fileName = command;
                        }
                        //save to directory
                        else
                        {
                            struct stat st = {0};
                            std::cout<<stat(argv[argc-1], &st)<<std::endl;
                            if (stat(argv[argc-1], &st) != 0) {
                              std::cout<<"1"<<std::endl;
                              int t = mkdir(argv[argc-1], 0700);
                            }
                            std::cout<<m_directory.c_str()<<std::endl;
                            m_fileName.replace(0,m_directory.length(),command);
                        }
                        saveCanvasToFile();
                    }
                }
            }
        }
    }
    else
    {
        std::cout<<"Invalid Command Line, please refer to ./Mia -h for more help. Meow~"<<endl;
    }
}

int MIACommandApp::validateCommand(int argc, char* argv[])
{
    if (argc < 3 && strncmp(argv[1], "-h", 2) == 0)
    {
        //std::cout<<"Help doc"<<std::endl;
        return 1;
    }

    if (argc < 3)
    {
        return 0;
    }

    std::string first_arg = argv[1];
    std::string second_arg = argv[2];
    std::string last_arg = argv[argc-1];


    if (argc < 4 && isValidImageFile(first_arg) && isValidImageFileName(second_arg) && hasDifferentSuffix(first_arg, second_arg))
    {
        //std::cout<<"Transfer img type."<<std::endl;
        return 1;
    }

    if(isValidDir(first_arg)&&isValidDir(last_arg)){
        return 1;
    }

    if (argc > 3 && isValidImageFile(first_arg))
    {
        std::string third_arg = argv[3];
        std::string second_last_arg = argv[argc-2];


        if (hasCompare(argc, argv))
        {
            if(second_last_arg != "-compare")
            {
                //cout<<"Error! Has compare but not the second last!"<<endl;
                return 0;
            }
            else if (!isValidImageFile(last_arg))
            {
                //cout<<"Error! Has compare but comparee is not a vaild img!"<<endl;
                return 0;
            }
            else if(second_last_arg == "-compare"&&isValidImageFile(first_arg))
            {
                PixelBuffer* temp_buff;
                temp_buff=ImportExporter::importImage(last_arg, m_compareBuffer);
                m_compareBuffer = temp_buff;
                return 1;
            }
        }


        if (isCommand(second_arg) && isValidImageFileName(last_arg))
        {
            if (second_arg  == "-edgedetect")
            {
                if (argc == 4)
                {
                    //cout<<"OK! edgedetecting now"<<endl;
                    return 1;
                }
                else
                {
                    if (validateRest(argc, argv, 3))
                    {
                        //cout<<"OK! Looks like a long command"<<endl;
                        return 1;
                    }
                    else
                    {
                        //cout<<"Error! with edgedetect "<<endl;
                        return 0;
                    }
                }
            }
            else
            {
                if (isNum(third_arg))
                {
                    if (argc == 5)
                    {
                        //cout<<"OK!"<<endl;
                        return 1;
                    }
                    else
                    {
                        if (validateRest(argc, argv, 4))
                        {
                            //cout<<"OK!"<<endl;
                            return 1;
                        }
                        else
                        {
                            //cout<<"Error! num ok"<<endl;
                            return 0;
                        }
                    }
                }
                else
                {
                    //cout<<"Error! num not ok"<<endl;
                    return 0;
                }
            }
        }
        else
        {
            //cout<<second_arg<<" "<<last_arg<<endl;

            //cout<<"Error! 2nd is not command and last not valid file"<<endl;
            return 0;
        }
    }
    else
    {
        //cout<<"Error! argc > 3 but last is not valid img file"<<endl;
        return 0;
    }
    return 0;
}

int MIACommandApp::validateRest(int argc, char* argv[], int from)
{
    if (hasCompare(argc, argv))
    {
        argc = argc-1;
    }


    for (int i = from; i < argc-1; i++)
    {
        //std::cout<<i <<" ";

        string temp = argv[i];
        if (isNum(temp))
        {
            return 0;
        }

        if (temp != "-edgedetect")
        {
            if (isCommand(temp))
            {
                string next = argv[i+1];
                if (!isNum(next))
                {
                    return 0;
                }
                i = i + 1;
            }
            else
            {
                return 0;
            }
        }
    }
    return 1;
}

bool MIACommandApp::hasSuffix(const std::string & str, const std::string & suffix)
{
    return str.find(suffix,str.length()-suffix.length()) != std::string::npos;
}

int MIACommandApp::isValidImageFileName(const std::string & name)
{
    if (hasSuffix(name, ".png") || hasSuffix(name, ".jpg") || hasSuffix(name, ".jpeg"))
        return 1;
    else
        return 0;
}

int MIACommandApp::isValidImageFile(const std::string & name)
{
    FILE *file;

    if (isValidImageFileName(name))
    {
        if ((file = fopen( name.c_str(), "r")))
        {
            fclose(file);
            return 1;
        }
    }
    return 0;
}

int MIACommandApp::isValidDir(const std::string & name)
{
    return !isNum(name)&&!isValidImageFileName(name)&&!isCommand(name);
}


int MIACommandApp::isCommand(const std::string & name)
{
    if (name == "-sharpen")
    {
        return 1;
    }
    else if (name == "-edgedetect")
    {
        return 1;
    }
    else if (name == "-thresh")
    {
        return 1;
    }
    else if (name == "-quantize")
    {
        return 1;
    }
    else if (name == "-blur")
    {
        return 1;
    }
    else if (name == "-saturate")
    {
        return 1;
    }
    else if (name == "-multrgb")
    {
        return 1;
    }
    else if (name == "-compare")
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int MIACommandApp::isNum(const std::string & name)
{
    int has_2_comma = 0;
    int point=0;

    for(int t=0;t<name.length();t++)
    {
        if(name[t]==',')
        {
            has_2_comma++;
        }
    }

    if (has_2_comma==2)
    {
        int dot_counter = 0;
        for (int i = 0; i < name.length(); i++)
        {
            if (name[i] == '.')
            {
                dot_counter++;
                if(dot_counter > 1)
                {
                    //std::cout<< "Not a num before ,"<<std::endl;
                    return 0;
                }
            }
            else if(name[i]==','||i==name.length()-1)
            {
                if(has_2_comma==2)
                {
                    string value_red = name.substr(point,i);
                    has_2_comma=1;
                    i++;
                    point=i;
                    dot_counter=0;
                    m_filterParameters.multiply_colorRed = atof(value_red.c_str());
                    //cout<<value_red<<endl;
                }
                else if(has_2_comma==1)
                {
                    string value_green = name.substr(point,i-point);
                    has_2_comma=0;
                    i++;
                    point=i;
                    dot_counter=0;
                    m_filterParameters.multiply_colorGreen = atof(value_green.c_str());
                    //cout<<value_green<<endl;
                }
                else if(has_2_comma==0)
                {
                    string value_blue = name.substr(point,i-point+1);
                    m_filterParameters.multiply_colorBlue = atof(value_blue.c_str());
                    has_2_comma=-1;
                    //cout<<value_blue<<endl;
                    return 1;
                }
            }
            else if (name[i] < '0' || name[i] > '9')
            {
                //std::cout<< "No a num!"<<std::endl;
                return 0;
            }
        }
    }
    else
    {
        int dot_counter = 0;
        for (int i = 0; i < name.length(); i++)
        {
            if (name[i] == '.')
            {
                dot_counter++;
                if(dot_counter > 1)
                {
                    //std::cout<< "Doesn't have 2 , and not a number"<<std::endl;
                    return 0;
                }
            }
            else if (name[i] < '0' || name[i] > '9')
            {
                //std::cout<< "Just No a number anyway!"<<std::endl;
                return 0;
            }
        }
        return 1;
    }
    return 0;
}



int MIACommandApp::hasCompare(int argc, char* argv[])
{
    for (int i = 0; i < argc; i++)
    {
        string temp = argv[i];

        if(temp == "-compare")
        {
            return 1;
        }
    }
    return 0;
}

int MIACommandApp::hasDifferentSuffix(const std::string & name1, const std::string & name2)
{
    if(name1[name1.length()-2]!=name2[name2.length()-2])
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
