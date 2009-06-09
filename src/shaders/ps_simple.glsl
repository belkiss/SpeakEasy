#version 130

in vec4 outVertexColor_vs;
out vec4 outVertexColor_ps;

void main(void)
{
    outVertexColor_ps = outVertexColor_vs;
}
