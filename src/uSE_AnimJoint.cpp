#include "uSE_AnimJoint.h"


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
uSE_AnimJoint::uSE_AnimJoint():
    m_name(""),
    m_parent_index(0),
    m_flags(0),
    m_data_start_index(0)
{
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
uSE_AnimJoint::uSE_AnimJoint( const std::string& inName,
                              const int          inParentIndex,
                              const int          inFlags,
                              const int          inDataStartIndex ):
    m_name(inName),
    m_parent_index(inParentIndex),
    m_flags(inFlags),
    m_data_start_index(inDataStartIndex)
{
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
uSE_AnimJoint::~uSE_AnimJoint()
{
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
std::string uSE_AnimJoint::getName()
{
    return m_name;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
int uSE_AnimJoint::getParentIndex()
{
    return m_parent_index;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
int uSE_AnimJoint::getFlags()
{
    return m_flags;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
int uSE_AnimJoint::getDataStartIndex()
{
    return m_data_start_index;
}
