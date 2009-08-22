#pragma once
#include "uSE_GLVector.h"

class uSE_Weight
{
    public:
        uSE_Weight();
        uSE_Weight( const int inDependingJoint, const float inBiasFactor, const uSE_GLVector inPosition );
        virtual ~uSE_Weight();

    private: //members
        int          m_depending_joint;
        float        m_bias_factor;
        uSE_GLVector m_position;

    public: //methods
        int          getDependingJoint() { return m_depending_joint; }
        float        getBiasFactor() { return m_bias_factor; }
        uSE_GLVector getPosition() { return m_position; }
};
