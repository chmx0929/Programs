#include <setjmp.h>
#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include "jpeglib.h"
#include "jconfig.h"
#include "png.h"

#include "ColorData.h"
#include "PixelBuffer.h"
#include "ImportExporter.h"


PixelBuffer* ImportExporter::read_jpeg(const std::string & f_name, ColorData backgroundColor) {                  //Provide pixel buffer to be modified
    PixelBuffer* temp_buffer;
    /* This struct contains the JPEG decompression parameters and pointers to
     * working space (which is allocated as needed by the JPEG library).
     */
    struct jpeg_decompress_struct cinfo;
    /* We use our private extension JPEG error handler.
     * Note that this struct must live as long as the main JPEG parameter
     * struct, to avoid dangling-pointer problems.
     */
    struct jpeg_error_mgr jerr;
    /* In this example we want to open the input file before doing anything else,
     * so that the setjmp() error recovery below can assume the file is open.
     * VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
     * requires it in order to read binary files.
     */
    FILE *infile = fopen( f_name.c_str() , "rb" );
    unsigned long location = 0;/* The variable to store location */
    JSAMPROW row_pointer[1]; /* pointer to JSAMPLE row[s] */
    unsigned char *raw_image = NULL; /* Array to store each pixel's data */
    /* In this example we want to open the input file before doing anything else,
     * so that the setjmp() error recovery below can assume the file is open.
     * VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
     * requires it in order to read binary files.
     */
    if ( !infile )
    {
        printf("Error opening jpeg file %s\n!", f_name.c_str() );
    }
    /* We set up the normal JPEG error routines, then override error_exit. */
    cinfo.err = jpeg_std_error( &jerr );
    /* Now we can initialize the JPEG decompression object. */
    jpeg_create_decompress( &cinfo );
    /* Specify data source (eg, a file) */
    jpeg_stdio_src( &cinfo, infile );
    /* Read file parameters with jpeg_read_header() */
    jpeg_read_header( &cinfo, TRUE );
    /* Start decompressor */
    jpeg_start_decompress( &cinfo );
    /* JSAMPLEs per row in output buffer */
    raw_image = (unsigned char*) malloc( cinfo.output_width*cinfo.output_height*cinfo.num_components );
    assert(raw_image);
    /* Make a one-row-high sample array that will go away when done with image */
    row_pointer[0] = (unsigned char *)malloc( cinfo.output_width*cinfo.num_components);
    assert(row_pointer[0]);
    /* Here we use the library's state variable cinfo.output_scanline as the
     * loop counter, so that we don't have to keep track ourselves.
     */
    while( cinfo.output_scanline < cinfo.image_height )
    {
        jpeg_read_scanlines( &cinfo, row_pointer, 1 );
        for( int i=0; i<cinfo.image_width*cinfo.num_components;i++)
            raw_image[location++] = row_pointer[0][i];
    }
    /* Finish decompression */
    jpeg_finish_decompress( &cinfo );
    /* Create temp pixelbuffer to store each pixel's image data(RGB) */
    temp_buffer = new PixelBuffer( cinfo.image_width, cinfo.image_height, backgroundColor);
    /* Set the values(RGB) to temp pixelbuffer */
    for (int y=0; y < cinfo.image_height; y++){
        for (int x=0; x < cinfo.image_width; x++){
            float R =(float)raw_image[(y*cinfo.image_width*3)+(x*3)+0]/255;
            float G =(float)raw_image[(y*cinfo.image_width*3)+(x*3)+1]/255;
            float B = (float)raw_image[(y*cinfo.image_width*3)+(x*3)+2]/255;
            temp_buffer->setPixel(x,cinfo.image_height - (y+1) , ColorData(R,G,B));
        }
    }
    /* Release JPEG decompression object */
    jpeg_destroy_decompress( &cinfo );
    /* Release the row_pointer */
    free( row_pointer[0] );
    free(raw_image);
    /* After finish_decompress, we can close the input file.
     * Here we postpone it until after no more JPEG errors are possible,
     * so as to simplify the setjmp error logic above.  (Actually, I don't
     * think that jpeg_destroy can do an error exit, but why assume anything...)
     */
    fclose( infile );
    return temp_buffer;
}

PixelBuffer* ImportExporter::read_png(const std::string & f_name, ColorData backgroundColor) {          //Provide pixel buffer to be modified
    PixelBuffer* temp_buffer;
    int width, height; /* Variable to store image size*/
    png_byte color_type; /* Variable to store color type */
    png_byte bit_depth; /* Variable to store bit depth */
    png_bytep *row_pointers; /* Array to store each pixel data(RBGA) */
    /* Open the file */
    FILE *fp = fopen(f_name.c_str(), "rb");
    /* Variable to store png structure */
    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    /* Variable to store png information */
    png_infop info = png_create_info_struct(png);
    /* Set error handling if you are using the setjmp/longjmp method (this is
    * the normal method of doing things with libpng).  REQUIRED unless you
    * set up your own error handlers in the png_create_read_struct() earlier.
    */
    if(setjmp(png_jmpbuf(png))) abort();
    /* Set up the input control if you are using standard C streams */
    png_init_io(png, fp);
    /* The call to png_read_info() gives us all of the information from the
     * PNG file before the first IDAT (image data chunk).  REQUIRED
     */
    png_read_info(png, info);
    /* Set values for each variable */
    width      = png_get_image_width(png, info);
    height     = png_get_image_height(png, info);
    color_type = png_get_color_type(png, info);
    bit_depth  = png_get_bit_depth(png, info);
    if(bit_depth == 16)
        png_set_strip_16(png);
    if(color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png);
    if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png);
    if(png_get_valid(png, info, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png);
    if(color_type == PNG_COLOR_TYPE_RGB ||color_type == PNG_COLOR_TYPE_GRAY ||color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
    if(color_type == PNG_COLOR_TYPE_GRAY ||color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png);
    /* Optional call to gamma correct and add the background to the palette
     * and update info structure.  REQUIRED if you are expecting libpng to
     * update the palette for you (ie you selected such a transform above).
     */
    png_read_update_info(png, info);
    /* Create the pointer array */
    row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    assert(row_pointers);
    for(int y = 0; y < height; y++) {
        row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
        assert(row_pointers[y]);
    }
    /* Read the entire image in one go */
    png_read_image(png, row_pointers);
    /* Create temp pixelbuffer to store each pixel's image data(RGBA) */
    temp_buffer = new PixelBuffer( width, height, backgroundColor);
    /* Set the values(RGB) to temp pixelbuffer */
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            float R =(float)row_pointers[y][x*4]/255.0;
            float G =(float)row_pointers[y][x*4+1]/255.0;
            float B =(float)row_pointers[y][x*4+2]/255.0;
            float A =(float)row_pointers[y][x*4+3]/255.0;
            temp_buffer->setPixel(x,height - (y+1) , ColorData(R,G,B,A));
        }
    }
    for(int y = 0; y < height; y++) {
        free(row_pointers[y]);
    }
    free(row_pointers);
    fclose(fp);
    return temp_buffer;
}

PixelBuffer* ImportExporter::importImage(const std::string & f_name, PixelBuffer* p_buff) {
    ColorData backgroundColor = p_buff->getBackgroundColor();
    if(isValidImageFile(f_name)){
        if (hasSuffix(f_name, ".jpg")|| hasSuffix(f_name, ".jpeg")){
            return read_jpeg(f_name, backgroundColor);
        }else{
            return read_png(f_name, backgroundColor);
        }
    }
}


void ImportExporter::write_png(const std::string & f_name, PixelBuffer* p_buff){
    /* Variable to store image size*/
    int width = p_buff->getWidth();
    int height = p_buff->getHeight();
    /* Array to store each pixel data(RBGA) */
    png_bytep *row_pointers;
    /* Open the file */
    FILE *fp = fopen(f_name.c_str(), "wb");
    /* Check the file and abort if inofrmation not correct */
    if(!fp) abort();
    /* Variable to store png structure */
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) abort();
    /* Variable to store png information */
    png_infop info = png_create_info_struct(png);
    if (!info) abort();
    if (setjmp(png_jmpbuf(png))) abort();
    /* Set up the output control if you are using standard C streams */
    png_init_io(png, fp);
    /* Set the image information here.  Width and height are up to 2^31,
     * bit_depth is one of 1, 2, 4, 8, or 16, but valid values also depend on
     * the color_type selected. color_type is one of PNG_COLOR_TYPE_GRAY,
     * PNG_COLOR_TYPE_GRAY_ALPHA, PNG_COLOR_TYPE_PALETTE, PNG_COLOR_TYPE_RGB,
     * or PNG_COLOR_TYPE_RGB_ALPHA.  interlace is either PNG_INTERLACE_NONE or
     * PNG_INTERLACE_ADAM7, and the compression_type and filter_type MUST
     * currently be PNG_COMPRESSION_TYPE_BASE and PNG_FILTER_TYPE_BASE. REQUIRED
     */
    png_set_IHDR(
        png,
        info,
        width, height,
        8,
        PNG_COLOR_TYPE_RGBA,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT
    );
    /* Create the pointer array */
    row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    assert(row_pointers);
    /* Set up pointers into your "image" byte array */
    for(int y = 0; y < height; y++) {
        row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
        assert(row_pointers[y]);
    }
    /* Write the file header information.  REQUIRED */
    png_write_info(png, info);
    /* Set the values(RGBA) of display pixelbuffer to array */
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            ColorData tempColor =  p_buff->getPixel(x,height - (y+1));
            row_pointers[y][x*4] =tempColor.getRed()*255.0;
            row_pointers[y][x*4+1] =tempColor.getGreen()*255.0;
            row_pointers[y][x*4+2] =tempColor.getBlue()*255.0;
            row_pointers[y][x*4+3] =tempColor.getAlpha()*255.0;
        }
    }
    /* Write out the entire image data in one call */
    png_write_image(png, row_pointers);
    /* It is REQUIRED to call this to finish writing the rest of the file */
    png_write_end(png, NULL);
    /* Release the array */
    for(int y = 0; y < height; y++) {
        free(row_pointers[y]);
    }
    free(row_pointers);
    fclose(fp);
}

void ImportExporter::write_jpeg(const std::string & f_name, PixelBuffer* p_buff){
    /* Array to store each pixel's data */
    unsigned char *raw_image = NULL;
    /* This struct contains the JPEG compression parameters and pointers to
     * working space (which is allocated as needed by the JPEG library).
     * It is possible to have several such structures, representing multiple
     * compression/decompression processes, in existence at once.  We refer
     * to any one struct (and its associated working data) as a "JPEG object".
     */
    struct jpeg_compress_struct cinfo;
    /* This struct represents a JPEG error handler.  It is declared separately
     * because applications often want to supply a specialized error handler
     * (see the second half of this file for an example).  But here we just
     * take the easy way out and use the standard error handler, which will
     * print a message on stderr and call exit() if compression fails.
     * Note that this struct must live as long as the main JPEG parameter
     * struct, to avoid dangling-pointer problems.
     */
    struct jpeg_error_mgr jerr;
    /* pointer to JSAMPLE row[s] */
    JSAMPROW row_pointer[1];
    /* Here we use the library-supplied code to send compressed data to a
     * stdio stream.  You can also write your own code to do something else.
     * VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
     * requires it in order to write binary files.
     */
    FILE *outfile = fopen(f_name.c_str(), "wb" );
    /* Check the file */
    if ( !outfile )
    {
        printf("Error opening output jpeg file %s\n!", f_name.c_str() );
        abort();
    }
    /* We set up the normal JPEG error routines, then override error_exit. */
    cinfo.err = jpeg_std_error( &jerr );
    /* Now we can initialize the JPEG decompression object. */
    jpeg_create_compress(&cinfo);
    /* Step 2: specify data source (eg, a file) */
    jpeg_stdio_dest(&cinfo, outfile);
    /* Set data to each variable */
    cinfo.image_width = p_buff->getWidth();
    cinfo.image_height = p_buff->getHeight();
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;
    /* Now use the library's routine to set default compression parameters.
     * (You must set at least cinfo.in_color_space before calling this,
     * since the defaults depend on the source color space.)
     */
    jpeg_set_defaults( &cinfo );
    /* Start decompressor */
    jpeg_start_compress( &cinfo, TRUE );
    /* Create the pointer array */
    raw_image = (unsigned char*)malloc(cinfo.image_width*cinfo.image_height*3);
    assert(raw_image);
    /* Set the values(RGB) of display pixelbuffer to array */
    for (int i=0; i < cinfo.image_height; i++){
        for (int j=0; j < cinfo.image_width; j++){
            ColorData tempColor = p_buff->getPixel(j,cinfo.image_height - (i+1));
            raw_image[(i*cinfo.image_width*3)+(j*3)+0] =tempColor.getRed() * 255;
            raw_image[(i*cinfo.image_width*3)+(j*3)+1] =tempColor.getGreen() * 255;
            raw_image[(i*cinfo.image_width*3)+(j*3)+2] =tempColor.getBlue() * 255;
        }
    }
    /* Here we use the library's state variable cinfo.next_scanline as the
     * loop counter, so that we don't have to keep track ourselves.
     * To keep things simple, we pass one scanline per call; you can pass
     * more if you wish, though.
     */
    while( cinfo.next_scanline < cinfo.image_height )
    {
        row_pointer[0] = &raw_image[ cinfo.next_scanline * cinfo.image_width * 3];
        (void)jpeg_write_scanlines( &cinfo, row_pointer, 1 );
    }
    /* Finish compression */
    jpeg_finish_compress( &cinfo );
    /* After finish_compress, we can close the output file. */
    fclose( outfile );
    /* This is an important step since it will release a good deal of memory. */
    jpeg_destroy_compress( &cinfo );
    free(raw_image);
}

void ImportExporter::exportImage(const std::string & f_name, PixelBuffer* p_buff) {
    if (hasSuffix(f_name, ".jpg")|| hasSuffix(f_name, ".jpeg")){
        write_jpeg(f_name, p_buff);
    }else{
        write_png(f_name, p_buff);
    }
}


bool ImportExporter::hasSuffix(const std::string & str, const std::string & suffix){
    return str.find(suffix,str.length()-suffix.length()) != std::string::npos;
}


bool ImportExporter::hasSupportedExtension(const std::string & name) {

    if (hasSuffix(name, ".png")
        || hasSuffix(name, ".jpg")
        || hasSuffix(name, ".jpeg")
        )
        return true;
    else
        return false;
}

bool ImportExporter::isValidImageFile(const std::string & name) {

    FILE *f;
    bool isValid = false;
    if (hasSupportedExtension(name)) {
        if ((f = fopen( name.c_str(), "r"))) {
            isValid = true;
            fclose(f);
        }
    }
    return isValid;
}
