#include "uSE_GLMesh.h"


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
uSE_GLMesh::uSE_GLMesh()
{
    unsigned int vertex_1_index = m_vertices.size();
    m_vertices.push_back(0); // x
    m_vertices.push_back(0); // y
    m_vertices.push_back(0); // z

    unsigned int vertex_2_index = m_vertices.size();
    m_vertices.push_back(1); // x
    m_vertices.push_back(0); // y
    m_vertices.push_back(0); // z

    unsigned int vertex_3_index = m_vertices.size();
    m_vertices.push_back(1); // x
    m_vertices.push_back(1); // y
    m_vertices.push_back(0); // z

    m_indices.push_back(0);
    m_indices.push_back(1);
    m_indices.push_back(2);

    m_triangles.push_back(uSE_GLTriangle(vertex_1_index, vertex_2_index, vertex_3_index));

}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
uSE_GLMesh::~uSE_GLMesh()
{
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void uSE_GLMesh::display()
{
    for( unsigned int i = 0; i < m_triangles.size(); i++ )
    {
        m_triangles.at(i).display();
    }
}
