#pragma once
#include <string>
#include "uSE_GLVector.h"

#include <Eigen/Geometry>
using namespace Eigen;

class uSE_Joint
{
    public:
        uSE_Joint();
        uSE_Joint(  const std::string & inName,
                    const int         & inParentIndex,
                    const Vector3f    & inPosition,
                    const Quaternionf & inOrientation);

        virtual ~uSE_Joint();

    private://members
        std::string    m_name;
        int            m_parent_index;
        Vector3f       m_position;
        Quaternionf    m_orientation;

    public://methods
        void setName( const std::string & inName ) { m_name = inName; }
        void setParentIndex ( const int inParentIndex ) { m_parent_index = inParentIndex; }
        void setPosition ( const Vector3f & inPosition) { m_position = inPosition; }
        void setOrientation ( const Quaternionf & inOrientation ) { m_orientation = inOrientation; }

        std::string    getName() { return m_name; }
        int            getParentIndex() { return m_parent_index; }
        Vector3f       getPosition() { return m_position; }
        Quaternionf    getOrientation() { return m_orientation; }
};
