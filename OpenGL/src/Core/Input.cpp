#include "Input.hpp"

using namespace BrainOpenGL;

<<<<<<< HEAD
void KeyboardController::processInput(GLFWwindow *window, const float deltaTime) {
    if(glfwGetKey(window, keys.escape) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    //if (glfwGetKey(window, keys.moveForward) == GLFW_PRESS) camera.processKeyboardInput(FORWARD, deltaTime);
    //if (glfwGetKey(window, keys.moveBackward) == GLFW_PRESS) camera.processKeyboardInput(BACKWARD, deltaTime);
    //if (glfwGetKey(window, keys.moveLeft) == GLFW_PRESS) camera.processKeyboardInput(LEFT, deltaTime);
    //if (glfwGetKey(window, keys.moveRight) == GLFW_PRESS) camera.processKeyboardInput(RIGHT, deltaTime);
=======
void KeyboardController::ProcessInput(GLFWwindow *window, Camera &camera, const float deltaTime) {
    if(glfwGetKey(window, keys.escape) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
        if (glfwGetKey(window, keys.moveForward) == GLFW_PRESS) camera.ProcessKeyboardInput(FORWARD, deltaTime);
        if (glfwGetKey(window, keys.moveBackward) == GLFW_PRESS) camera.ProcessKeyboardInput(BACKWARD, deltaTime);
        if (glfwGetKey(window, keys.moveLeft) == GLFW_PRESS) camera.ProcessKeyboardInput(LEFT, deltaTime);
        if (glfwGetKey(window, keys.moveRight) == GLFW_PRESS) camera.ProcessKeyboardInput(RIGHT, deltaTime);
>>>>>>> camera
}
