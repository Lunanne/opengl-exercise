#include <GL/glew.h>
#include <GL/gl.h>
#include <QtGui/QMouseEvent>
#include <QtOpenGL/QGLWidget>
#include <iostream>
#include "glwidget.h"
#include "../Tools/objectfileparser.h"

/* One face per line */
GLfloat		vertices[] =
  {
    -1, -1, -1,   -1, -1,  1,   -1,  1,  1,   -1,  1, -1,
     1, -1, -1,    1, -1,  1,    1,  1,  1,    1,  1, -1,
    -1, -1, -1,   -1, -1,  1,    1, -1,  1,    1, -1, -1,
    -1,  1, -1,   -1,  1,  1,    1,  1,  1,    1,  1, -1,
    -1, -1, -1,   -1,  1, -1,    1,  1, -1,    1, -1, -1,
    -1, -1,  1,   -1,  1,  1,    1,  1,  1,    1, -1,  1
  };

GLfloat		colors[] =
  {
    0, 0, 0,   0, 0, 1,   0, 1, 1,   0, 1, 0,
    1, 0, 0,   1, 0, 1,   1, 1, 1,   1, 1, 0,
    0, 0, 0,   0, 0, 1,   1, 0, 1,   1, 0, 0,
    0, 1, 0,   0, 1, 1,   1, 1, 1,   1, 1, 0,
    0, 0, 0,   0, 1, 0,   1, 1, 0,   1, 0, 0,
    0, 0, 1,   0, 1, 1,   1, 1, 1,   1, 0, 1
  };

GLWidget::GLWidget(QWidget *parent):QGLWidget(parent) {

    setMouseTracking(true);

}
GLWidget::~GLWidget()
{
   // DestroyShaders();
    //DestroyVBO();
}
void GLWidget::initializeGL() {
    VertexShader ="#version 400\n"\
                  "layout(location=0) in vec4 in_Position;\n"\
                  "layout(location=1) in vec4 in_Color;\n"\
                  "out vec4 ex_Color;\n"\
                  "void main(void)\n"\
                  "{\n"\
                  "   gl_Position = in_Position;\n"\
                  "   ex_Color = in_Color;\n"\
                  "}\n";
    FragmentShader ="#version 400\n"\
                    "in vec4 ex_Color;\n"\
                    "out vec4 out_Color;\n"\
                    "void main(void)\n"\
                    "{\n"\
                    "   out_Color = ex_Color;\n"\
                    "}\n";
    if(glewInit()!=GLEW_OK)
        std::cout<<"glew init failed"<<std::endl;
    glClearColor(0, 0, 0, 0);
      glEnable(GL_DEPTH_TEST);
    
    ObjectFileParser parser;
    cube = parser.ParseObjFile();
}

void GLWidget::resizeGL(int w, int h) {
    glMatrixMode(GL_PROJECTION);

      glLoadIdentity();
      gluPerspective(20, w / (float) h, 5, 15);
      glViewport(0, 0, w, h);

}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    static float alpha = 0;

      /* Clear the buffer, clear the matrix */
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glLoadIdentity();

      /* A step backward, then spin the cube */
      glTranslatef(0, 0, -10);
      glRotatef(30, 1, 0, 0);
      glRotatef(alpha, 0, 1, 0);

      /* We have a color array and a vertex array */
      glEnableClientState(GL_VERTEX_ARRAY);
      glEnableClientState(GL_COLOR_ARRAY);
      glVertexPointer(3, GL_FLOAT, 0, vertices);
      glColorPointer(3, GL_FLOAT, 0, colors);

      /* Send data : 24 vertices */
      glDrawArrays(GL_QUADS, 0, 24);

      /* Cleanup states */
      glDisableClientState(GL_COLOR_ARRAY);
      glDisableClientState(GL_VERTEX_ARRAY);


      /* Rotate a bit more */
      alpha = alpha + 0.1;

      /* End */
      glFlush();
}

void GLWidget::CreateVBO()
{
    GLfloat Vertices[] = {
        1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,1.0f,-1.0f,
       1.0f,1.0f,1.0f,
        -1.0f,1.0f,1.0f,
        -1.0f,1.0f,-1.0f
    };

    GLubyte indices[]={
        1,2,3,
        1,3,4,
        5,8,7,
        5,7,6,
        1,5,6,
        1,6,2,
        2,6,7,
        2,7,3,
        3,7,8,
        3,8,4,
        5,1,4,
        5,4,8
    };

    GLfloat Colors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f
    };

    glGenVertexArrays(1,&VaoId);
    glBindVertexArray(VaoId);

    glGenBuffers(1,&VboId);
    glBindBuffer(GL_ARRAY_BUFFER,VboId);
    glBufferData(GL_ARRAY_BUFFER,sizeof(Vertices),Vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
    glEnableVertexAttribArray(0);
    glGenBuffers(1, &ColorBufferId);

    glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);


}
void GLWidget::DestroyVBO() {
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
