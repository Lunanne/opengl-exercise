#include <GL/glew.h>
#include <QtGui/QMouseEvent>
#include <QtOpenGL/QGLWidget>
#include "stdio.h"
#include <iostream>
#include <QGLFormat>

#include "glwidget.h"
GLWidget::GLWidget(QWidget *parent):QGLWidget(parent) {
    setMouseTracking(true);

}
GLWidget::~GLWidget()
{
    DestroyShaders();
    DestroyVBO();
}
void GLWidget::initializeGL() {
    glewInit();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glEnable(GL_POLYGON_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    CreateShaders();
    CreateVBO();
    glClearColor(0, 0, 0, 0);
    std::cout<<glGetString(GL_VERSION);
}

void GLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1.0l, 1.0l);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT||GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES,0,3);
}

void GLWidget::CreateVBO()
{
    GLfloat Vertices[] = {
        -0.8f, -0.8f, 0.0f, 1.0f,
        0.0f,  0.8f, 0.0f, 1.0f,
        0.8f, -0.8f, 0.0f, 1.0f
    };

    GLfloat Colors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f
    };

    glGenVertexArrays(1,&VaoId);
    glBindVertexArray(VaoId);

    glGenBuffers(1,&VboId);
    glBindBuffer(GL_ARRAY_BUFFER,VboId);
    glBufferData(GL_ARRAY_BUFFER,sizeof(Vertices),Vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,0,0);
    glEnableVertexAttribArray(0);
    glGenBuffers(1, &ColorBufferId);

    glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);


}
void GLWidget::DestroyVBO(){
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER,0);

    glDeleteBuffers(1,&ColorBufferId);
    glDeleteBuffers(1,&VboId);

    glBindVertexArray(0);
    glDeleteVertexArrays(1,&VaoId);

}
void GLWidget::CreateShaders()
{
    VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShaderId,1,&VertexShader,NULL);
    glCompileShader(VertexShaderId);

    FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShaderId,1,&FragmentShader,NULL);
    glCompileShader(FragmentShaderId);

    ProgramId=glCreateProgram();
    glAttachShader(ProgramId,VertexShaderId);
    glAttachShader(ProgramId,FragmentShaderId);
    glLinkProgram(ProgramId);
    glUseProgram(ProgramId);

}
void GLWidget::DestroyShaders()
{
    glUseProgram(0);
    glDetachShader(ProgramId,VertexShaderId);
    glDetachShader(ProgramId,FragmentShaderId);

    glDeleteShader(FragmentShaderId);
    glDeleteShader(VertexShaderId);

    glDeleteProgram(ProgramId);
}
void GLWidget::mousePressEvent(QMouseEvent *event) {

}
void GLWidget::mouseMoveEvent(QMouseEvent *event) {
}

void GLWidget::keyPressEvent(QKeyEvent* event) {
}
