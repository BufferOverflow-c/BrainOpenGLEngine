#include "Input.hpp"

using namespace BrainOpenGL;

void KeyboardController::ProcessInput(GLFWwindow *window, Camera &camera,
                                      const float deltaTime) {
  if (glfwGetKey(window, m_keys.escape) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  if (glfwGetKey(window, m_keys.moveUp) == GLFW_PRESS)
    camera.ProcessKeyboardInput(UP, deltaTime);
  if (glfwGetKey(window, m_keys.moveDown) == GLFW_PRESS)
    camera.ProcessKeyboardInput(DOWN, deltaTime);
  if (glfwGetKey(window, m_keys.moveForward) == GLFW_PRESS)
    camera.ProcessKeyboardInput(FORWARD, deltaTime);
  if (glfwGetKey(window, m_keys.moveBackward) == GLFW_PRESS)
    camera.ProcessKeyboardInput(BACKWARD, deltaTime);
  if (glfwGetKey(window, m_keys.moveLeft) == GLFW_PRESS)
    camera.ProcessKeyboardInput(LEFT, deltaTime);
  if (glfwGetKey(window, m_keys.moveRight) == GLFW_PRESS)
    camera.ProcessKeyboardInput(RIGHT, deltaTime);
}
