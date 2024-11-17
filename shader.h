#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>

class Shader {
    public:
        unsigned int vertexShader, fragmentShader, shaderProgram;
        Shader(const char* vFile, const char* fFile) {
            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            std::string svShaderSource = read_file(vFile);
            const char* vShaderSource = svShaderSource.c_str();
            glShaderSource(vertexShader, 1, &vShaderSource, NULL);
            glCompileShader(vertexShader);
            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            std::string sfShaderSource = read_file(fFile);
            const char* fShaderSource = sfShaderSource.c_str();
            glShaderSource(fragmentShader, 1, &fShaderSource, NULL);
            glCompileShader(fragmentShader);
            shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram, vertexShader);
            glAttachShader(shaderProgram, fragmentShader);
            glLinkProgram(shaderProgram);
        }

        void use_program() {
            glUseProgram(shaderProgram);
        }

        std::string read_file(const char* file) {
            std::ifstream f(file);
            if (!f.is_open()) {
                std::cerr << "Error: Could not open file " << file << std::endl;
                return "";
            }
            std::string s;
            std::string content;
            while (getline(f, s)) {
                content += s + "\n";
            }
            return content;
        }

        void check_compile_errors(unsigned int shader, const std::string& type) {
            GLint success;
            GLchar infoLog[1024];
            if (type != "PROGRAM") {
                glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                if (success == GL_TRUE) {
                    glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                    std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n";
                }
            } else {
                glGetProgramiv(shader, GL_LINK_STATUS, &success);
                if (success == GL_TRUE) {
                    glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                    std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n";
                }
            }
        }

        void SetInt(std::string property, int value) {
            glUniform1i(glGetUniformLocation(shaderProgram, property.c_str()), value);
        }

        void SetFloat(std::string property, float value) {
            glUniform1f(glGetUniformLocation(shaderProgram, property.c_str()), value);
        }

        ~Shader() {
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            glDeleteProgram(shaderProgram);
        }
};
