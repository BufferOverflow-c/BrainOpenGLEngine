#pragma once

// thirdparty
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// STD
#include <string>

namespace BrainOpenGL {

class Window {
public:
    Window(int width, int height, std::string window_name);
    ~Window();

    //~ Deleting the copy constructors to prevent mem leak
    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;

    bool shouldClose() const { return glfwWindowShouldClose(window); }

    [[nodiscard]] GLFWwindow *getGLFWwindow() const { return window; }


private:
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

    void initWindow();

    // Window parameters
    int width;
    int height;
    std::string windowName;

    // Window
    GLFWwindow *window;
};
} // namespace Brain
