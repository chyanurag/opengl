#version 330 core
out vec4 FragColor;  
in vec3 ourColor;

uniform float offset;
void main()
{
    FragColor = vec4(ourColor*offset, 1.0);
}
