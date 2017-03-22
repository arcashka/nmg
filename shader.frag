#version 330 core
in highp vec2 TexCoord;
in highp vec3 Normal;
in highp vec3 Tangent;
in highp vec3 WorldPos;

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

uniform sampler2D ourTexture;

uniform sampler2D ourNormalMap;

uniform sampler2D ourSpecMap;

vec4 CalcDiffuseColor()
{
    vec3 normalTemp = normalize(Normal);
    vec3 tangentTemp = normalize(Tangent);
    tangentTemp = normalize(tangentTemp - dot(tangentTemp, normalTemp) * normalTemp);
    vec3 Bitangent = cross(tangentTemp, normalTemp);
    vec3 BumpMapNormal = texture2D(ourNormalMap, TexCoord.xy).xyz;
    BumpMapNormal = 2.0 * BumpMapNormal - vec3(1.0, 1.0, 1.0);
    vec3 NewNormal;
    mat3 TBN = mat3(Tangent, Bitangent, Normal);
    NewNormal = TBN * BumpMapNormal;
    NewNormal = normalize(NewNormal);
    float DiffuseFactor = dot(NewNormal, -light.Direction);

    if(DiffuseFactor > 0)
    {
        return vec4(light.Color, 1.0) *
                light.DiffuseIntensity *
                DiffuseFactor;
    }
    else
        return vec4(0.0, 0.0, 0.0, 0.0);
}

vec4 CalcSpecColor()
{
    vec3 VertexToEye = normalize(vec3(0, 0, 5) - WorldPos);
    vec3 LightReflect = normalize(reflect(light.Direction, normalize(Normal)));
    float SpecularFactor = dot(VertexToEye, LightReflect);
    SpecularFactor = pow(SpecularFactor, light.SpecPower);
    if (SpecularFactor > 0)
    {
        return vec4(light.Color, 1.0f)
                        * texture2D(ourSpecMap, TexCoord.xy) *
                        SpecularFactor;
    }
    else
        return vec4(0, 0, 0, 0);
}

void main()
{
    vec4 DiffuseColor = CalcDiffuseColor();
    vec4 AmbientColor = vec4(light.Color, 1.0) *
            light.AmbientIntensity;
    vec4 SpecularColor = CalcSpecColor();
    fColor = texture2D(ourTexture, TexCoord.xy) *
            (AmbientColor + DiffuseColor);
}
