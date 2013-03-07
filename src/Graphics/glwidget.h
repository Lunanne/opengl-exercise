#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL/QGLWidget>
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
    const GLchar* VertexShader =
    {
        "#version 400\n"\

        "layout(location=0) in vec4 in_Position;\n"\
        "layout(location=1) in vec4 in_Color;\n"\
        "out vec4 ex_Color;\n"\

        "void main(void)\n"\
        "{\n"\
        "   gl_Position = in_Position;\n"\
        "   ex_Color = in_Color;\n"\
        "}\n"
    };
    const GLchar* FragmentShader =
    {
        "#version 400\n"\

        "in vec4 ex_Color;\n"\
        "out vec4 out_Color;\n"\

        "void main(void)\n"\
        "{\n"\
        "   out_Color = ex_Color;\n"\
        "}\n"
    };


void CreateVBO();
void DestroyVBO();
void CreateShaders();
void DestroyShaders();

};

#endif // GLWIDGET_H
