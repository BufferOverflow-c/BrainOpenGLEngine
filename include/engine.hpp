#pragma once

#include "brain_window.hpp"

// thirdparty
#include <glm/glm.hpp>

namespace Brain {
class Engine {
public:
    static constexpr int WIDTH{800};
    static constexpr int HEIGHT{600};

    Engine();
    ~Engine();

    //~ Delete copy constructors
    Engine(const Engine &) = delete;
    Engine &operator=(const Engine &) = delete;

    void run();

private:
    void loadGameObjects();
    void fibonacci(unsigned int transformLoc, glm::vec3 translate, glm::mat4 transMatrix, int depth);
    BrainWindow window{WIDTH, HEIGHT, "Brain Engine"};
    //BrnRenderer brnRenderer{brnWindow, brnDevice};
};
}


