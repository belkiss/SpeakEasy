#version 330

layout(location = 0) in vec4 vs_inPosition;
layout(location = 1) in vec4 vs_inColor;

// smooth is an interpolation qualifier
// There are two other alternatives: noperspective and flat
// If none is provided, smooth will be used by default
smooth out vec4 vs_outColor;

void main(void)
{
    gl_Position = vs_inPosition;
    vs_outColor = vs_inColor;
}
