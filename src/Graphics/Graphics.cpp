#include "Graphics.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glfw.h>
#include <iostream>

Graphics::~Graphics()
{
    DestroyShaders();
    delete triangle;
}
void Graphics::initializeGL()
{
vertexShader ="#version 330 core\n"\
              "layout(location = 0) in vec3 vertexPosition_modelspace;\n"\
              "uniform mat4 MVP;\n"\
              "void main(){\n"\
              "gl_Position =  MVP * vec4(vertexPosition_modelspace,1);\n"\
              "};\n";
//    vertexShader ="#version 400\n"\
//                  "layout(location=0) in vec4 in_Position;\n"\
//                  "layout(location=1) in vec4 in_Color;\n"\
//                  "out vec4 ex_Color;\n"\
//                  "void main(void)\n"\
//                  "{\n"\
//                  "gl_Position = in_position;"\
//                  "ex_Color = in_Color;\n"\
//                  "}\n";
    fragmentShader ="#version 330 core\n"\
                    "out vec3 color;\n"\
                    "void main()\n"\
                    "{\n"\
                    "color = vec3(1,0,0);\n"
                    "};\n";

//"in vec4 ex_Color;\n"\"   out_Color = ex_Color;\n"
    std::cout<<"initialized GL \n";
    CreateShaders();
    triangle = new GraphicsObject(programID);
}

void Graphics::paintGL()
{
//     glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//
//
//      glLoadIdentity();
//
//      /* A step backward, then spin the cube */
//      glTranslatef(0, 0, -10);
//
//
//      /* We have a color array and a vertex array */
//      glEnableClientState(GL_VERTEX_ARRAY);
//      glEnableClientState(GL_COLOR_ARRAY);
//      glVertexPointer(3, GL_FLOAT, 0, vertices);
//      glColorPointer(3, GL_FLOAT, 0, colors);
//
//      /* Send data : 24 vertices */
//      glDrawArrays(GL_QUADS, 0, 24);
//
//      /* Cleanup states */
//      glDisableClientState(GL_COLOR_ARRAY);
//      glDisableClientState(GL_VERTEX_ARRAY);
//
//      glFlush();
    glClear( GL_COLOR_BUFFER_BIT );


    triangle->Render();

    // Swap buffers
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
