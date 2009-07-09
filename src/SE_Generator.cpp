#include "SE_Generator.h"

#include <iostream>
#include <cstdlib>
#include <SFML/System/Randomizer.hpp>

unsigned int SQUARELAND_SIDE_ELEMENTS_NB = 10;
unsigned int SQUARELAND_SIDE_SIZE = 50;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
SE_Generator::SE_Generator():
    m_VBOVerticesIndex(0),
    m_VBOIndicesIndex(0),
    m_groundIndicesNb(0)
{
    // set the seed for the random number generator
    unsigned int seed = 10;
    sf::Randomizer::SetSeed(seed);
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
    float step = (float)SQUARELAND_SIDE_SIZE / SQUARELAND_SIDE_ELEMENTS_NB;

    m_groundIndicesNb = SQUARELAND_SIDE_ELEMENTS_NB * SQUARELAND_SIDE_ELEMENTS_NB * 6;

    m_ground_vertices.reserve((SQUARELAND_SIDE_ELEMENTS_NB + 1) * (SQUARELAND_SIDE_ELEMENTS_NB + 1) * 3);
    m_ground_indices .reserve(m_groundIndicesNb);

    for(unsigned int i = 0; i <= SQUARELAND_SIDE_ELEMENTS_NB; i++)
    {
        for(unsigned int j = 0; j <= SQUARELAND_SIDE_ELEMENTS_NB; j++)
        {
            m_ground_vertices.push_back( i*step );// x
            m_ground_vertices.push_back( j*step );// y
            float tmp = sf::Randomizer::Random(-10.f, 2.f);
            // the test is here to create planes
            m_ground_vertices.push_back( tmp > 0 ? tmp : 0 );// z
        }
    }

    for(unsigned int i = 0; i < SQUARELAND_SIDE_ELEMENTS_NB; i++)
    {
        for(unsigned int j = 0; j < SQUARELAND_SIDE_ELEMENTS_NB; j++)
        {
            // note : the order is very important !!!!
            m_ground_indices.push_back((i         * (SQUARELAND_SIDE_ELEMENTS_NB + 1)) + j);
            m_ground_indices.push_back((( i + 1 ) * (SQUARELAND_SIDE_ELEMENTS_NB + 1)) + j);
            m_ground_indices.push_back((( i + 1 ) * (SQUARELAND_SIDE_ELEMENTS_NB + 1)) + j + 1);

            m_ground_indices.push_back((i         * (SQUARELAND_SIDE_ELEMENTS_NB + 1)) + j);
            m_ground_indices.push_back((( i + 1 ) * (SQUARELAND_SIDE_ELEMENTS_NB + 1)) + j + 1);
            m_ground_indices.push_back((i         * (SQUARELAND_SIDE_ELEMENTS_NB + 1)) + j + 1);
        }
    }

    // Generate And Bind The Vertex Buffer
    glGenBuffers( 1, &m_VBOVerticesIndex );                  // Generate the name and store it in buffer ID
    glBindBuffer( GL_ARRAY_BUFFER, m_VBOVerticesIndex ); // Bind The Buffer
    glBufferData( GL_ARRAY_BUFFER, m_ground_vertices.size() * sizeof(GLfloat), &m_ground_vertices.front(), GL_STATIC_DRAW );    // Load The Data

    glGenBuffers( 1, &m_VBOIndicesIndex);                  // Get A Valid Name
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_VBOIndicesIndex ); // Bind The Buffer
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, m_groundIndicesNb * sizeof(GLuint),&m_ground_indices.front(), GL_STATIC_DRAW );    // Load The Data

}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_Generator::subdivideGround()
{
    SQUARELAND_SIDE_ELEMENTS_NB++;

    float step = (float)SQUARELAND_SIDE_SIZE / SQUARELAND_SIDE_ELEMENTS_NB;

    std::vector<GLfloat> vl_vertices;
    std::vector<GLuint> vl_indices;

    m_groundIndicesNb = SQUARELAND_SIDE_ELEMENTS_NB * SQUARELAND_SIDE_ELEMENTS_NB * 6;

    vl_vertices.reserve((SQUARELAND_SIDE_ELEMENTS_NB + 1) * (SQUARELAND_SIDE_ELEMENTS_NB + 1) * 3);
    vl_indices .reserve(m_groundIndicesNb);

    for(unsigned int i = 0; i <= SQUARELAND_SIDE_ELEMENTS_NB; i++)
    {
        for(unsigned int j = 0; j <= SQUARELAND_SIDE_ELEMENTS_NB; j++)
        {
            vl_vertices.push_back( i*step );// x
            vl_vertices.push_back( j*step );// y
            float tmp = sf::Randomizer::Random(-10.f, 2.f);
            // the test is here to create planes
            vl_vertices.push_back( tmp > 0 ? tmp : 0 );// z
        }
    }

    for(unsigned int i = 0; i < SQUARELAND_SIDE_ELEMENTS_NB; i++)
    {
        for(unsigned int j = 0; j < SQUARELAND_SIDE_ELEMENTS_NB; j++)
        {
            // note : the order is very important !!!!
            vl_indices.push_back((i         * (SQUARELAND_SIDE_ELEMENTS_NB + 1)) + j);
            vl_indices.push_back((( i + 1 ) * (SQUARELAND_SIDE_ELEMENTS_NB + 1)) + j);
            vl_indices.push_back((( i + 1 ) * (SQUARELAND_SIDE_ELEMENTS_NB + 1)) + j + 1);

            vl_indices.push_back((i         * (SQUARELAND_SIDE_ELEMENTS_NB + 1)) + j);
            vl_indices.push_back((( i + 1 ) * (SQUARELAND_SIDE_ELEMENTS_NB + 1)) + j + 1);
            vl_indices.push_back((i         * (SQUARELAND_SIDE_ELEMENTS_NB + 1)) + j + 1);
        }
    }

    glBindBuffer( GL_ARRAY_BUFFER, m_VBOVerticesIndex ); // Bind The Buffer
    glBufferData( GL_ARRAY_BUFFER, vl_vertices.size() * sizeof(GLfloat), &vl_vertices.front(), GL_STATIC_DRAW );    // Load The Data

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_VBOIndicesIndex ); // Bind The Buffer
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, m_groundIndicesNb * sizeof(GLuint),&vl_indices.front(), GL_STATIC_DRAW );    // Load The Data
}

