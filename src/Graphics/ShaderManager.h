#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <map>

#include "GraphicsTypes.h"
#include "Camera.h"
#include "Light.h"

class Shader;
class ShaderManager
{
private:
    static std::map<ShaderType, Shader*> shaders;
    
public:
    static void UseShader(ShaderType p_shaderType, MaterialPtr p_material);
    static const GLuint GetProgramID(ShaderType p_shaderType);
    static void Init(Camera p_camera, Light light);
    static void Clear();
};
#endif
