#include "SE_Generator.h"
#include <GL/GLee.h>


//////////////////////////////////////
//////////////////////////////////////
SE_Generator::SE_Generator():
    m_VBOVerticesIndex(0),
    m_VBOIndicesIndex(0)
{
}


//////////////////////////////////////
//////////////////////////////////////
SE_Generator::~SE_Generator()
{
}


//////////////////////////////////////
//////////////////////////////////////
void SE_Generator::generateGround()
{

    GLfloat  pl_Vertices[][3] = 
    {
        { -1.0, -1.0, -1.0 },
        {  1.0, -1.0, -1.0 },
        {  1.0,  1.0, -1.0 },
        { -1.0,  1.0, -1.0 },
        { -1.0, -1.0,  1.0 },
        {  1.0, -1.0,  1.0 },
        {  1.0,  1.0,  1.0 },
        { -1.0,  1.0,  1.0 }
    };

    GLubyte pl_indices[][4] = 
    {
    { 0, 1, 2, 3 },
    { 4, 7, 6, 5 },
    { 0, 4, 5, 1 },
    { 3, 2, 6, 7 },
    { 0, 3, 7, 4 },
    { 1, 5, 6, 2 },
    };

    // Generate And Bind The Vertex Buffer
    glGenBuffersARB( 1, &m_VBOVerticesIndex );                  // Get A Valid Name
    glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_VBOVerticesIndex ); // Bind The Buffer
    glBufferDataARB( GL_ARRAY_BUFFER_ARB, sizeof(pl_Vertices), pl_Vertices, GL_STATIC_DRAW_ARB );    // Load The Data

    glGenBuffersARB( 1, &m_VBOIndicesIndex);                  // Get A Valid Name
    glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, m_VBOIndicesIndex ); // Bind The Buffer
    glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER_ARB, sizeof(pl_indices), pl_indices, GL_STATIC_DRAW_ARB );    // Load The Data
}
