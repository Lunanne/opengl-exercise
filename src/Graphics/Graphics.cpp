#ifdef __APPLE__
#include <OpenGL/glu.h>
#endif

#include <vector>

#include "RenderComponent.h"

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
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_BLEND);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
}

void Graphics::PaintGL(GLFWwindow* p_window, const std::vector<RenderComponentPtr> p_renderComponents)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (const RenderComponentPtr renderComponentPtr : p_renderComponents)
    {
        renderComponentPtr->Render();
    }

    glfwSwapBuffers(p_window);
}