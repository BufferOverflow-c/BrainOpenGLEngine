#pragma once

#include "Window.hpp"
#include "../Renderer/Camera.hpp"

// thirdparty
#include <glm/glm.hpp>

namespace BrainOpenGL {
class Application {
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

    Application();
    ~Application() = default;

    //~ Delete copy constructors
    Application(const Application &) = delete;
    Application &operator=(const Application &) = delete;

    void run();

#pragma region variables
    static constexpr int WIDTH{800};
    static constexpr int HEIGHT{600};
    float currentFrame{};
    float deltaTime{};
    float lastFrame{};
#pragma endregion variables
private:


    KeyMappings keys{};
    void loadGameObjects();
    void processInput(const float deltaTime);
    //void fibonacci(unsigned int transformLoc, glm::vec3 translate, glm::mat4 transMatrix, int depth);
    Window window{WIDTH, HEIGHT, "Brain Engine"};
};
}


