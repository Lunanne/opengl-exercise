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
#include <assert.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

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
        std::printf("Assimp error : %s \n", error.c_str());
        assert(scene != NULL);
    }

    return scene;

}