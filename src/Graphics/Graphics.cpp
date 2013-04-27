#include "Graphics.h"

#include <GL/gl.h>
#include <GL/glfw.h>
#include <iostream>


Graphics::~Graphics()
{
	glDisable(GL_DEPTH_TEST);
    DestroyShaders();
    delete triangle;
}
void Graphics::initializeGL()
{
    vertexShader ="#version 330 core\n"\
                  "layout(location = 0) in vec3 in_position;\n"\
                  "uniform mat4 MVP;\n"\
                  "void main(){\n"\
                  "gl_Position =  MVP * vec4(in_position,1);\n"\
                  "};\n";
    fragmentShader ="#version 330 core\n"\
                    "out vec3 color;\n"\
                    "void main()\n"\
                    "{\n"\
                    "color = vec3(0.7f,0.7f,0.7f);\n"\
                    "};\n";

    std::cout<<"initialized GL \n";
    CreateShaders();
    triangle = new GraphicsObject(programID);
	

  glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void Graphics::paintGL()
{

    glClear( GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);

    triangle->Render();

    glfwSwapBuffers();
}


void Graphics::CreateShaders()
{
    vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderID,1,&vertexShader,NULL);
    glCompileShader(vertexShaderID);

    fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderID,1,&fragmentShader,NULL);
    glCompileShader(fragmentShaderID);

    programID=glCreateProgram();
    glAttachShader(programID,fragmentShaderID);
    glAttachShader(programID,vertexShaderID);
    glLinkProgram(programID);
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
