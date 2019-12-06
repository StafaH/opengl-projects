#ifndef WINDOW_H_
#define WINDOW_H_

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "camera.h"

class Window {
public:
    Window(int width, int height, const char *title);
    ~Window();
    void ProcessInput(float delta_time, Shader &shader, Camera& camera);
    GLFWwindow *GetWindowHandle() { return window; }

    int GetWindowWidth() { return window_width; }
    int GetWindowHeight() { return window_height; }
private:
    GLFWwindow *window;
    int window_width, window_height;
    bool running = true;

    bool first_mouse_move;
    float mouse_lastx;
    float mouse_lasty;

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