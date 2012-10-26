#version 330

in  vec4 vs_outColor;

out vec4 ps_outColor;

void main(void)
{
    ps_outColor = vs_outColor;
}
