#ifndef VAO_H
#define VAO_H

#include "vbo.h"

class VAO {
    public:
        GLuint ID;
        VAO() {
            glGenVertexArrays(1, &ID);
        }

        void LinkVertexAttrib(VBO vbo, GLuint layout, GLuint components, GLenum type, GLsizeiptr stride, void* offset) {
            vbo.Bind();
            glVertexAttribPointer(layout, components, type, GL_FALSE, stride, offset);
            glEnableVertexAttribArray(layout);
            vbo.Unbind();
        }
    
        void Bind() {
            glBindVertexArray(ID);
        }

        void Unbind() {
            glBindVertexArray(0);
        }

        ~VAO() {
            glDeleteVertexArrays(1, &ID);
        }
};

#endif
