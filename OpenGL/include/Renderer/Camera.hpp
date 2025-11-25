#pragma once

// thirdparty
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace BrainOpenGL {
enum class CameraMovement { UP, DOWN, FORWARD, BACKWARD, LEFT, RIGHT };

constexpr float YAW         = -90.0f;
constexpr float PITCH       = 0.f;
constexpr float SPEED       = 2.5f;
constexpr float SENSITIVITY = 0.1f;
constexpr float ZOOM        = 45.0f;

class Camera {
public:
  // camera attributes
  glm::vec3 m_position;
  glm::vec3 m_front;
  glm::vec3 m_up;
  glm::vec3 m_right;
  glm::vec3 m_worldUp;
  // euler angles
  float m_yaw;
  float m_pitch;
  // camera options
  float m_movementSpeed;
  float m_mouseSensitivity;
  float m_zoom;

  // vectors
  Camera(glm::vec3 position = glm::vec3(0.f, 0.f, 0.f),
         glm::vec3 up = glm::vec3(0.f, 1.f, 0.f), float yaw = YAW,
         float pitch = PITCH);
  // scalers
  Camera(float posX, float posY, float posZ, float upX, float upY, float upZ,
         float yaw, float pitch);

  glm::mat4 GetViewMatrix() const {
    return glm::lookAt(m_position, m_position + m_front, m_up);
  }

  void ProcessKeyboardInput(CameraMovement direction, float deltaTime);
  void ProcessMouseMovement(float xOffset, float yOffset,
                            GLboolean constrainPitch = true);
  void ProcessMouseScroll(float yOffset);

private:
  void updateCameraVectors();
};

} // namespace BrainOpenGL
