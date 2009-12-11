#ifdef _WIN32
#include "GLee.h"
#endif
#include "SE_Generator.h"

#include <iostream>
#include <cstdlib>
#include <SFML/System/Randomizer.hpp>


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
SE_Generator::SE_Generator():
    m_VBOGroundVerticesIndex(0),
    m_VBOGroundIndicesIndex(0),
    m_groundSideElementsNb(50),
    m_groundSideSize(50),
    m_groundIndicesNb(0),
    m_VBOBuildingsVerticesIndex(0),
    m_VBOBuildingsIndicesIndex(0)
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
    float step = 10;//(float)m_groundSideSize / m_groundSideElementsNb;

    m_groundIndicesNb = m_groundSideElementsNb * m_groundSideElementsNb * 6;

    m_ground_vertices.reserve((m_groundSideElementsNb + 1) * (m_groundSideElementsNb + 1) * 3);
    m_ground_indices .reserve(m_groundIndicesNb);

    for(unsigned int i = 0; i <= m_groundSideElementsNb; i++)
    {
        for(unsigned int j = 0; j <= m_groundSideElementsNb; j++)
        {
            m_ground_vertices.push_back( i*step );// x
            m_ground_vertices.push_back( j*step );// y
            float tmp = sf::Randomizer::Random(-10.f, 2.f);
            // the test is here to create planes
            m_ground_vertices.push_back( tmp > 0 ? tmp : 0 );// z
        }
    }

    for(unsigned int i = 0; i < m_groundSideElementsNb; i++)
    {
        for(unsigned int j = 0; j < m_groundSideElementsNb; j++)
        {
            // note : the order is very important !!!!
            m_ground_indices.push_back((i         * (m_groundSideElementsNb + 1)) + j);
            m_ground_indices.push_back((( i + 1 ) * (m_groundSideElementsNb + 1)) + j);
            m_ground_indices.push_back((( i + 1 ) * (m_groundSideElementsNb + 1)) + j + 1);

            m_ground_indices.push_back((i         * (m_groundSideElementsNb + 1)) + j);
            m_ground_indices.push_back((( i + 1 ) * (m_groundSideElementsNb + 1)) + j + 1);
            m_ground_indices.push_back((i         * (m_groundSideElementsNb + 1)) + j + 1);
        }
    }

    // Generate And Bind The Vertex Buffer
    glGenBuffers( 1, &m_VBOGroundVerticesIndex );                  // Generate the name and store it in buffer ID
    glBindBuffer( GL_ARRAY_BUFFER, m_VBOGroundVerticesIndex ); // Bind The Buffer
    glBufferData( GL_ARRAY_BUFFER, m_ground_vertices.size() * sizeof(GLfloat), &m_ground_vertices.front(), GL_STATIC_DRAW );    // Load The Data

    glGenBuffers( 1, &m_VBOGroundIndicesIndex);                  // Get A Valid Name
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_VBOGroundIndicesIndex ); // Bind The Buffer
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, m_groundIndicesNb * sizeof(GLuint),&m_ground_indices.front(), GL_STATIC_DRAW );    // Load The Data

}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_Generator::generateBuildings()
{
    for(unsigned int i = 0; i < m_groundSideElementsNb; i+=2)
    {
        for(unsigned int j = 0; j < m_groundSideElementsNb; j+=2)
        {
            if( m_ground_vertices.at(((i         * (m_groundSideElementsNb + 1)) + j)    *3 + 2) == 0 &&
                m_ground_vertices.at(((i         * (m_groundSideElementsNb + 1)) + j + 1)*3 + 2) == 0 &&
                m_ground_vertices.at(((( i + 1 ) * (m_groundSideElementsNb + 1)) + j + 1)*3 + 2) == 0 &&
                m_ground_vertices.at(((( i + 1 ) * (m_groundSideElementsNb + 1)) + j)    *3 + 2) == 0)
            {
                // ground
                m_buildings_vertices.push_back(m_ground_vertices.at(((i         * (m_groundSideElementsNb + 1)) + j)    *3 + 0));
                m_buildings_vertices.push_back(m_ground_vertices.at(((i         * (m_groundSideElementsNb + 1)) + j)    *3 + 1));
                m_buildings_vertices.push_back(0.f);

                m_buildings_vertices.push_back(m_ground_vertices.at(((i         * (m_groundSideElementsNb + 1)) + j + 1)*3 + 0));
                m_buildings_vertices.push_back(m_ground_vertices.at(((i         * (m_groundSideElementsNb + 1)) + j + 1)*3 + 1));
                m_buildings_vertices.push_back(0.f);

                m_buildings_vertices.push_back(m_ground_vertices.at(((( i + 1 ) * (m_groundSideElementsNb + 1)) + j + 1)*3 + 0));
                m_buildings_vertices.push_back(m_ground_vertices.at(((( i + 1 ) * (m_groundSideElementsNb + 1)) + j + 1)*3 + 1));
                m_buildings_vertices.push_back(0.f);

                m_buildings_vertices.push_back(m_ground_vertices.at(((( i + 1 ) * (m_groundSideElementsNb + 1)) + j)    *3 + 0));
                m_buildings_vertices.push_back(m_ground_vertices.at(((( i + 1 ) * (m_groundSideElementsNb + 1)) + j)    *3 + 1));
                m_buildings_vertices.push_back(0.f);

                // roof
                float height = (float)sf::Randomizer::Random(20, 60);
                m_buildings_vertices.push_back(m_ground_vertices.at(((i         * (m_groundSideElementsNb + 1)) + j)    *3 + 0));
                m_buildings_vertices.push_back(m_ground_vertices.at(((i         * (m_groundSideElementsNb + 1)) + j)    *3 + 1));
                m_buildings_vertices.push_back(height);

                m_buildings_vertices.push_back(m_ground_vertices.at(((i         * (m_groundSideElementsNb + 1)) + j + 1)*3 + 0));
                m_buildings_vertices.push_back(m_ground_vertices.at(((i         * (m_groundSideElementsNb + 1)) + j + 1)*3 + 1));
                m_buildings_vertices.push_back(height);

                m_buildings_vertices.push_back(m_ground_vertices.at(((( i + 1 ) * (m_groundSideElementsNb + 1)) + j + 1)*3 + 0));
                m_buildings_vertices.push_back(m_ground_vertices.at(((( i + 1 ) * (m_groundSideElementsNb + 1)) + j + 1)*3 + 1));
                m_buildings_vertices.push_back(height);

                m_buildings_vertices.push_back(m_ground_vertices.at(((( i + 1 ) * (m_groundSideElementsNb + 1)) + j)    *3 + 0));
                m_buildings_vertices.push_back(m_ground_vertices.at(((( i + 1 ) * (m_groundSideElementsNb + 1)) + j)    *3 + 1));
                m_buildings_vertices.push_back(height);

                unsigned int nb_previous_vertices = m_buildings_vertices.size() / 3;
                m_buildings_indices.push_back(nb_previous_vertices + 0);
                m_buildings_indices.push_back(nb_previous_vertices + 1);
                m_buildings_indices.push_back(nb_previous_vertices + 2);

                m_buildings_indices.push_back(nb_previous_vertices + 2);
                m_buildings_indices.push_back(nb_previous_vertices + 3);
                m_buildings_indices.push_back(nb_previous_vertices + 0);

                m_buildings_indices.push_back(nb_previous_vertices + 4);
                m_buildings_indices.push_back(nb_previous_vertices + 1);
                m_buildings_indices.push_back(nb_previous_vertices + 0);

                m_buildings_indices.push_back(nb_previous_vertices + 4);
                m_buildings_indices.push_back(nb_previous_vertices + 5);
                m_buildings_indices.push_back(nb_previous_vertices + 1);

                m_buildings_indices.push_back(nb_previous_vertices + 3);
                m_buildings_indices.push_back(nb_previous_vertices + 2);
                m_buildings_indices.push_back(nb_previous_vertices + 6);

                m_buildings_indices.push_back(nb_previous_vertices + 3);
                m_buildings_indices.push_back(nb_previous_vertices + 6);
                m_buildings_indices.push_back(nb_previous_vertices + 7);

                m_buildings_indices.push_back(nb_previous_vertices + 2);
                m_buildings_indices.push_back(nb_previous_vertices + 1);
                m_buildings_indices.push_back(nb_previous_vertices + 5);

                m_buildings_indices.push_back(nb_previous_vertices + 2);
                m_buildings_indices.push_back(nb_previous_vertices + 5);
                m_buildings_indices.push_back(nb_previous_vertices + 6);

                m_buildings_indices.push_back(nb_previous_vertices + 0);
                m_buildings_indices.push_back(nb_previous_vertices + 3);
                m_buildings_indices.push_back(nb_previous_vertices + 7);

                m_buildings_indices.push_back(nb_previous_vertices + 0);
                m_buildings_indices.push_back(nb_previous_vertices + 7);
                m_buildings_indices.push_back(nb_previous_vertices + 4);

                m_buildings_indices.push_back(nb_previous_vertices + 4);
                m_buildings_indices.push_back(nb_previous_vertices + 7);
                m_buildings_indices.push_back(nb_previous_vertices + 6);

                m_buildings_indices.push_back(nb_previous_vertices + 4);
                m_buildings_indices.push_back(nb_previous_vertices + 6);
                m_buildings_indices.push_back(nb_previous_vertices + 5);
            }
        }
    }

    // Generate And Bind The Vertex Buffer
    glGenBuffers( 1, &m_VBOBuildingsVerticesIndex );                  // Generate the name and store it in buffer ID
    glBindBuffer( GL_ARRAY_BUFFER, m_VBOBuildingsVerticesIndex ); // Bind The Buffer
    glBufferData( GL_ARRAY_BUFFER, m_buildings_vertices.size() * sizeof(GLfloat), &m_buildings_vertices.front(), GL_STATIC_DRAW );    // Load The Data

    glGenBuffers( 1, &m_VBOBuildingsIndicesIndex);                  // Get A Valid Name
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_VBOBuildingsIndicesIndex ); // Bind The Buffer
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, m_buildings_indices.size() * sizeof(GLuint),&m_buildings_indices.front(), GL_STATIC_DRAW );    // Load The Data
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_Generator::subdivideGround()
{
    m_groundSideElementsNb++;

    float step = 10;//(float)m_groundSideSize / m_groundSideElementsNb;

    std::vector<GLfloat> vl_vertices;
    std::vector<GLuint> vl_indices;

    m_groundIndicesNb = m_groundSideElementsNb * m_groundSideElementsNb * 6;

    vl_vertices.reserve((m_groundSideElementsNb + 1) * (m_groundSideElementsNb + 1) * 3);
    vl_indices .reserve(m_groundIndicesNb);

    for(unsigned int i = 0; i <= m_groundSideElementsNb; i++)
    {
        for(unsigned int j = 0; j <= m_groundSideElementsNb; j++)
        {
            vl_vertices.push_back( i*step );// x
            vl_vertices.push_back( j*step );// y
            float tmp = sf::Randomizer::Random(-10.f, 2.f);
            // the test is here to create planes
            vl_vertices.push_back( tmp > 0 ? tmp : 0 );// z
        }
    }

    for(unsigned int i = 0; i < m_groundSideElementsNb; i++)
    {
        for(unsigned int j = 0; j < m_groundSideElementsNb; j++)
        {
            // note : the order is very important !!!!
            vl_indices.push_back((i         * (m_groundSideElementsNb + 1)) + j);
            vl_indices.push_back((( i + 1 ) * (m_groundSideElementsNb + 1)) + j);
            vl_indices.push_back((( i + 1 ) * (m_groundSideElementsNb + 1)) + j + 1);

            vl_indices.push_back((i         * (m_groundSideElementsNb + 1)) + j);
            vl_indices.push_back((( i + 1 ) * (m_groundSideElementsNb + 1)) + j + 1);
            vl_indices.push_back((i         * (m_groundSideElementsNb + 1)) + j + 1);
        }
    }

    glBindBuffer( GL_ARRAY_BUFFER, m_VBOGroundVerticesIndex ); // Bind The Buffer
    glBufferData( GL_ARRAY_BUFFER, vl_vertices.size() * sizeof(GLfloat), &vl_vertices.front(), GL_STATIC_DRAW );    // Load The Data

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_VBOGroundIndicesIndex ); // Bind The Buffer
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, m_groundIndicesNb * sizeof(GLuint),&vl_indices.front(), GL_STATIC_DRAW );    // Load The Data
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_Generator::drawGround(const GLuint inProgramId)
{
    GLuint location = glGetUniformLocation(inProgramId,"draw_what");
    glUniform1i(location, 1);

    glBindBuffer( GL_ARRAY_BUFFER, m_VBOGroundVerticesIndex ); // Bind The Buffer
    // instead of (char*) there is a macro BUFFER_OFFSET (unverified)
    glVertexAttribPointer((GLint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_VBOGroundIndicesIndex ); // Bind The Buffer
    glDrawElements( GL_TRIANGLES, m_groundIndicesNb, GL_UNSIGNED_INT, (char*) 0 );
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_Generator::drawBuildings(const GLuint inProgramId)
{
    GLuint location = glGetUniformLocation(inProgramId,"draw_what");
    glUniform1i(location, 2);

    glBindBuffer( GL_ARRAY_BUFFER, m_VBOBuildingsVerticesIndex ); // Bind The Buffer
    // instead of (char*) there is a macro BUFFER_OFFSET (unverified)
    glVertexAttribPointer((GLint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_VBOBuildingsIndicesIndex ); // Bind The Buffer
    glDrawElements( GL_TRIANGLES, m_buildings_indices.size(), GL_UNSIGNED_INT, (char*) 0 );
}
