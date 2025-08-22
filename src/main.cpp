#include "engine.hpp"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main() {
    Brain::Engine engine{};

    try {
        engine.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
