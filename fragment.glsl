#version 330 core

out vec4 FragColor;
in vec3 color;

in vec2 TexCoord;

uniform sampler2D ourTexture;

void main() {

    FragColor = texture(ourTexture, TexCoord) * vec4(color, .5f);

}
