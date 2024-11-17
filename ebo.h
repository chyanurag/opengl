#ifndef EBO_H
#define EBO_H
#include <GL/glew.h>
#include <GL/gl.h>

class EBO {
    public:
        GLuint ID;
        EBO(GLuint* indices, GLsizeiptr size) {
            glGenBuffers(1, &ID);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
        }

        void Bind() {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
        }

        void Unbind() {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        ~EBO() {
            glDeleteBuffers(1, &ID);
        }
};
#endif
