#include "uSE_GLVector.h"
#include <cmath>

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
uSE_GLVector::uSE_GLVector()
{
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
uSE_GLVector::uSE_GLVector(GLfloat inX, GLfloat inY, GLfloat inZ):
    m_x(inX),
    m_y(inY),
    m_z(inZ)
{
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
uSE_GLVector::~uSE_GLVector()
{
    m_x = 0;
    m_y = 0;
    m_z = 0;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
void uSE_GLVector::set(GLfloat inX, GLfloat inY, GLfloat inZ)
{
    m_x = inX;
    m_y = inY;
    m_z = inZ;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
void uSE_GLVector::getLength(GLfloat& outLength)
{
    outLength = sqrt( m_x * m_x + m_y * m_y * m_z * m_z );
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
void uSE_GLVector::normalize()
{
    GLfloat vl_length = 0;
    getLength(vl_length);

    m_x = m_x / vl_length;
    m_y = m_y / vl_length;
    m_z = m_z / vl_length;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
GLfloat uSE_GLVector::operator*(const uSE_GLVector& inVector)
{
    return (m_x * inVector.m_x +
            m_y * inVector.m_y +
            m_z * inVector.m_z );
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
uSE_GLVector uSE_GLVector::operator^(const uSE_GLVector& inVector)
{
    uSE_GLVector vl_toreturn;
    vl_toreturn.set( m_y * inVector.m_z - m_z * inVector.m_y,
                     m_z * inVector.m_x - m_x * inVector.m_z,
                     m_x * inVector.m_y - m_y * inVector.m_x );
    return vl_toreturn;
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
bool uSE_GLVector::operator==(const uSE_GLVector& inVector)
{
    return ( m_x == inVector.m_x && m_y == inVector.m_y && m_z == inVector.m_z);
}
