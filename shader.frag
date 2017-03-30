#version 330 core
in highp vec3 posColor;

out highp vec4 fColor;

struct Light
{
    vec3 Color;
    float AmbientIntensity;
    float DiffuseIntensity;
    vec3 Direction;
    float SpecPower;
};

uniform Light light;

void main()
{
    fColor = vec4(posColor, 1.0);
}
