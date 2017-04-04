#version 440 core
layout (depth_any) out float gl_FragDepth;

in TSE_OUT
{
    vec2 tc;
    float depth;
    vec4 normal;
} fsIn;

out highp vec4 fColor;
uniform mat4 modelToWorld;
uniform mat4 worldToCamera;
uniform mat4 cameraToView;
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
    gl_FragDepth = fsIn.depth;
    fColor = texture(diffuseMap, fsIn.tc);
}
