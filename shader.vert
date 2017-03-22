#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;

out vec2 TexCoord;
out vec3 Normal;
out vec3 Tangent;
out vec3 WorldPos;

uniform mat4 modelToWorld;
uniform mat4 worldToView;

void main()
{
    gl_Position = worldToView * modelToWorld * vec4(position, 1.0);
    Normal = vec4(modelToWorld * vec4(normal, 0.0)).xyz;
    TexCoord = texCoord;
    Tangent = vec4(modelToWorld * vec4(tangent, 0.0)).xyz;
    WorldPos = vec4(modelToWorld * vec4(position, 1.0)).xyz;
}
