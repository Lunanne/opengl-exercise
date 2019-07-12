#include "../Tools/FileReader.h"

#include "Shader.h"

Shader::Shader() :
m_programID(0),
m_vertexShader(NULL),
m_fragmentShader(NULL)
{}

Shader::Shader(const char* p_vsFilePath, const char* p_fsFilePath)
{
    GLint result = GL_FALSE;
    int infoLogLength;
    
    m_vertexShader = FileReader::ReadFile(p_vsFilePath);
    m_fragmentShader = FileReader::ReadFile(p_fsFilePath);
    
    m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_vertexShaderID, 1, const_cast<const GLchar**>(&m_vertexShader), NULL);
    glCompileShader(m_vertexShaderID);
    
    //check the vertex shader
    glGetShaderiv(m_vertexShaderID, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        glGetShaderiv(m_vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> VertexShaderErrorMessage(infoLogLength);
        glGetShaderInfoLog(m_vertexShaderID, infoLogLength, NULL, &VertexShaderErrorMessage[0]);
        fprintf(stdout, "vertex shader error output: %s\n", &VertexShaderErrorMessage[0]);
    }
    
    m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_fragmentShaderID, 1, const_cast<const GLchar**>(&m_fragmentShader), NULL);
    glCompileShader(m_fragmentShaderID);
    
    //check the fragment shader
    glGetShaderiv(m_fragmentShaderID, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        glGetShaderiv(m_fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> FragmentShaderErrorMessage(infoLogLength);
        glGetShaderInfoLog(m_fragmentShaderID, infoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        fprintf(stdout, "fragment shader error output : %s\n", &FragmentShaderErrorMessage[0]);
    }
    
    m_programID = glCreateProgram();
    glAttachShader(m_programID, m_fragmentShaderID);
    glAttachShader(m_programID, m_vertexShaderID);
    glLinkProgram(m_programID);
    
    // Check the program
    glGetProgramiv(m_programID, GL_LINK_STATUS, &result);
    if (result == GL_FALSE)
    {
        glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> ProgramErrorMessage(std::max(infoLogLength, int(1)));
        glGetProgramInfoLog(m_programID, infoLogLength, NULL, &ProgramErrorMessage[0]);
        fprintf(stdout, "program error output: %s\n", &ProgramErrorMessage[0]);
    }
}


Shader::~Shader()
{
    glUseProgram(0);
    glDetachShader(m_programID, m_vertexShaderID);
    glDetachShader(m_programID, m_fragmentShaderID);
    
    glDeleteShader(m_fragmentShaderID);
    glDeleteShader(m_vertexShaderID);
    
    glDeleteProgram(m_programID);
    if(m_vertexShader)
        delete m_vertexShader;
    if(m_fragmentShader)
        delete m_fragmentShader;
}

void Shader::Use(MaterialPtr p_material)
{
    glUseProgram(m_programID);
}