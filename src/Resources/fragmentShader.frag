#version 430
in vec3 Position;
in vec3 Normal;

struct SpotLightInfo {
vec4 position;
vec3 intensity;
vec3 direction;
float exponent;
float cutoff;
};
uniform SpotLightInfo Spot;

uniform vec3 Kd;
uniform vec3 Ka;
uniform vec3 Ks;
uniform float Shininess;


layout (location = 0) out vec4 FragColor;

vec3 ads(){
  vec3 s = normalize( vec3(Spot.position) - Position);
  float angle = acos(dot(-s,Spot.direction));
  float cutoff = radians(clamp(Spot.cutoff,0.0,90.0));
  vec3 ambient = Spot.intensity * Ka;
  if(angle<cutoff){
   float spotFactor = pow(dot(-s,Spot.direction), Spot.exponent);

    vec3 v = normalize(vec3(-Position));
    vec3 h = normalize(v + s);


    return Kd;
 //  return ambient +
         spotFactor * Spot.intensity *(
             Kd * max(dot(s,Normal),0.0)+
             Ks*pow(max(dot(h,Normal),0.0),Shininess));
 }
 else {
   return vec3(0,1,0); //ambient;

   }
}

void main()
{
  FragColor = vec4(ads(),1.0);
}
