#ifdef _WIN32
#include <Windows.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glew.h>

#endif

#include <GLFW/glfw3.h>

#include <iostream>
#include <iterator>

#include "Graphics/Graphics.h"
#include "Graphics/ShaderManager.h"
#include "Scene/Scene.h"
#include "Physics/World.h"

static void error_callback(int error, const char *description)
{
    fprintf(stderr, "Error description %s \n", description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void APIENTRY
debug_callback(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message, const
void *param)
{
    // ignore non-significant error/warning codes
    if (id !=131169 && id !=131185 && id != 131218 && id != 131204) {

        std::cout << "---------------" << std::endl;
        std::cout << "Debug message (" << id << "): " << message << std::endl;

        switch (source) {
            case GL_DEBUG_SOURCE_API:
                std::cout << "Source: API";
                break;
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
                std::cout << "Source: Window System";
                break;
            case GL_DEBUG_SOURCE_SHADER_COMPILER:
                std::cout << "Source: Shader Compiler";
                break;
            case GL_DEBUG_SOURCE_THIRD_PARTY:
                std::cout << "Source: Third Party";
                break;
            case GL_DEBUG_SOURCE_APPLICATION:
                std::cout << "Source: Application";
                break;
            case GL_DEBUG_SOURCE_OTHER:
                std::cout << "Source: Other";
                break;
        }
        std::cout << std::endl;

        switch (type) {
            case GL_DEBUG_TYPE_ERROR:
                std::cout << "Type: Error";
                break;
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
                std::cout << "Type: Deprecated Behaviour";
                break;
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
                std::cout << "Type: Undefined Behaviour";
                break;
            case GL_DEBUG_TYPE_PORTABILITY:
                std::cout << "Type: Portability";
                break;
            case GL_DEBUG_TYPE_PERFORMANCE:
                std::cout << "Type: Performance";
                break;
            case GL_DEBUG_TYPE_MARKER:
                std::cout << "Type: Marker";
                break;
            case GL_DEBUG_TYPE_PUSH_GROUP:
                std::cout << "Type: Push Group";
                break;
            case GL_DEBUG_TYPE_POP_GROUP:
                std::cout << "Type: Pop Group";
                break;
            case GL_DEBUG_TYPE_OTHER:
                std::cout << "Type: Other";
                break;
        }
        std::cout << std::endl;

        switch (severity) {
            case GL_DEBUG_SEVERITY_HIGH:
                std::cout << "Severity: high";
                break;
            case GL_DEBUG_SEVERITY_MEDIUM:
                std::cout << "Severity: medium";
                break;
            case GL_DEBUG_SEVERITY_LOW:
                std::cout << "Severity: low";
                break;
            case GL_DEBUG_SEVERITY_NOTIFICATION:
                std::cout << "Severity: notification";
                break;
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
}

int main(int argc, char **argv)
{
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(1024, 768, "Opengl exercise", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to open GLFW window.");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, true);
    glfwSetKeyCallback(window, key_callback);

#ifndef __APPLE__
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }
#endif

    glDebugMessageCallback(debug_callback, NULL);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);

    fprintf(stdout, "OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));

    World world;
    world.InitializeBullet();

    Graphics graphics;
    graphics.InitializeGL();

    Scene scene("./Resources/world.blend");
    ShaderManager::Init(scene.GetCamera(), scene.GetLight());
    world.AddPhysicComponents(scene.GetSceneObjects());

    while (!glfwWindowShouldClose(window)) {
        world.SimulatePhysics();

        graphics.PaintGL(window, scene.GetSceneObjects());
        glfwPollEvents();
    }

    ShaderManager::Clear();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}