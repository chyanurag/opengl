#include <GL/glew.h>
#include <GL/gl.h>
#include "stb.h"
#include <string>

class Texture2D { 
    public:
        GLuint texture;
        unsigned char* data;
        Texture2D(std::string filename) {
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            int width, height, nrChannels;
            data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
            if(filename.find(".jpg") != std::string::npos) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            } else if(filename.find(".png") != std::string::npos) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            }
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        void Bind() {
            glBindTexture(GL_TEXTURE_2D, texture);
        }

        ~Texture2D() {
            stbi_image_free(data);
        }
};

