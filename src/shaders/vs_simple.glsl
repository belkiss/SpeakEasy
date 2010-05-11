#version 150

in vec3 inVertexPosition;
out vec4 outVertexColor_vs;

uniform mat4 projection_matrix;
uniform mat4 modelview_matrix;

uniform int draw_what;

void main(void)
{
    vec4 pos = modelview_matrix * vec4(inVertexPosition, 1.0);
    gl_Position = projection_matrix * pos;

    // make the color varying with vertex position
    if(draw_what == 0) // character
    {
        outVertexColor_vs = vec4(inVertexPosition.z/2.f+0.5,
                                 inVertexPosition.z/2.f+0.5,
                                 inVertexPosition.z/2.f+0.5,
                                 1.0);
    }
    else if(draw_what == 1) // ground
    {
        outVertexColor_vs = vec4(0,
                                 inVertexPosition.z/28.f,
                                 0,
                                 1.0);
    }
    else // buildings
    {
        outVertexColor_vs = vec4(inVertexPosition.z/16.f,
                                 inVertexPosition.z/16.f,
                                 inVertexPosition.z/16.f,
                                 1);
    }
}
