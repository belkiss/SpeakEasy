#version 330

layout(location = 0) in vec4 vs_inPosition;
layout(location = 1) in vec4 vs_inColor;

out vec4 vs_outColor;

void main(void)
{
    gl_Position = vs_inPosition;
    vs_outColor = vs_inColor;
}
