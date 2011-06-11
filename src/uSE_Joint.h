#pragma once

#include <Eigen/Geometry>

class uSE_Joint
{
    public:
        uSE_Joint();
        uSE_Joint( const std::string&        inName,
                   const int&                inParentIndex,
                   const Eigen::Vector3f&    inPosition,
                   const Eigen::Quaternionf& inOrientation);

        virtual ~uSE_Joint();

        EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    private://members
        std::string        m_name;
        int                m_parent_index;
        Eigen::Vector3f    m_position;
        Eigen::Quaternionf m_orientation;

    public://methods
        void               setName       ( const std::string&        inName );
        void               setParentIndex( const int                 inParentIndex );
        void               setPosition   ( const Eigen::Vector3f&    inPosition );
        void               setOrientation( const Eigen::Quaternionf& inOrientation );

        std::string        getName       ();
        int                getParentIndex();
        Eigen::Vector3f    getPosition   ();
        Eigen::Quaternionf getOrientation();
};
