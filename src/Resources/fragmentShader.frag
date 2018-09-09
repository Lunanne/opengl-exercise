#version 330 core
out vec4 color;
in vec2 UVcoords;
uniform sampler2D texSampler;
void main()
{
//color = texture(texSampler, UVcoords).rgba;
color = vec4(0.7f, 0.7f, 0.7f, 1.0f);
}
