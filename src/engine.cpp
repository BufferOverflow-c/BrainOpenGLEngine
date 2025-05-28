#include "engine.hpp"
#include "keyboardcontroller.hpp"
#include "shader.hpp"

// thirdparty
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// STD
#include <iostream>

using namespace Brain;

Engine::Engine() {
    loadGameObjects();
}

Engine::~Engine() {}

void Engine::run() {
    KeyboardController controller{};
    Shader shader("../shaders/simple_shader.vert", "../shaders/simple_shader.frag");

    float vertices[] = {
        // positions         // colors        // texture coords
         -1.f,  1.f, 0.f,    1.f, 0.f, 0.f,   -0.25f, 1.05f,     // top left
          1.f,  1.f, 0.f,    0.f, 1.f, 0.f,    1.25f, 1.05f,     // top right
          0.f, -1.f, 0.f,    0.f, 0.f, 0.f,    0.5f, -0.5f,     // bottom
    };

    unsigned int indices[] = {   // note start at 0
        0, 1, 2,
    };

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // copy our vertices array in a vertex buffer for OpenGL
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // copy our Indices array in a element buffer for OpenGL
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // textures
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // wireframes
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // texture generation process
    unsigned int texture1, texture2;
    int width, height, nrChannels;
    unsigned char *data;

    //texture 1
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load(std::filesystem::path("../resources/container.jpg").c_str(), &width, &height, &nrChannels, 0);
    if(data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture\n";
    }
    stbi_image_free(data);

    // texture 2
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    data = stbi_load(std::filesystem::path("../resources/awesomeface.png").c_str(), &width, &height, &nrChannels, 0);
    if(data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture\n";
    }
    stbi_image_free(data);

    // set glUseProgram, as well as texture uniforms
    shader.use();
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);
    shader.setFloat("textureOpacity", 0.2);

    while(!window.shouldClose()) {
        controller.process_input(window.getGLFWwindow());

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // :: Drawing Code ::
        // Bind textures to corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // transform & render
        glBindVertexArray(VAO);
        unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
        fibonacci(transformLoc, glm::vec3(0.f, -0.5f, 0.f), glm::mat4(1.f), 7);

        // swap buffers and poll IO events
        glfwSwapBuffers(window.getGLFWwindow());
        glfwPollEvents();
    }

    //optional: de-allocate resources once they've outlived their purpose
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Engine::loadGameObjects() {}

void Engine::fibonacci(unsigned int transformLoc, glm::vec3 translate, glm::mat4 transMatrix, int depth) {
    if(depth < 0) { return; }

    // center
    transMatrix = glm::translate(transMatrix, translate);   // move
    transMatrix = glm::scale(transMatrix, glm::vec3(0.5f)); // scale
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transMatrix));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    --depth;
    fibonacci(transformLoc, glm::vec3(0.f, 1.5f, 0.f), transMatrix, depth);     // top
    fibonacci(transformLoc, glm::vec3(-1.f, -0.5f, 0.f), transMatrix, depth);   // left
    transMatrix = glm::scale(transMatrix, glm::vec3(-1.f, 1.f, 1.f));           // flip matrix on x to reverse texture
    fibonacci(transformLoc, glm::vec3(-1.f, -0.5f, 0.f), transMatrix, depth);   // right side
}
