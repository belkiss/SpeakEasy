#pragma once
#include <string>
#include "uSE_GLVector.h"
#include "uSE_Quaternion.h"

class uSE_Joint
{
    public:
        uSE_Joint();
        uSE_Joint( const std::string & inName, const int inParentIndex, const uSE_GLVector & inPosition, const uSE_Quaternion & inOrientation);
        virtual ~uSE_Joint();

    private://members
        std::string    m_name;
        int            m_parent_index;
        uSE_GLVector   m_position;
        uSE_Quaternion m_orientation;

    public://methods
        void setName( const std::string & inName ) { m_name = inName; }
        void setParentIndex ( const int inParentIndex ) { m_parent_index = inParentIndex; }
        void setPosition ( const uSE_GLVector & inPosition) { m_position = inPosition; }
        void setOrientation ( const uSE_Quaternion & inOrientation ) { m_orientation = inOrientation; }

        std::string    getName() { return m_name; }
        int            getParentIndex() { return m_parent_index; }
        uSE_GLVector   getPosition() { return m_position; }
        uSE_Quaternion getOrientation() { return m_orientation; }
};
