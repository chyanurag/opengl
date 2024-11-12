#include <iostream>
#include <GL/glew.h>
#include <cmath>
#include "shader.h"
#include <GLFW/glfw3.h>

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_CAPS_LOCK) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

float vertices[] = {
    // position      colors
    -.5f, -.5f, 0.f, 1.0f, 0.f, 0.f, // bottom right
    .5f,  -.5f, 0.f, 0.f, 1.f, 0.f, // bottom left
    .0f,  .5f, 0.f, 0.f, 0.f, 1.f, // top
};

int main() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "Opengl", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Error creating window" << '\n';
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glViewport(0, 0, 800, 800);

    glewInit();
    Shader shader("./vertex.glsl", "./fragment.glsl");
    unsigned int VAO;
    unsigned int VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    float offset = .01f;

    while(!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.3f, .3f, .3f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        shader.setFloat("ourColor", 1.0f);
        shader.setFloat("offset", offset);
        offset += .01f;
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
