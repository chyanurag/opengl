#ifndef VBO_H
#define VBO_H
#include <GL/glew.h>
#include <GL/gl.h>
#include <fstream>
#include <iostream>
#include <sstream>

class VBO {
    public:
        GLuint ID;
        VBO(GLfloat* vertices, int size) {
            glGenBuffers(1, &ID);
            glBindBuffer(GL_ARRAY_BUFFER, ID);
            glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW);
        }

        void Bind() {
            glBindBuffer(GL_ARRAY_BUFFER, ID);
        }

        void Unbind() {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        ~VBO() {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
};
#endif
