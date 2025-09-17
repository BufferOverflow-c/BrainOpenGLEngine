#pragma once

#include "Input.hpp"
#include "Window.hpp"
#include "../Renderer/Camera.hpp"

// thirdparty
#include <glm/glm.hpp>

namespace BrainOpenGL {

#pragma region camera/window variables
    extern Camera camera;
    extern const int WIDTH;
    extern const int HEIGHT;
    extern double lastX;
    extern double lastY;
    extern bool firstMouse;
#pragma endregion
#pragma region camera callbacks
    void mouse_callback(GLFWwindow* window, double xPosInput, double yPosInput);
    void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
#pragma endregion

class Application {
public:
    Application();
    ~Application() = default;

    //~ Delete copy constructors
    Application(const Application &) = delete;
    Application &operator=(const Application &) = delete;

    void run();

<<<<<<< HEAD
#pragma region variables
    static constexpr int WIDTH{800};
    static constexpr int HEIGHT{600};
=======
#pragma region timing variables
>>>>>>> camera
    float currentFrame{};
    float deltaTime{};
    float lastFrame{};
#pragma endregion variables
private:
<<<<<<< HEAD


    KeyMappings keys{};
    void loadGameObjects();
    void processInput(const float deltaTime);
    //void fibonacci(unsigned int transformLoc, glm::vec3 translate, glm::mat4 transMatrix, int depth);
=======
    KeyboardController controller{};
    void loadGameObjects();
>>>>>>> camera
    Window window{WIDTH, HEIGHT, "Brain Engine"};
};
}


