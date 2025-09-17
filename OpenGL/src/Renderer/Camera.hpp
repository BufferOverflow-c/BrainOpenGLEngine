#pragma once

// thirdparty
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GLFW/glfw3.h"

namespace BrainOpenGL {

enum Camera_Movements {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
};

// Default camera values
constexpr float YAW = -90.f;
constexpr float PITCH = 0.f;
constexpr float SPEED = 2.5f;
constexpr float SENSITIVITY = 0.1f;
constexpr float ZOOM = 45.f;

class BrainCamera {
public:
    // vectors
    BrainCamera(GLFWwindow *window = nullptr, glm::vec3 position = glm::vec3(0.f, 0.f, 0.f), glm::vec3 up = glm::vec3(0.f, 1.f, 0.f), float yaw = YAW, float pitch = PITCH);
    // scalers
    BrainCamera(GLFWwindow *window, float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
    ~BrainCamera();

    glm::mat4 getViewMatrix();

    void processKeyboardInput(Camera_Movements direction, float deltaTime);
    void processMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true);
    void processMouseScroll(float yOffset);

    // Camera attributes
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    // euler angles
    float yaw;
    float pitch;
    // camera options
    float movementSpeed;
    float mouseSensitivity;
    float zoom;
private:
    void updateCameraVectors();
};
}
