#include "keyboardcontroller.hpp"

using namespace Brain;

void KeyboardController::processInput(GLFWwindow *window, float deltaTime) {
    if(glfwGetKey(window, keys.escape) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

