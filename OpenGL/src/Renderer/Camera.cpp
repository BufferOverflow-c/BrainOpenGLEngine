#include "Camera.hpp"

using namespace BrainOpenGL;

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : Front(glm::vec3(0.f, 0.f, -1.f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.f, 0.f, -1.f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

<<<<<<< HEAD
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
    float velocity = MovementSpeed * deltaTime;
=======
void Camera::ProcessKeyboardInput(const Camera_Movement direction, const float deltaTime) {
    const float velocity = MovementSpeed * deltaTime;
>>>>>>> camera
    if (direction == FORWARD) Position += Front * velocity;
    if (direction == BACKWARD) Position -= Front * velocity;
    if (direction == LEFT) Position -= Right * velocity;
    if (direction == RIGHT) Position += Right * velocity;
}

<<<<<<< HEAD
void Camera::ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch) {
=======
void Camera::ProcessMouseMovement(float xOffset, float yOffset, const GLboolean constrainPitch) {
>>>>>>> camera
    xOffset *= MouseSensitivity;
    yOffset *= MouseSensitivity;

    Yaw += xOffset;
    Pitch += yOffset;

    if (constrainPitch) {
        if (Pitch > 89) Pitch = 89;
        if (Pitch < -89) Pitch = -89;
    }

    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yOffset) {
    Zoom -= static_cast<float>(yOffset);
    if (Zoom < 1.0f) Zoom = 1.0f;
    if (Zoom > 45.0f) Zoom = 45.0f;
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}