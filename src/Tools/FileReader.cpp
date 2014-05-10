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


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "stb_image.h"
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
    int width, height, channels;
    FILE* file = fopen(p_fileName, "rb");
    if (file)
    {
        unsigned char* data = stbi_load_from_file(file, &width, &height, &channels, 0);
        image.width = width;
        image.height = height;
        image.bitDepth = 8;
        image.format = GL_RGBA;
        image.data = new unsigned char[width * height * channels];
        memcpy(image.data, data, sizeof(unsigned char)* width * height * channels);
        stbi_image_free(data);
    }
    return image;
}

const aiScene* FileReader::ReadScene(const std::string& p_filePath, Assimp::Importer& p_importer)
{
    const aiScene* scene = p_importer.ReadFile(p_filePath, aiProcess_Triangulate |
        aiProcess_CalcTangentSpace |
        aiProcess_GenSmoothNormals |
        aiProcess_ValidateDataStructure |
        aiProcess_RemoveRedundantMaterials |
        aiProcess_FixInfacingNormals |
        aiProcess_FindInvalidData |
        aiProcess_OptimizeMeshes |
        aiProcess_PreTransformVertices |
        aiProcess_GenUVCoords |
        aiProcess_TransformUVCoords);
    
    if (scene == NULL)
    {
        std::string error =  p_importer.GetErrorString();
        std::printf("Assimp error : %s \n", error);
        assert(scene != NULL);
    }

    return scene;

}