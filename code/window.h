#ifndef WINDOW_H_
#define WINDOW_H_

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader.h"

class Window
{
public:
    Window(int width, int height, const char *title);
    ~Window();
    void ProcessInput(Shader &shader);
    GLFWwindow *GetWindowHandle() { return window; }

private:
    GLFWwindow *window;
    int width, height;
    bool running = true;
};

static void glfwErrorCallback(int error, const char *description)
{
    std::cerr << "Glfw Error " << error << ": " << description << std::endl;
}

static void glfwFrameBufferCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

#endif //WINDOW_H_