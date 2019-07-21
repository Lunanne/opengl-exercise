#version 430
layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) uniform vec3 TransformPosition;

out vec3 Position;
out vec3 Normal;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 MVP;


void main()
{
  vec3 pos = VertexPosition + TransformPosition;
  Normal = normalize( NormalMatrix * VertexNormal);
  Position = vec3( ModelViewMatrix * vec4(pos,1.0));
  gl_Position = MVP * vec4(VertexPosition,1.0);
}

