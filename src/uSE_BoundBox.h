#pragma once
#include <Eigen/Core>

class uSE_BoundBox
{
    public:
        uSE_BoundBox();
        uSE_BoundBox( const Eigen::Vector3f& inMin,
                      const Eigen::Vector3f& inMax );

        virtual ~uSE_BoundBox();

        EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    private://members
        Eigen::Vector3f m_min;
        Eigen::Vector3f m_max;

    public://methods
        Eigen::Vector3f getMin();
        Eigen::Vector3f getMax();
};
