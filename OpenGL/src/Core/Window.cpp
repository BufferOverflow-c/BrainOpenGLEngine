#include "Window.hpp"

// STD
#include <iostream>

using namespace BrainOpenGL;

Window::Window(const int width, const int height, std::string window_name) {
  initWindow();
  p_window = glfwCreateWindow(width, height, "Brain", nullptr, nullptr);
  if (p_window == nullptr) {
    std::cerr << "Failed to Create Window\n";
    return;
  }
  glfwMakeContextCurrent(p_window);
  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    std::cerr << "Failed to initialize GLAD\n";
    return;
  }
  glfwSetFramebufferSizeCallback(p_window, framebuffer_size_callback);
}

Window::~Window() {
  glfwDestroyWindow(p_window);
  glfwTerminate();
}

void Window::framebuffer_size_callback(GLFWwindow *window, const int width,
                                       const int height) {
  glViewport(0, 0, width, height);
}

void Window::initWindow() {
  if (!glfwInit()) {
    std::cerr << "GLFW Initialization Failed\n";
    return;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}
