#include "engine.hpp"
#include "keyboardcontroller.hpp"
#include "shader.hpp"

// thirdparty
#include <OpenGL/gl.h>
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
    glEnable(GL_DEPTH_TEST);
    /*
    float vertices[] = {
        // positions         // colors        // texture coords
         -1.f,  1.f, 0.f,    1.f, 0.f, 0.f,   -0.25f, 1.05f,     // top left
          1.f,  1.f, 0.f,    0.f, 1.f, 0.f,    1.25f, 1.05f,     // top right
          0.f, -1.f, 0.f,    0.f, 0.f, 0.f,    0.5f, -0.5f,     // bottom
    };
    */

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // textures
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
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
        std::println("Failed to load texture\n");
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
        std::println("Failed to load texture\n");
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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // :: Drawing Code ::
        // Bind textures to corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // create transforms
        glm::mat4 view{glm::mat4(1.f)};
        glm::mat4 projection{glm::mat4(1.f)};
        view = glm::translate(view, glm::vec3(0.f, 0.f, -3.f));
        projection = glm::perspective(glm::radians(45.f), static_cast<float>(WIDTH) / static_cast<float>(HEIGHT), 0.1f, 100.f);
        unsigned int viewLoc = glGetUniformLocation(shader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        // transform & render
        glBindVertexArray(VAO);
        for(unsigned int i{}; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.f * i * static_cast<float>(glfwGetTime());
            model = glm::rotate(model, glm::radians(angle), glm::vec3(0.5f, 1.0f, 0.0f));
            shader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        //unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
        //fibonacci(transformLoc, glm::vec3(0.f, -0.5f, 0.f), glm::mat4(1.f), 7);


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

/*
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
*/
