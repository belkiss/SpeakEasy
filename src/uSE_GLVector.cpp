#include "uSE_GLVector.h"
#include <cmath>

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
uSE_GLVector::uSE_GLVector():
    m_x(0),
    m_y(0),
    m_z(0)
{
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
uSE_GLVector::uSE_GLVector(GLfloat inX, GLfloat inY, GLfloat inZ):
    m_x(inX),
    m_y(inY),
    m_z(inZ)
{
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
uSE_GLVector::~uSE_GLVector()
{
    m_x = 0;
    m_y = 0;
    m_z = 0;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void uSE_GLVector::set(GLfloat inX, GLfloat inY, GLfloat inZ)
{
    m_x = inX;
    m_y = inY;
    m_z = inZ;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void uSE_GLVector::getNormSquared(GLfloat& outNorm)
{
    outNorm = m_x * m_x + m_y * m_y + m_z * m_z;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void uSE_GLVector::getNorm(GLfloat& outNorm)
{
    float tmp = 0.f;
    getNormSquared(tmp);
    outNorm = sqrt( tmp );
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void uSE_GLVector::normalize()
{
    GLfloat vl_length = 0;
    getNorm(vl_length);

    m_x = m_x / vl_length;
    m_y = m_y / vl_length;
    m_z = m_z / vl_length;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
uSE_GLVector uSE_GLVector::getOpposite() const
{
    return uSE_GLVector(-m_x,-m_y,-m_z);
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
uSE_GLVector uSE_GLVector::operator+( const uSE_GLVector& inVector)
{
    return uSE_GLVector( m_x + inVector.m_x,
                         m_y + inVector.m_y,
                         m_z + inVector.m_z );
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
uSE_GLVector uSE_GLVector::operator-( const uSE_GLVector& inVector)
{
    return (*this + inVector.getOpposite());
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
uSE_GLVector uSE_GLVector::operator*(const float &inValue )
{
    return uSE_GLVector( m_x * inValue,
                         m_y * inValue,
                         m_z * inValue );
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
GLfloat uSE_GLVector::operator*(const uSE_GLVector& inVector)
{
    return (m_x * inVector.m_x +
            m_y * inVector.m_y +
            m_z * inVector.m_z );
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
uSE_GLVector uSE_GLVector::operator^(const uSE_GLVector& inVector)
{
    uSE_GLVector vl_toreturn;
    vl_toreturn.set( m_y * inVector.m_z - m_z * inVector.m_y,
                     m_z * inVector.m_x - m_x * inVector.m_z,
                     m_x * inVector.m_y - m_y * inVector.m_x );
    return vl_toreturn;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
bool uSE_GLVector::operator==(const uSE_GLVector& inVector)
{
    return ( m_x == inVector.m_x && m_y == inVector.m_y && m_z == inVector.m_z);
}
