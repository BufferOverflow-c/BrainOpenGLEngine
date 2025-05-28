#include "brain_window.hpp"

// STD
#include <iostream>

using namespace Brain;

BrainWindow::BrainWindow(int width, int height, std::string window_name) {
    initWindow();
    window = glfwCreateWindow(width, height, "Brain", nullptr, nullptr);
    if(window == nullptr) {
        std::cerr << "Failed to Create Window\n";
        return;
    }
    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

BrainWindow::~BrainWindow() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void BrainWindow::framebuffer_size_callback(GLFWwindow *window, const int width, const int height) {
    glViewport(0, 0, width, height);
}

void BrainWindow::initWindow() {
    if(!glfwInit()) {
        std::cerr << "GLFW Initialization Failed\n";
        return;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}
