#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
  
out vec3 ourColor;
uniform float offset;

void main()
{
    gl_Position = vec4(aPos.x*2, aPos.y*2, aPos.z, 1.0);
    ourColor = aColor;
}       
