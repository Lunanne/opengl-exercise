#version 430
in vec3 Position;
in vec3 Normal;

uniform vec4 LightPosition;
uniform vec3 LightIntensity;
uniform vec3 Kd;
uniform vec3 Ka;

const int levels = 6 ;
const float scaleFactor = 1.0f;

layout (location = 0) out vec4 FragColor;

vec3 toonShade(){
  vec3 s = normalize(LightPosition.xyz - Position.xyz);
  float cosine = max (0.0, dot ( s, Normal));
  vec3 diffuse = Kd * floor ( cosine * levels ) * scaleFactor;
  return LightIntensity * (Ka +
                           diffuse) ;
  }

void main()
{
  FragColor = vec4(toonShade(),1.0);
}
