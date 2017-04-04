#version 440 core
layout (triangles) in;
layout (triangle_strip) out;
layout (max_vertices = 3) out;

in TSE_OUT
{
    vec2 tc;
    float depth;
} geomIn[];

out GEOM_OUT
{
    vec2 tc;
    float depth;
} geomOut;

void main(void)
{
    int i;
    for(i = 0; i<gl_in.length(); i++)
    {
        gl_Position = gl_in[i].gl_Position;
        geomOut.tc = geomIn[i].tc;
        geomOut.depth = geomIn[i].depth;
        EmitVertex();
    }
    EndPrimitive();
}
