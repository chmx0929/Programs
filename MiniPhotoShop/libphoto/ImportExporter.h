//
//  ImportExporter.h
//  
//

#ifndef IMPORTEXPORTER_H
#define IMPORTEXPORTER_H

class PixelBuffer;
class ColorData;

class ImportExporter {
public:

	static PixelBuffer* importImage(const std::string & f_name, PixelBuffer* p_buff);
	static void exportImage(const std::string & f_name, PixelBuffer* p_buff);

    static bool hasSupportedExtension(const std::string & name);
    static bool isValidImageFile(const std::string & name);

private:

	static PixelBuffer* read_jpeg(const std::string & f_name, ColorData backgroundColor);
	static PixelBuffer* read_png(const std::string & f_name, ColorData backgroundColor);
	static void write_png(const std::string & f_name, PixelBuffer* p_buff);
    static void write_jpeg(const std::string & f_name, PixelBuffer* p_buff);

	static bool hasSuffix(const std::string & str, const std::string & suffix);	
};


#endif