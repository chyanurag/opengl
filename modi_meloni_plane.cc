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
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.7f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 0.7f, 0.0f,   0.0f, 1.0f  // top left 
    };
unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

int main() {
    
    const int WIDTH = 1000;
    const int HEIGHT = 1000;
    Renderer renderer(WIDTH, HEIGHT, "Opengl");
    glewInit();

    Shader shader("vertex.glsl", "fragment.glsl");
    VAO vao;
    vao.Bind();

    VBO vbo(vertices, sizeof(vertices));
    EBO ebo(indices, sizeof(indices));

    vao.LinkVertexAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vao.LinkVertexAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3*sizeof(float)));
    vao.LinkVertexAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6*sizeof(float)));
    vao.Unbind();
    vbo.Unbind();

    stbi_set_flip_vertically_on_load(true);

    Texture2D texture("modiji.jpg");
    Texture2D texture2("meloni.png");

    shader.use_program();
    shader.SetInt("texture1", 0);
    shader.SetInt("texture2", 1);

    float mixValue = .1f;
    float mixMult = 1.f;
    float angle = 0.f;
    float angleMult = 1.f;

    shader.SetFloat("mixValue", mixValue);

    shader.use_program();

    glm::mat4 proj = glm::perspective(glm::radians(90.f),(float)WIDTH/(float)HEIGHT, .1f, 5000.f);
    glm::mat4 model = glm::mat4(1.f);
    model = glm::rotate(model, glm::radians(-55.f), glm::vec3(1.f, 0.f, 0.f));
    glm::mat4 view = glm::mat4(1.f);
    view = glm::translate(view, glm::vec3(0.f, 0.f, -1.f));

    shader.SetMat4("model", model);
    shader.SetMat4("projection", proj);
    shader.SetMat4("view", view);

    glm::mat4 trans = glm::mat4(1.f);

    std::function<void (void)> draw = [&] (){
        glClear(GL_COLOR_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0);
        texture.Bind();
        glActiveTexture(GL_TEXTURE1);
        texture2.Bind();
        shader.use_program();
        if (mixValue > 1.f) {
            mixMult = -1.f;
        } else if (mixValue < 0.f) {
            mixMult = 1.f;
        }
        mixValue += mixMult * .001f;
        angle += .005f;
        shader.SetFloat("mixValue", mixValue);
        trans = glm::rotate(trans, glm::radians(angle), glm::vec3(0.f, 0.f, 1.f));
        shader.SetMat4("transform", trans);
        vao.Bind();
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    };

    renderer.run(draw);
    return 0;
}
