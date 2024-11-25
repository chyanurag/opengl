#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum CameraDirection {
    Forward,
    Backward,
    Left,
    Right
};

class Camera {
    public:
        glm::mat4 view;
        glm::vec3 cameraPos = glm::vec3(0.f, 0.f, 3.f);
        glm::vec3 cameraTarget = glm::vec3(0.f, 0.f, 0.f);
        glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
        glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);
        glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
        Camera() {
            view = glm::mat4(1.f);
        }

        void move(enum CameraDirection direction, float time) {
            switch (direction) {
                case Forward:
                    view = glm::translate(view, glm::vec3(0.f, 0.f, time*10.f));
                    break;
                case Backward:
                    view = glm::translate(view, glm::vec3(0.f, 0.f, -time*10.f));
                    break;
                case Left:
                    view = glm::translate(view, glm::vec3(time*10.f, 0.f, 0.f));
                    break;
                case Right:
                    view = glm::translate(view, glm::vec3(-time*10.f, 0.f, 0.f));
                    break;
            }
        }

        void update() {
            const float radius = 2.0f;
            float camX = sin(glfwGetTime()) * radius;
            float camZ = cos(glfwGetTime()) * radius;
            view = glm::mat4(1.f);
            view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        }

        glm::mat4 GetViewMatrix() {
            return view;
        }
};
#endif
