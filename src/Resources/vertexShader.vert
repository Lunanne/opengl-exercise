#version 430
layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexTexCoord;

out vec3 TexCoord;

uniform vec3 transform_position;
uniform mat4 MVP;

void main()
{
TexCoord = VertexPosition;
vec3 position = VertexPosition + transform_position;
gl_Position =  MVP * vec4(position, 1);
}
