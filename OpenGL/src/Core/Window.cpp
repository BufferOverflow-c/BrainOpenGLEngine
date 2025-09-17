#include "Window.hpp"

// STD
#include <iostream>

using namespace BrainOpenGL;

Window::Window(const int width, const int height, std::string window_name) : lastX(width/2.f), lastY(height/2.f) {
    initWindow();
    window = glfwCreateWindow(width, height, "Brain", nullptr, nullptr);
    if(window == nullptr) {
        std::cerr << "Failed to Create Window\n";
        return;
    }
    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "Failed to initialize GLAD\n";
        return;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::framebuffer_size_callback(GLFWwindow *window, const int width, const int height) {
    glViewport(0, 0, width, height);
}

void Window::mouse_callback(GLFWwindow *window, const double xPosInput, const double yPosInput) {
    const float xPos = static_cast<float>(xPosInput);
    const float yPos = static_cast<float>(yPosInput);

    if (firstMouse) {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    const float xOffset = xPos - lastX;
    const float yOffset = lastY - yPos;
    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMovement(xOffset, yOffset);
}

void Window::scroll_callback(GLFWwindow *window, const double xOffset, const double yOffset) {
    camera.ProcessMouseScroll(static_cast<float>(yOffset));
}

void Window::initWindow() {
    if(!glfwInit()) {
        std::cerr << "GLFW Initialization Failed\n";
        return;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}
