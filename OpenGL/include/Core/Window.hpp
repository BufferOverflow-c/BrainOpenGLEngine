#pragma once

// thirdparty
#include <GLFW/glfw3.h>
#include <glad/glad.h>

// STD
#include <string>

namespace BrainOpenGL {

class Window {
public:
  Window(int width, int height, std::string window_name);
  ~Window();

  //~ Deleting the copy constructors to prevent mem leak
  Window(const Window &)            = delete;
  Window &operator=(const Window &) = delete;

  bool shouldClose() const { return glfwWindowShouldClose(p_window); }

  [[nodiscard]] GLFWwindow *getGLFWwindow() const { return p_window; }

private:
  static void framebuffer_size_callback(GLFWwindow *window, int width,
                                        int height);

  void initWindow();

  // Window parameters
  int         m_width;
  int         m_height;
  std::string m_windowName;

  // Window
  GLFWwindow *p_window;
};
} // namespace BrainOpenGL
