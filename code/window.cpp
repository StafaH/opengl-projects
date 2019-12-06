#include "window.h"
#include "shader.h"

Window::Window(int width, int height, const char *title)
{
    window_width = width;
    window_height = height;

    glfwSetErrorCallback(glfwErrorCallback);
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        glfwTerminate();
    }

    // Set opengl context versions
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);          // Mac OSX
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE); // Requires 4.3+

    // Create window with graphics context
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);

    // Enable vsync
    glfwSwapInterval(1);

    glfwSetFramebufferSizeCallback(window, glfwFrameBufferCallback);
}

Window::~Window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::ProcessInput(float delta_time, Shader &shader, Camera &camera)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        shader.Reload("code/basic.vert", "code/basic.frag");
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.UpdatePosition(camera.forward, delta_time);
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.UpdatePosition(-camera.forward, delta_time);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.UpdatePosition(-camera.right, delta_time);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.UpdatePosition(camera.right, delta_time);
    }

    double x_pos, y_pos;
    glfwGetCursorPos(window, &x_pos, &y_pos);

    if (first_mouse_move)
    {
        mouse_lastx = x_pos;
        mouse_lasty = y_pos;
        first_mouse_move = false;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        float x_offset = x_pos - mouse_lastx;
        float y_offset = mouse_lasty - y_pos;
        camera.UpdateView(x_offset, y_offset);
    }

    mouse_lastx = x_pos;
    mouse_lasty = y_pos;
}