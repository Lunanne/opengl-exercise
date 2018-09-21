#version 430
in vec3 Position;
in vec3 Normal;

uniform vec4 LightPosition;
uniform vec3 LightIntensity;
uniform vec3 Kd;
uniform vec3 Ka;
uniform vec3 Ks;
uniform float Shininess;

struct FogInfo {
float maxDist;
float minDist;
vec3 color;
};

uniform FogInfo Fog;

layout (location = 0) out vec4 FragColor;

vec3 ads(){
  vec3 n = normalize(Normal);
  vec3 s = normalize( vec3(LightPosition) - Position);
  vec3 v = normalize(vec3(-Position));
  vec3 h = normalize(v + s);
  return LightIntensity * (Ka +
                           Kd * max( dot(s,Normal),0.0) +
                           Ks * pow( max( dot(h,n), 0.0), Shininess));
  }

void main()
{
  float dist = abs(Position.z);
  float fogFactor =  (Fog.maxDist-dist)/(Fog.maxDist-Fog.minDist);
  fogFactor = clamp (fogFactor, 0.0,1.0);
 vec3 shadeColor   = ads();
 vec3 color  = mix(Fog.color, shadeColor, fogFactor);
  FragColor = vec4(color,1.0);
}
