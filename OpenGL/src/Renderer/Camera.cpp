#include "Camera.hpp"

using namespace BrainOpenGL;

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : m_front(glm::vec3(0.f, 0.f, -1.f)), m_movementSpeed(SPEED),
      m_mouseSensitivity(SENSITIVITY), m_zoom(ZOOM) {
  m_position = position;
  m_worldUp  = up;
  m_yaw      = yaw;
  m_pitch    = pitch;
  updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY,
               float upZ, float yaw, float pitch)
    : m_front(glm::vec3(0.f, 0.f, -1.f)), m_movementSpeed(SPEED),
      m_mouseSensitivity(SENSITIVITY), m_zoom(ZOOM) {
  m_position = glm::vec3(posX, posY, posZ);
  m_worldUp  = glm::vec3(upX, upY, upZ);
  m_yaw      = yaw;
  m_pitch    = pitch;
  updateCameraVectors();
}

void Camera::ProcessKeyboardInput(const CameraMovement direction,
                                  const float           deltaTime) {
  const float velocity = m_movementSpeed * deltaTime;
  if (direction == CameraMovement::UP)
    m_position += m_up * velocity;
  if (direction == CameraMovement::DOWN)
    m_position -= m_up * velocity;
  if (direction == CameraMovement::FORWARD)
    m_position += m_front * velocity;
  if (direction == CameraMovement::BACKWARD)
    m_position -= m_front * velocity;
  if (direction == CameraMovement::LEFT)
    m_position -= m_right * velocity;
  if (direction == CameraMovement::RIGHT)
    m_position += m_right * velocity;
}

void Camera::ProcessMouseMovement(float xOffset, float yOffset,
                                  const GLboolean constrainPitch) {
  xOffset *= m_mouseSensitivity;
  yOffset *= m_mouseSensitivity;

  m_yaw += xOffset;
  m_pitch += yOffset;

  if (constrainPitch) {
    if (m_pitch > 89)
      m_pitch = 89;
    if (m_pitch < -89)
      m_pitch = -89;
  }

  updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yOffset) {
  m_zoom -= static_cast<float>(yOffset);
  if (m_zoom < 1.0f)
    m_zoom = 1.0f;
  if (m_zoom > 45.0f)
    m_zoom = 45.0f;
}

void Camera::updateCameraVectors() {
  glm::vec3 front;
  front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
  front.y = sin(glm::radians(m_pitch));
  front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
  m_front   = glm::normalize(front);
  m_right   = glm::normalize(glm::cross(m_front, m_worldUp));
  m_up      = glm::normalize(glm::cross(m_right, m_front));
}
