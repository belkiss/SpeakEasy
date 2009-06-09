#include "SE_Generator.h"
#include <vector>
#include <iostream>

#define GL_GLEXT_PROTOTYPES
#include <QGLWidget>

const unsigned int LAND_SQUARE_SIZE = 15;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
SE_Generator::SE_Generator():
    m_VBOVerticesIndex(0),
    m_VBOIndicesIndex(0),
    m_groundIndicesNb(0)
{
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
SE_Generator::~SE_Generator()
{
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_Generator::generateGround()
{
    std::vector<GLfloat> vl_vertices;
    std::vector<GLubyte> vl_indices;

    m_groundIndicesNb = LAND_SQUARE_SIZE * LAND_SQUARE_SIZE * 6;

    vl_vertices.reserve((LAND_SQUARE_SIZE + 1) * (LAND_SQUARE_SIZE + 1) * 3);
    vl_indices .reserve(m_groundIndicesNb);

    for(unsigned int i = 0; i <= LAND_SQUARE_SIZE; i++)
    {
        for(unsigned int j = 0; j <= LAND_SQUARE_SIZE; j++)
        {
            vl_vertices.push_back( i );// x
            vl_vertices.push_back( j );// y
            vl_vertices.push_back( rand()%2 );// z
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

            vl_indices.push_back((i         * (LAND_SQUARE_SIZE + 1)) + j);
            vl_indices.push_back((( i + 1 ) * (LAND_SQUARE_SIZE + 1)) + j + 1);
            vl_indices.push_back((i         * (LAND_SQUARE_SIZE + 1)) + j + 1);
        }
    }

    // Generate And Bind The Vertex Buffer
    glGenBuffers( 1, &m_VBOVerticesIndex );                  // Generate the name and store it in buffer ID
    glBindBuffer( GL_ARRAY_BUFFER, m_VBOVerticesIndex ); // Bind The Buffer
    glBufferData( GL_ARRAY_BUFFER, vl_vertices.size() * sizeof(GLfloat), &vl_vertices.front(), GL_STATIC_DRAW );    // Load The Data

    glGenBuffers( 1, &m_VBOIndicesIndex);                  // Get A Valid Name
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_VBOIndicesIndex ); // Bind The Buffer
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, m_groundIndicesNb * sizeof(GLubyte),&vl_indices.front(), GL_STATIC_DRAW );    // Load The Data

}
