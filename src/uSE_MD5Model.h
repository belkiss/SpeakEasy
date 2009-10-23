#pragma once
#include<Eigen/StdVector>
#include "uSE_Mesh.h"
#include "uSE_Joint.h"
#include "uSE_Animation.h"
#include <map>

class uSE_MD5Model
{
    public:
        uSE_MD5Model();
        virtual ~uSE_MD5Model();

    private://members
        std::vector<uSE_Mesh>  m_meshes;
        std::vector<uSE_Joint> m_joints;

        std::vector<uSE_Animation> m_animations;

    public://methods
        void parsemd5mesh( const std::string& inFilename );
        void parsemd5anim( const std::string& inFilename );

    ////////////////////////////////////////////////////////////////////////////
    // pose dependant elements
    private :
        std::vector<GLfloat> m_pose_vertices;
        std::vector<GLuint>  m_pose_indices;

    public:
        void generateVerticesIndicesPose();

        unsigned int get_nb_meshes       () { return m_meshes.size(); }
        unsigned int get_nb_pose_vertices() { return m_pose_vertices.size(); }
        unsigned int get_nb_pose_indices () { return m_pose_indices.size(); }

        const std::vector<GLfloat> & get_pose_vertices() { return m_pose_vertices; }
        const std::vector<GLuint>  & get_pose_indices () { return m_pose_indices; }
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    // animation elements
    private :
        std::map<int, std::vector<GLfloat> > m_frames_vertices;
        std::map<int, std::vector<GLuint>  > m_frames_indices;

    public:
        int  getNbFramesFromAnim( const unsigned int inAnim ) { return m_animations.at(inAnim).getNbFrames(); }
        void generateVerticesIndicesFromAnimAtFrame( const unsigned int inAnim, const unsigned int inFrame );
};

