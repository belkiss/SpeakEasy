#pragma once
#ifdef _WIN32
#include <windows.h>
#else
#define GL_GLEXT_PROTOTYPES
#endif
#include <vector>
#include <GL/gl.h>

class SE_Generator
{
    public:
        SE_Generator();
        virtual ~SE_Generator();

    public: //methods
        // ground
        void generateGround();
        void subdivideGround();

        void drawGround(const GLuint inProgramId);

        // buildings
        void generateBuildings();

        void drawBuildings(const GLuint inProgramId);

    private: //members
        // ground
        unsigned int m_VBOGroundVerticesIndex;
        unsigned int m_VBOGroundIndicesIndex;

        unsigned int m_groundSideElementsNb;
        unsigned int m_groundSideSize;
        unsigned int m_groundIndicesNb;

        std::vector<GLfloat> m_ground_vertices;
        std::vector<GLuint>  m_ground_indices;

        // buildings
        unsigned int m_VBOBuildingsVerticesIndex;
        unsigned int m_VBOBuildingsIndicesIndex;

        std::vector<GLfloat> m_buildings_vertices;
        std::vector<GLuint>  m_buildings_indices;
};

