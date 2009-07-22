#pragma once
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <vector>
#include "uSE_GLTriangle.h"
#include "uSE_GLVector.h"
#include <string>

class uSE_GLMesh
{
    public:
        uSE_GLMesh();
        virtual ~uSE_GLMesh();

    private://members
        std::vector<GLfloat> m_vertices;
        std::vector<GLuint>  m_indices;

        std::vector<uSE_GLTriangle> m_triangles;

    public:
        unsigned int get_nb_vertices() { return m_vertices.size(); }
        unsigned int get_nb_indices()  { return m_indices.size(); }

        const std::vector<GLfloat> & get_vertices() { return m_vertices; }
        const std::vector<GLuint> & get_indices() { return m_indices; }

        void parseobj( std::string inFilename );
        void parsemd5mesh( const std::string& inFilename );
        void parsemd5anim( const std::string& inFilename );

        // for debug
        void display();
};
