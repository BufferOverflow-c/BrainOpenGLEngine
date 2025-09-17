#include "Camera.hpp"
#include "../Core/Window.hpp"

using namespace BrainOpenGL;

BrainCamera::BrainCamera(GLFWwindow *window, glm::vec3 position, glm::vec3 up, float yaw, float pitch) : front(glm::vec3(0.f, 0.f, -1.f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM) {
    worldUp = up;
    this->position = position;
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVectors();
}

BrainCamera::BrainCamera(GLFWwindow *window, float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : front(glm::vec3(0.f, 0.f, -1.f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM) {
    position = glm::vec3(posX, posY, posZ);
    worldUp = glm::vec3(upX, upY, upZ);
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVectors();
}

BrainCamera::~BrainCamera() = default;

glm::mat4 BrainCamera::getViewMatrix() {
    return glm::lookAt(position, position + front, up);
}

void BrainCamera::processKeyboardInput(const Camera_Movements direction, const float deltaTime) {
    const float velocity = movementSpeed * deltaTime;
    if (direction == FORWARD) position += front * velocity;
    if (direction == BACKWARD) position -= front * velocity;
    if (direction == LEFT) position -= right * velocity;
    if (direction == RIGHT) position += right * velocity;
}

void BrainCamera::processMouseMovement(float xOffset, float yOffset, const GLboolean constrainPitch) {
    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;
    yaw += xOffset;
    pitch += yOffset;
    if (constrainPitch) {
        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;
    }
    updateCameraVectors();
}

void BrainCamera::processMouseScroll(const float yOffset) {
    zoom -= (float)yOffset;
    if (zoom < 1.0f) zoom = 1.0f;
    if (zoom > 45.0f) zoom = 45.0f;
}

void BrainCamera::updateCameraVectors() {
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}