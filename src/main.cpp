#include <glfw/glfw3.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>
#include "Graphics/Graphics.h"

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error description %s \n", description);
}

int	main(int argc, char **argv)
{
    glfwSetErrorCallback(error_callback);
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow( 1024, 768, "Opengl exercise", NULL, NULL );
    if( !window )
    {
        fprintf( stderr, "Failed to open GLFW window." );
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, true);
    Graphics graphics;
    graphics.initializeGL();

    do
    {
        graphics.paintGL( window );
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
            glfwGetWindowAttrib(window, GLFW_VISIBLE) );

    glfwTerminate();

    return 0;
}

