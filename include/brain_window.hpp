#pragma once

// thirdparty
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// STD
#include <string>

namespace Brain {
class BrainWindow {
public:
    BrainWindow(int width, int height, std::string window_name);
    ~BrainWindow();

    //~ Deleting the copy constructors to prevent mem leak
    BrainWindow(const BrainWindow &) = delete;
    BrainWindow &operator=(const BrainWindow &) = delete;

    bool shouldClose() { return glfwWindowShouldClose(window); }

    GLFWwindow *getGLFWwindow() const { return window; }

private:
    static void framebuffer_size_callback(GLFWwindow *window, const int width, const int height);
    void initWindow();

    //~ Window parameters
    int width;
    int height;
    std::string windowName;

    //~ Window
    GLFWwindow *window;
};
} // namespace Brain
