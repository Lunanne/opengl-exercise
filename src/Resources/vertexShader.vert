#version 430
in vec3 in_position;

uniform vec3 transform_position;
uniform mat4 MVP;
void main()
{
vec3 position = in_position + transform_position;
gl_Position =  MVP * vec4(position, 1);
}
