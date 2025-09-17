#pragma once

#include "../Renderer/Camera.hpp"

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
    void mouse_callback(GLFWwindow *window, double xPosInput, double yPosInput);
    void scroll_callback(GLFWwindow *window, double xOffset, double yOffset);
    void initWindow();

    // Window parameters
    int width;
    int height;
    std::string windowName;

    // Window
    GLFWwindow *window;

    // Camera
    Camera camera{glm::vec3(0.0f, 0.0f, 3.0f)};
#pragma region camera variables
    float lastX;
    float lastY;
    bool firstMouse = true;
#pragma endregion
};
} // namespace Brain
