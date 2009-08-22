#pragma once
#include <string>

class uSE_AnimJoint
{
    public:
        uSE_AnimJoint();
        uSE_AnimJoint( const std::string & inName, const int inParentIndex, const int inFlags, const int inDataStartIndex );
        virtual ~uSE_AnimJoint();

    private://members
        std::string m_name;
        int         m_parent_index;
        int         m_flags;
        int         m_data_start_index;

    public://methods
        std::string getName() { return m_name; }
        int         getParentIndex() { return m_parent_index; }
        int         getFlags() { return m_flags; }
        int         getDataStartIndex() { return m_data_start_index; }
};
