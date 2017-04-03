#version 440 core
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
    vec4 noral = modelToWorld * fsIn.normal;
    noral = normalize(noral);
    float lightFactor = dot(vec4(light.Direction, 1.0), noral);
    //fColor = noral;
    fColor = texture(diffuseMap, fsIn.tc) + lightFactor * 0.5f;
    //vec4(0.0f, 0.0f, 0.0f, 1.0f);//texture(diffuseMap, fsIn.tc);
    //gl_FragCoord.z = fsIn.depth;
    //fColor = vec4(vec3(gl_FragCoord.z), 1.0f);
}
