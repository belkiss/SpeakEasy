#version 150

in vec3 inVertexPosition;
out vec4 outVertexColor_vs;

uniform mat4 projection_matrix;
uniform mat4 modelview_matrix;

void main(void)
{
    vec4 pos = modelview_matrix * vec4(inVertexPosition, 1.0);
    gl_Position = projection_matrix * pos;

    // make the color varying with vertex position
    outVertexColor_vs = vec4(inVertexPosition.x/512,inVertexPosition.y/512,inVertexPosition.z,1.0);
}
