#pragma once
#define GL_GLEXT_PROTOTYPES
#include <vector>
#include <GL/gl.h>

class SE_Generator
{
    public:
        SE_Generator();
        virtual ~SE_Generator();

    public: //methods
        unsigned int getVBOVerticesIndex() { return m_VBOVerticesIndex; }
        unsigned int getVBOIndicesIndex () { return m_VBOIndicesIndex; }
        unsigned int getGroundIndicesNb () { return m_groundIndicesNb; }

        void generateGround();
        void subdivideGround();

    private: //members
        unsigned int m_VBOVerticesIndex;
        unsigned int m_VBOIndicesIndex;
        unsigned int m_groundIndicesNb;

        std::vector<GLfloat> m_ground_vertices;
        std::vector<GLuint> m_ground_indices;
};

