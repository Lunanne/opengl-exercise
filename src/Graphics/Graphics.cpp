
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "Graphics.h"


std::string readFile(const char* fileName)
{
    std::ifstream file( fileName, std::ios::in | std::ios::binary);
    if (file)
    {
        std::stringstream fileData;
        fileData << file.rdbuf();
        file.close();
        return fileData.str();
    }
    else
    {
        std::printf("Can't open file at %s \n", fileName);
        return "";
    }
}


Graphics::~Graphics()
{
	glDisable(GL_DEPTH_TEST);
    DestroyShaders();
    delete triangle;
}
void Graphics::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0, 0, 0, 0);
    
    CreateShaders();
    triangle = new GraphicsObject(programID);
    
    std::cout<<"initialized GL \n";
}

void Graphics::paintGL( GLFWwindow* p_window)
{

    glClear( GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);

    triangle->Render();

    glfwSwapBuffers(p_window);
}


void Graphics::CreateShaders()
{
    GLint result = GL_FALSE;
    int infoLogLength;
    
    const char* vertexShader = readFile("./Resources/vertexShader.vert").c_str();
    const char* fragmentShader = readFile("./Resources/fragmentShader.frag").c_str();
    vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderID,1,static_cast<const GLchar**>(&vertexShader),NULL);
    glCompileShader(vertexShaderID);
    
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    std::vector<char> VertexShaderErrorMessage(infoLogLength);
    glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &VertexShaderErrorMessage[0]);
    fprintf(stdout, "vertex shader error output: %s\n", &VertexShaderErrorMessage[0]);

    fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1,static_cast<const GLchar**>(&fragmentShader), NULL);
    glCompileShader(fragmentShaderID);
    
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    std::vector<char> FragmentShaderErrorMessage(infoLogLength);
    glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &FragmentShaderErrorMessage[0]);
    fprintf(stdout, "fragment shader error output : %s\n", &FragmentShaderErrorMessage[0]);
    
    programID=glCreateProgram();
    glBindAttribLocation(programID, 0, 	"in_position");
    glAttachShader(programID,fragmentShaderID);
    glAttachShader(programID,vertexShaderID);
    glLinkProgram(programID);
    
    // Check the program
    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    std::vector<char> ProgramErrorMessage( std::max(infoLogLength, int(1)) );
    glGetProgramInfoLog(programID, infoLogLength, NULL, &ProgramErrorMessage[0]);
    fprintf(stdout, "program error output: %s\n", &ProgramErrorMessage[0]);
    
    glUseProgram(programID);
}
void Graphics::DestroyShaders()
{
    glUseProgram(0);
    glDetachShader(programID,vertexShaderID);
    glDetachShader(programID,fragmentShaderID);

    glDeleteShader(fragmentShaderID);
    glDeleteShader(vertexShaderID);

    glDeleteProgram(programID);
}
