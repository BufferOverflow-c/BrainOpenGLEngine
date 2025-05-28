#include "keyboardcontroller.hpp"

using namespace Brain;

void KeyboardController::process_input(GLFWwindow *window) {
    if(glfwGetKey(window, keys.escape) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

