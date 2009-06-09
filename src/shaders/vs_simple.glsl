#version 130

in vec3 inVertexPosition;
out vec4 outVertexColor_vs;

uniform mat4 projection_matrix;
uniform mat4 modelview_matrix;

void main(void)
{
    vec4 pos = modelview_matrix * vec4(inVertexPosition, 1.0);
    gl_Position = projection_matrix * pos;

    // make the color varying with vertex position
    outVertexColor_vs = vec4(pos.x/10,pos.y/10,pos.z/10,1.0);
}
