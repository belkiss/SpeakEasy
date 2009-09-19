#pragma once
#include "uSE_GLVector.h"
#include <Eigen/Core>
using namespace Eigen;

class uSE_Weight
{
    public:
        uSE_Weight();
        uSE_Weight( const int& inDependingJoint, const float& inBiasFactor, const Vector3f& inPosition );
        virtual ~uSE_Weight();

    private: //members
        int          m_depending_joint;
        float        m_bias_factor;
        Vector3f     m_position;

    public: //methods
        int          getDependingJoint() { return m_depending_joint; }
        float        getBiasFactor() { return m_bias_factor; }
        Vector3f     getPosition() { return m_position; }
};
