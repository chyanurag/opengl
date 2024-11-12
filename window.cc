#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

int main() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glewInit();

    GLFWwindow* window = glfwCreateWindow(800, 800, "Opengl Window", NULL, NULL);
    glfwMakeContextCurrent(window);
    glViewport(0, 0, 800, 800);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 1.f, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
