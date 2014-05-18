#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <map>

#include "GraphicsTypes.h"

class Shader;
class ShaderManager
{
private:
    static std::map<ShaderType, Shader*> shaders;
    
public:
    static void UseShader(ShaderType p_shaderType);
    static const GLuint GetProgramID(ShaderType p_shaderType);
    static void Init();
    static void Clear();
};
#endif
