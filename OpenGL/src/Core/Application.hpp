#pragma once

#include "Window.hpp"
#include "../Renderer/Camera.hpp"

// thirdparty
#include <glm/glm.hpp>

namespace BrainOpenGL {
class Engine {
public:
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

    Engine();
    ~Engine();

    //~ Delete copy constructors
    Engine(const Engine &) = delete;
    Engine &operator=(const Engine &) = delete;

    void run();

    // callbacks
    static void mouse_callback(GLFWwindow *window, double xPosInput, double yPosInput);
    static void scroll_callback(GLFWwindow *window, double xOffset, double yOffset);

#pragma region variables
    static constexpr int WIDTH{800};
    static constexpr int HEIGHT{600};
    static float lastX;
    static float lastY;
    static bool firstMouse;
    float currentFrame{};
    float deltaTime{};
    float lastFrame{};
#pragma endregion variables
private:
    KeyMappings keys{};
    void loadGameObjects();
    void processInput(const float deltaTime);
    //void fibonacci(unsigned int transformLoc, glm::vec3 translate, glm::mat4 transMatrix, int depth);
    BrainWindow window{WIDTH, HEIGHT, "Brain Engine"};
    BrainCamera camera {window.getGLFWwindow(), glm::vec3(0.f, 0.f, 3.f)};
};
}


