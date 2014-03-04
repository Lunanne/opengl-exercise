#version 120 
attribute vec3 in_position;
uniform mat4 MVP;
void main()
{
gl_Position =  MVP * vec4(in_position,1);
};
