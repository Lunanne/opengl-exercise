#version 430
in vec3 in_position;

in vec2 in_texCoords;

out vec2 UVcoords;
uniform vec3 transform_position;
uniform mat4 MVP;
void main()
{
vec3 position = in_position + transform_position;
gl_Position =  MVP * vec4(position, 1);
UVcoords = in_texCoords;
}
