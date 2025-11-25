#pragma once

#include "../Renderer/Camera.hpp"
#include "Input.hpp"
#include "Window.hpp"

// thirdparty
#include <glm/glm.hpp>

namespace BrainOpenGL {

#pragma region   camera/window variables
extern Camera    camera;
extern const int WIDTH;
extern const int HEIGHT;
extern double    lastX;
extern double    lastY;
extern bool      firstMouse;
#pragma endregion
#pragma region camera callbacks
void mouse_callback(GLFWwindow *window, double xPosInput, double yPosInput);
void scroll_callback(GLFWwindow *window, double xOffset, double yOffset);
#pragma endregion

class Application {
public:
  Application();
  ~Application() = default;

  //~ Delete copy constructors
  Application(const Application &)            = delete;
  Application &operator=(const Application &) = delete;

  void run();

#pragma region timing variables
  float currentFrame{};
  float deltaTime{};
  float lastFrame{};
#pragma endregion variables
private:
  KeyboardController m_controller{};
  void               loadGameObjects();
  Window             m_window{WIDTH, HEIGHT, "Brain Engine"};
};
} // namespace BrainOpenGL
