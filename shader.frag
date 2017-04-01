#version 440 core
in TSE_OUT
{
    vec2 tc;
} fsIn;

out highp vec4 fColor;

uniform sampler2D diffuseMap;

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
    fColor = texture(diffuseMap, fsIn.tc);
}
