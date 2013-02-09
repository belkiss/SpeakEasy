#version 330

in  vec4 vs_outColor;

out vec4 fs_outColor;

void main(void)
{
    fs_outColor = vs_outColor;
}
