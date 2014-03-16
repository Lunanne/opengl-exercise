#include <vector>

#include <SceneObject.h>

#include "Graphics.h"

Graphics::~Graphics()
{
    glDisable(GL_DEPTH_TEST);
}
void Graphics::InitializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
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