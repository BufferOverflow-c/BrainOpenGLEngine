#pragma once

#include "../Renderer/Camera.hpp"
#include "Window.hpp"

namespace BrainOpenGL {
    class KeyboardController {

public:
<<<<<<< HEAD
      struct KeyMappings {
        int moveLeft = GLFW_KEY_A;
        int moveRight = GLFW_KEY_D;
        int moveForward = GLFW_KEY_W;
        int moveBackward = GLFW_KEY_S;
        int moveUp = GLFW_KEY_E;
        int moveDown = GLFW_KEY_Q;
        int lookLeft = GLFW_KEY_LEFT;
        int lookRight = GLFW_KEY_RIGHT;
        int lookUp = GLFW_KEY_UP;
        int lookDown = GLFW_KEY_DOWN;
        int escape = GLFW_KEY_ESCAPE;
      };
      void processInput(GLFWwindow *window, const float deltaTime);
=======
        struct KeyMappings {
            int moveLeft = GLFW_KEY_A;
            int moveRight = GLFW_KEY_D;
            int moveForward = GLFW_KEY_W;
            int moveBackward = GLFW_KEY_S;
            int moveUp = GLFW_KEY_E;
            int moveDown = GLFW_KEY_Q;
            int lookLeft = GLFW_KEY_LEFT;
            int lookRight = GLFW_KEY_RIGHT;
            int lookUp = GLFW_KEY_UP;
            int lookDown = GLFW_KEY_DOWN;
            int escape = GLFW_KEY_ESCAPE;
        };
>>>>>>> camera

        KeyboardController() = default;
        ~KeyboardController() = default;
        void ProcessInput(GLFWwindow *window, Camera &camera, const float deltaTime);

        KeyMappings keys{};
        float moveSpeed{3.f};
        float lookSpeed{1.5f};
    };
}
