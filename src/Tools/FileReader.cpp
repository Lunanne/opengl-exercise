#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <iostream>
#include <fstream>

#include <png.h>

#include "../Graphics/GraphicsTypes.h"
#include "FileReader.h"

char* FileReader::ReadFile(const char* p_fileName)
{
    char* content;
    std::ifstream file(p_fileName, std::ios::in | std::ios::binary);
    if (file)
    {
        file.seekg(0, std::ios::end);
        const int length = static_cast<int>(file.tellg());
        content = new char[length + 1];
        file.seekg(0, std::ios::beg);
        file.read(content, length);
        content[length] = '\0';

        return content;
    }
    else
    {
        std::printf("Can't open file at %s \n", p_fileName);
    }
    return "";
}

Image FileReader::ReadPNG(const char* p_fileName)
{
    Image image;

    png_structp imagePtr;
    png_infop infoPtr;

    int bitDepth, colorType;
    png_uint_32 height, width;
    FILE* file = fopen(p_fileName, "rb");
    imagePtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    infoPtr = png_create_info_struct(imagePtr);

    if (setjmp(png_jmpbuf(imagePtr)))
        std::printf("Error during png stuff");

    png_init_io(imagePtr, file);
    png_read_info(imagePtr, infoPtr);
    png_get_IHDR(imagePtr, infoPtr, &width, &height, &bitDepth, &colorType, NULL, NULL, NULL);

    if (bitDepth != 8)
        std::printf("Error, unsupported bit depth");

    image.width = width;
    image.height = height;
    image.bitDepth = bitDepth;
    switch (colorType) {
    case PNG_COLOR_TYPE_RGB:
        image.format = GL_RGB;
        break;
    case PNG_COLOR_TYPE_RGB_ALPHA:
        image.format = GL_RGBA;
        break;
    default:
        std::printf("Error unsupported format %d \n", colorType);
        break;
    }

    png_read_update_info(imagePtr, infoPtr);


    int rowbytes = png_get_rowbytes(imagePtr, infoPtr);
    rowbytes += 3 - ((rowbytes - 1) % 4);
    size_t size = rowbytes * image.height * sizeof(png_byte*) +15;
    image.data = static_cast<unsigned char*>(malloc(size));
    png_byte** rowPtr = static_cast<png_byte**>(malloc(image.height * sizeof(png_byte *)));
    //point rowPtr to correct offset in image data
    for (int i = 0; i < image.height; ++i)
    {
        rowPtr[image.height - 1 - i] = image.data + i * rowbytes;
    }
    png_set_interlace_handling(imagePtr);
    png_read_image(imagePtr, rowPtr);
    fclose(file);
    png_destroy_read_struct(&imagePtr, &infoPtr, NULL);
    free(rowPtr);
    return image;
}
