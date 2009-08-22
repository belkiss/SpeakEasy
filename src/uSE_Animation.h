#pragma once

#include <string>
#include <vector>

#include "uSE_AnimJoint.h"
#include "uSE_BoundBox.h"
#include "uSE_GLVector.h"
#include "uSE_Quaternion.h"
#include "uSE_Joint.h"

class uSE_Animation
{
    public:
        uSE_Animation();
        uSE_Animation( const std::string & inAnimationName );
        virtual ~uSE_Animation();

    private://members
        std::string  m_animation_name;
        unsigned int m_nb_frames;
        unsigned int m_framerate_fps;
        unsigned int m_nb_animated_components;

        std::vector< uSE_AnimJoint >                           m_animjoints;
        std::vector< uSE_BoundBox >                            m_bound_boxes;
        std::vector< uSE_Joint >                               m_base_frame_joints;
        std::vector< std::vector< float > >                    m_frames_components;

    public://methods
        void addAnimJoint( const uSE_AnimJoint & inAnimJoint ) { m_animjoints.push_back(inAnimJoint); }
        void addBoundBox ( const uSE_BoundBox & inBoundBox ) { m_bound_boxes.push_back(inBoundBox); }
        void addBaseFrameJoint( const uSE_Joint & inBaseFrameJoint ) { m_base_frame_joints.push_back(inBaseFrameJoint); }
        void addFrameData ( const std::vector<float> & inFrameData ) { m_frames_components.push_back(inFrameData); }

        unsigned int getNbFrames() { return m_nb_frames; }
        unsigned int getFrameRateFPS() { return m_framerate_fps; }
        unsigned int getNbAnimatedComponents() { return m_nb_animated_components; }
        unsigned int getAnimJointsNb() { return m_animjoints.size(); }

        uSE_AnimJoint getAnimJointAtIndex ( int inIndex ) { return m_animjoints.at(inIndex); }
        uSE_BoundBox  getBoundBoxAtIndex (int inIndex ) { return m_bound_boxes.at(inIndex); }
        uSE_Joint     getBaseFrameJointAtIndex ( int inIndex ) { return m_base_frame_joints.at(inIndex); }
        float         getFrameComponentFromFrameAtIndex (int inFrame, int inIndex) { return m_frames_components.at(inFrame).at(inIndex); }

        void setNbAnimatedComponents ( const unsigned int inNbAnimatedComponents ) { m_nb_animated_components = inNbAnimatedComponents; }
        void setNbFrames             ( const unsigned int inNbFrames ) { m_nb_frames = inNbFrames; }
        void setFrameRateFPS         ( const unsigned int inFrameRate ) { m_framerate_fps = inFrameRate; }
};

