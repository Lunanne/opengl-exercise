#ifdef __APPLE__
#include <OpenGL/glu.h>
#endif

#include <vector>

#include <SceneObject.h>

#include "Graphics.h"

Graphics::~Graphics()
{
    glDisable(GL_DEPTH_TEST);
}
void Graphics::InitializeGL()
{
    GLenum errCode;
    const GLubyte *errString;
    if ((errCode = glGetError()) != GL_NO_ERROR) {
        errString = gluErrorString(errCode);
        fprintf(stderr, "OpenGL Error in Graphics: %s\n", errString);
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glClearColor(0, 0, 0, 0);
}

void Graphics::PaintGL(GLFWwindow* p_window, const std::vector<SceneObjectPtr> p_sceneObjects)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (const SceneObjectPtr sceneObject : p_sceneObjects)
    {
        sceneObject->Render();
    }

    glfwSwapBuffers(p_window);
}