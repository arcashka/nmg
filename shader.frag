#version 440 core
in TSE_OUT
{
    vec2 tc;
    float depth;
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
    fColor = texture(diffuseMap, fsIn.tc);//vec4(0.0f, 0.0f, 0.0f, 1.0f);//texture(diffuseMap, fsIn.tc);
    gl_FragCoord.z = fsIn.depth;
    //fColor = vec4(vec3(gl_FragCoord.z), 1.0f);
}
