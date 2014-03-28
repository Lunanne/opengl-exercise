#version 330 core
in vec3 in_position;

in vec2 in_texCoords;

out vec2 UVcoords;

uniform mat4 MVP;
void main()
{
gl_Position =  MVP * vec4(in_position,1);
UVcoords = in_texCoords;
}
