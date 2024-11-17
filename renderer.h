#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <functional>

class Renderer {
    public:
        GLFWwindow* window;
        Renderer(int WIDTH, int HEIGHT, const char* name) {
            init();
            window = glfwCreateWindow(WIDTH, HEIGHT, name, NULL, NULL);
            if (window == NULL) {
                std::cerr << "Window creation failed\n";
                glfwTerminate();
                std::exit(-1);
            }
            setup_opengl(WIDTH, HEIGHT);
        }

        void setup_opengl(int WIDTH, int HEIGHT) {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwMakeContextCurrent(window);
            glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
            glViewport(0, 0, WIDTH, HEIGHT);
            glClearColor(.2f, .2f, .2f, 1.f);
        }

        void init() {
            glfwInit();
        }

        static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
            glViewport(0, 0, width, height);
        }

        void handle_events() {
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) ==  GLFW_PRESS) {
                glfwSetWindowShouldClose(window, true);
            }
        }

        void run(std::function<void(void)>& draw) {
            while (!glfwWindowShouldClose(window)) {
                handle_events();
                draw();

                glfwSwapBuffers(window);
                glfwPollEvents();
            }
        }

        ~Renderer() {
            glfwTerminate();
        }
};
