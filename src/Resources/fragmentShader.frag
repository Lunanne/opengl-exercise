#version 430

in vec3 TexCoord;
layout (location = 0) out vec4 FragColor;

layout (binding = 0) uniform BlobSettings {
vec4 InnerColor;
vec4 OuterColor;
float InnerRadius;
float OuterRadius;
};

void main()
{
float dist = sqrt(TexCoord.x * TexCoord.x + TexCoord.y * TexCoord.y);
FragColor = mix(InnerColor, OuterColor, smoothstep(InnerRadius, OuterRadius, dist));
}
