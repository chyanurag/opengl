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
    
    Renderer renderer(800, 800, "Opengl");
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
    shader.SetFloat("mixValue", mixValue);

    std::function<void (void)> draw = [&] (){
        glClear(GL_COLOR_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0);
        texture.Bind();
        glActiveTexture(GL_TEXTURE1);
        texture2.Bind();
        shader.SetFloat("mixValue", mixValue);
        shader.use_program();
        if (mixValue < 1.f)  {
            mixValue += .002;
        }
        vao.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    };

    renderer.run(draw);
    return 0;
}
