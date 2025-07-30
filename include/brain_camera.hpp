#pragma once

// thirdparty
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Brain {

class BrainCamera {
public:
    BrainCamera(const glm::mat4 projectionMatrix, const glm::mat4 viewTranslation);
    ~BrainCamera();

    glm::mat4 getProjection() const { return projection; }
    void setProjection(const glm::mat4 projectionMatrix) { projection = projectionMatrix; }

    glm::mat4 getViewTranslation() const { return view; }
    void setView(const glm::mat4 viewTranslation) { view = viewTranslation; }

private:
    glm::mat4 projection{};
    glm::mat4 view{};
};
}
