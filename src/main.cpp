#define QT_NO_OPENGL_ES_2
#include <GL/glew.h>
#include <QApplication>
#include "Graphics/glwidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    GLWidget window;
    window.resize(800,600);
    window.show();
    
    return app.exec();
}
