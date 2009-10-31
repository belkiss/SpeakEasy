#pragma once
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <vector>
#include "uSE_Triangle.h"
#include "uSE_GLVector.h"
#include <string>
#include "uSE_Vertex.h"
#include "uSE_Weight.h"

class uSE_Mesh
{
    public:
        uSE_Mesh();
        virtual ~uSE_Mesh();

    private://members
        std::string               m_shader_name;
        std::vector<uSE_Vertex>   m_vertices;
        std::vector<uSE_Triangle> m_triangles;
        std::vector<uSE_Weight>   m_weights;

    public://methods
        void         add_vertex  ( const uSE_Vertex&   inVertex );
        void         add_triangle( const uSE_Triangle& inTriangle );
        void         add_weight  ( const uSE_Weight&   inWeight );

        std::string  getShaderName ();

        unsigned int getVerticesCount ();
        uSE_Vertex   getVertexAtIndex ( int inIndex );

        unsigned int getTrianglesCount ();
        uSE_Triangle getTriangleAtIndex (int inIndex );

        unsigned int getWeightsCount ();
        uSE_Weight   getWeightAtIndex ( int inIndex );

};
