#include "SE_Generator.h"
#include <GL/GLee.h>
#include <vector>
#include <iostream>

const unsigned int LAND_SQUARE_SIZE = 15;

//////////////////////////////////////
//////////////////////////////////////
SE_Generator::SE_Generator():
    m_VBOVerticesIndex(0),
    m_VBOIndicesIndex(0),
    m_groundIndicesNb(0)
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
    std::vector<GLfloat> vl_vertices;
    std::vector<GLubyte> vl_indices;

    m_groundIndicesNb = LAND_SQUARE_SIZE * LAND_SQUARE_SIZE * 4;

    vl_vertices.reserve((LAND_SQUARE_SIZE + 1) * (LAND_SQUARE_SIZE + 1) * 3);
    vl_indices .reserve(m_groundIndicesNb);

    for(unsigned int i = 0; i <= LAND_SQUARE_SIZE; i++)
    {
        for(unsigned int j = 0; j <= LAND_SQUARE_SIZE; j++)
        {
            vl_vertices.push_back( i );// x
            vl_vertices.push_back( j );// y
            vl_vertices.push_back( 0 );// z
        }
    }

    for(unsigned int i = 0; i < LAND_SQUARE_SIZE; i++)
    {
        for(unsigned int j = 0; j < LAND_SQUARE_SIZE; j++)
        {
            // note : the order is very important !!!!
            vl_indices.push_back((i         * (LAND_SQUARE_SIZE + 1)) + j);
            vl_indices.push_back((( i + 1 ) * (LAND_SQUARE_SIZE + 1)) + j);
            vl_indices.push_back((( i + 1 ) * (LAND_SQUARE_SIZE + 1)) + j + 1);
            vl_indices.push_back((i         * (LAND_SQUARE_SIZE + 1)) + j + 1);
        }
    }

    // Generate And Bind The Vertex Buffer
    glGenBuffersARB( 1, &m_VBOVerticesIndex );                  // Get A Valid Name
    glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_VBOVerticesIndex ); // Bind The Buffer
    glBufferDataARB( GL_ARRAY_BUFFER_ARB, vl_vertices.size() * sizeof(GLfloat), &vl_vertices.front(), GL_STATIC_DRAW_ARB );    // Load The Data

    glGenBuffersARB( 1, &m_VBOIndicesIndex);                  // Get A Valid Name
    glBindBufferARB( GL_ELEMENT_ARRAY_BUFFER_ARB, m_VBOIndicesIndex ); // Bind The Buffer
    glBufferDataARB( GL_ELEMENT_ARRAY_BUFFER_ARB, m_groundIndicesNb * sizeof(GLubyte),&vl_indices.front(), GL_STATIC_DRAW_ARB );    // Load The Data
}
