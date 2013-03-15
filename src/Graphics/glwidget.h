#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <GL/glew.h>
#include <QtOpenGL/QGLWidget>
#include <GL/GL.h>
class GLWidget : public QGLWidget
{
    Q_OBJECT
    
public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    GLuint
        VertexShaderId,
        FragmentShaderId,
        ProgramId,
        VaoId,
        VboId,
        ColorBufferId;
    const GLchar* VertexShader;
    const GLchar* FragmentShader;


void CreateVBO();
void DestroyVBO();
void CreateShaders();
void DestroyShaders();

};

#endif // GLWIDGET_H
