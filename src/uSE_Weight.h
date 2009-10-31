#pragma once
#include <Eigen/Core>

class uSE_Weight
{
    public:
        uSE_Weight();
        uSE_Weight( const int&             inDependingJoint,
                    const float&           inBiasFactor,
                    const Eigen::Vector3f& inPosition );

        virtual ~uSE_Weight();

        EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    private: //members
        int             m_depending_joint;
        float           m_bias_factor;
        Eigen::Vector3f m_position;

    public: //methods
        int             getDependingJoint();
        float           getBiasFactor();
        Eigen::Vector3f getPosition();
};
