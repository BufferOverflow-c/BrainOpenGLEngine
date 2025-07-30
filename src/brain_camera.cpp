#include "brain_camera.hpp"
#include "brain_window.hpp"

using namespace Brain;

BrainCamera::BrainCamera(const glm::mat4 projectionMatrix, const glm::mat4 viewTranslation) {
    projection = projectionMatrix;
    view = viewTranslation;
}

BrainCamera::~BrainCamera() {

}

// glm::ortho(0.f, width, height, 0.f, near, far);
// glm::perspective(glm::radians(45.f), static_cast<float>(width)/static_cast<float>(height), near, far);
