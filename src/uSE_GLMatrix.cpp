#include "uSE_GLMatrix.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
uSE_GLMatrix::uSE_GLMatrix()
{
    identity();
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
uSE_GLMatrix::uSE_GLMatrix( GLfloat inOne,      GLfloat inTwo,      GLfloat inThree,    GLfloat inFour,
                            GLfloat inFive,     GLfloat inSix,      GLfloat inSeven,    GLfloat inEight,
                            GLfloat inNine,     GLfloat inTen,      GLfloat inEleven,   GLfloat inTwelve,
                            GLfloat inThirteen, GLfloat inFourteen, GLfloat inFifteen,  GLfloat inSixteen):
    m_One(inOne),
    m_Two(inTwo),
    m_Three(inThree),
    m_Four(inFour),
    m_Five(inFive),
    m_Six(inSix),
    m_Seven(inSeven),
    m_Eight(inEight),
    m_Nine(inNine),
    m_Ten(inTen),
    m_Eleven(inEleven),
    m_Twelve(inTwelve),
    m_Thirteen(inThirteen),
    m_Fourteen(inFourteen),
    m_Fifteen(inFifteen),
    m_Sixteen(inSixteen)
{
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
uSE_GLMatrix::~uSE_GLMatrix()
{
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void uSE_GLMatrix::identity()
{
    m_One      = 1; m_Two      = 0; m_Three   = 0; m_Four    = 0;
    m_Five     = 0; m_Six      = 1; m_Seven   = 0; m_Eight   = 0;
    m_Nine     = 0; m_Ten      = 0; m_Eleven  = 1; m_Twelve  = 0;
    m_Thirteen = 0; m_Fourteen = 0; m_Fifteen = 0; m_Sixteen = 1;
}

