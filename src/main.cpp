#define QT_NO_OPENGL_ES_2
#define GLEW_STATIC
#include <GL/glew.h>
#include <QApplication>
#include <QGLFormat>
#include "Graphics/glwidget.h"
int main(int argc, char *argv[])
{
   QApplication app(argc, argv);
    QGLFormat fmt;
	fmt.setVersion(4,0);
	QGLFormat::setDefaultFormat(fmt);
    GLWidget window;
    window.resize(800,600);
    window.show();
    
    return app.exec();
}
