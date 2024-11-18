// comment
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include "renderer.h"
#include "shader.h"
#include "vbo.h"
#include "vao.h"
#include "ebo.h"
#include "stb.h"
#include "texture.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

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

float zTrans = 0.f;
float xTrans = 0.f;

float xRot = 0.f;
float yRot = 0.f;
float zRot = 0.f;

void process_events(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        zTrans += .1f;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        zTrans -= .1f;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        xTrans -= .1f;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        xTrans += .1f;
    }
}

int main() {
    
    const int WIDTH = 800;
    const int HEIGHT = 800;
    Renderer renderer(WIDTH, HEIGHT, "Opengl");
    glewInit();

    Shader shader("vertex.glsl", "fragment.glsl");
    VAO vao;
    vao.Bind();

    VBO vbo(vertices, sizeof(vertices));
    EBO ebo(indices, sizeof(indices));

    vao.LinkVertexAttrib(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
    vao.LinkVertexAttrib(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3*sizeof(float)));
    vao.Unbind();
    vbo.Unbind();

    stbi_set_flip_vertically_on_load(true);

    Texture2D texture("cube.jpg");

    shader.use_program();
    shader.SetInt("texture1", 0);

    float angle = 0.f;

    glEnable(GL_DEPTH_TEST);
    glm::mat4 view          = glm::mat4(1.0f);
    glm::mat4 projection    = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(90.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    view       = glm::translate(view, glm::vec3(xTrans, 0.0f, -2.f));
    glm::mat4 model = glm::mat4(1.0f);
    shader.SetMat4("model", model);
    shader.SetMat4("projection", projection);
    shader.SetMat4("view", view);

    std::function<void (void)> draw = [&] (){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0);
        texture.Bind();

        shader.use_program();
        angle += .01f;
        view = glm::rotate(view, glm::radians(angle), glm::vec3(1.f, 1.f, 1.f));
        shader.SetMat4("view", view);
        vao.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);
        process_events(renderer.window);
    };

    renderer.run(draw);
    return 0;
}
