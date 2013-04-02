#include "Graphics.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>

Graphics::~Graphics()
{
    DestroyShaders();
    DestroyVBO();
}
void Graphics::initializeGL() {
//     VertexShader ="#version 330\n"\
//                   "layout(location=0) in vec4 in_Position;\n"\
//                   "layout(location=1) in vec4 in_Color;\n"\
//                   "out vec4 ex_Color;\n"\
//                   "void main(void)\n"\
//                   "{\n"\
//                   "   gl_Position = in_Position;\n"\
//                   "   ex_Color = in_Color;\n"\
//                   "}\n";
//     FragmentShader ="#version 330\n"\
//                     "in vec4 ex_Color;\n"\
//                     "out vec4 out_Color;\n"\
//                     "void main(void)\n"\
//                     "{\n"\
//                     "   out_Color = ex_Color;\n"\
//                     "}\n";
//     glDisable(GL_TEXTURE_2D);
//     glDisable(GL_COLOR_MATERIAL);
//     glEnable(GL_BLEND);
//     glEnable(GL_POLYGON_SMOOTH);
//     glEnable(GL_DEPTH_TEST);
//     glEnable(GL_LESS);
//     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//     CreateShaders();
//     CreateVBO();
//     glClearColor(255, 255, 255, 0);
    
}

void Graphics::resizeGL(int w, int h) {
//     glViewport(0, 0, w, h);
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     glOrtho(0, w, 0, h, -1.0l, 1.0l);
//     glMatrixMode(GL_MODELVIEW);
//     glLoadIdentity();
}

void Graphics::paintGL() {
//     glClear(GL_COLOR_BUFFER_BIT||GL_DEPTH_BUFFER_BIT);
//     glDrawArrays(GL_TRIANGLES,0,12);
}

void Graphics::CreateVBO()
{
//     glGenVertexArrays(1,&VaoId);
//     glBindVertexArray(VaoId);
// 
//     glGenBuffers(1,&VboId);
//     glBindBuffer(GL_ARRAY_BUFFER,VboId);
//     glBufferData(GL_ARRAY_BUFFER,sizeof(cube.GetVertices()),cube.GetVertices().data(),GL_STATIC_DRAW);
//     glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,0,0);
//     glEnableVertexAttribArray(0);
//     glGenBuffers(1, &ColorBufferId);
// 
//     glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
//     glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
//     glEnableVertexAttribArray(1);


}
void Graphics::DestroyVBO() {
//     glDisableVertexAttribArray(1);
//     glDisableVertexAttribArray(0);
// 
//     glBindBuffer(GL_ARRAY_BUFFER,0);
// 
//     glDeleteBuffers(1,&ColorBufferId);
//     glDeleteBuffers(1,&VboId);
// 
//     glBindVertexArray(0);
//     glDeleteVertexArrays(1,&VaoId);

}
void Graphics::CreateShaders()
{
//     VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
//     glShaderSource(VertexShaderId,1,&VertexShader,NULL);
//     glCompileShader(VertexShaderId);
// 
//     FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
//     glShaderSource(FragmentShaderId,1,&FragmentShader,NULL);
//     glCompileShader(FragmentShaderId);
// 
//     ProgramId=glCreateProgram();
//     glAttachShader(ProgramId,VertexShaderId);
//     glAttachShader(ProgramId,FragmentShaderId);
//     glLinkProgram(ProgramId);
//     glUseProgram(ProgramId);

}
void Graphics::DestroyShaders()
{
//     glUseProgram(0);
//     glDetachShader(ProgramId,VertexShaderId);
//     glDetachShader(ProgramId,FragmentShaderId);
// 
//     glDeleteShader(FragmentShaderId);
//     glDeleteShader(VertexShaderId);
// 
//     glDeleteProgram(ProgramId);
}
