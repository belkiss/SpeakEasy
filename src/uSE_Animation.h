#pragma once

#include <Eigen/StdVector>
#include "uSE_AnimJoint.h"
#include "uSE_BoundBox.h"
#include "uSE_Joint.h"

class uSE_Animation
{
    public:
        uSE_Animation();
        uSE_Animation( const std::string& inAnimationName );

        virtual ~uSE_Animation();

    private://members
        std::string                          m_animation_name;
        unsigned int                         m_nb_frames;
        unsigned int                         m_framerate_fps;
        unsigned int                         m_nb_animated_components;

        std::vector< uSE_AnimJoint >         m_animjoints;
        std::vector< uSE_BoundBox >          m_bound_boxes;
        std::vector< uSE_Joint >             m_base_frame_joints;
        std::vector< std::vector< float > >  m_frames_components;

    public://methods
        void          addAnimJoint     ( const uSE_AnimJoint&      inAnimJoint );
        void          addBoundBox      ( const uSE_BoundBox&       inBoundBox );
        void          addBaseFrameJoint( const uSE_Joint&          inBaseFrameJoint );
        void          addFrameData     ( const std::vector<float>& inFrameData );

        unsigned int  getNbFrames();
        unsigned int  getFrameRateFPS();
        unsigned int  getNbAnimatedComponents();
        unsigned int  getAnimJointsNb();

        uSE_AnimJoint getAnimJointAtIndex               ( int inIndex );
        uSE_BoundBox  getBoundBoxAtIndex                ( int inIndex );
        uSE_Joint     getBaseFrameJointAtIndex          ( int inIndex );
        float         getFrameComponentFromFrameAtIndex ( int inFrame, int inIndex);

        void          setNbAnimatedComponents ( const unsigned int inNbAnimatedComponents );
        void          setNbFrames             ( const unsigned int inNbFrames );
        void          setFrameRateFPS         ( const unsigned int inFrameRate );
};

