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

static void error_callback(int error, const char *description) {
    fprintf(stderr, "Error description %s \n", description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(int argc, char **argv) {
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

    GLFWwindow *window = glfwCreateWindow(1024, 768, "Opengl exercise", NULL, NULL);
#include <vector>
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

    fprintf(stdout, "OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));

    World world;
    world.InitializeBullet();

    Graphics graphics;
    graphics.InitializeGL();

    ShaderManager::Init();
    Scene scene("../Resources/cube.blend");
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