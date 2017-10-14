#include "GraphicsTypes.h"
#include "DefaultShader.h"
#include "Shader.h"
#include "ShaderManager.h"

std::map<ShaderType, Shader*> ShaderManager::shaders;

void ShaderManager::Init()
{
    DefaultShader* defaultShader = new DefaultShader("../../Resources/vertexShader.vert","../../Resources/fragmentShader.frag");
    shaders.insert(std::pair<ShaderType,Shader*>(ShaderType_Default,defaultShader));
}

void ShaderManager::UseShader(ShaderType p_shaderType)
{
    shaders[p_shaderType]->Use();
}

const GLuint ShaderManager::GetProgramID(ShaderType p_shaderType)
{
    return shaders[p_shaderType]->GetProgramID();
}

void ShaderManager::Clear()
{
    shaders.clear();
}
                   
