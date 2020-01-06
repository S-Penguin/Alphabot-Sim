#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D ground_texture;

void main()
{    
    FragColor = texture(ground_texture, TexCoords);
}