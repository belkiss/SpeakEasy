#include "uSE_GLMatrix.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
uSE_GLMatrix::uSE_GLMatrix()
{
    identity();
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
uSE_GLMatrix::uSE_GLMatrix(
    GLfloat inOne,
    GLfloat inTwo,
    GLfloat inThree,
    GLfloat inFour,
    GLfloat inFive,
    GLfloat inSix,
    GLfloat inSeven,
    GLfloat inEight,
    GLfloat inNine,
    GLfloat inTen,
    GLfloat inEleven,
    GLfloat inTwelve,
    GLfloat inThirteen,
    GLfloat inFourteen,
    GLfloat inFifteen,
    GLfloat inSixteen
    )
{
    m_array[0] = inOne;   m_array[4] = inFive;  m_array[8] = inNine;    m_array[12] = inThirteen;
    m_array[1] = inTwo;   m_array[5] = inSix;   m_array[9] = inTen;     m_array[13] = inFourteen;
    m_array[2] = inThree; m_array[6] = inSeven; m_array[10] = inEleven; m_array[14] = inFifteen;
    m_array[3] = inFour;  m_array[7] = inEight; m_array[11] = inTwelve; m_array[15] = inSixteen;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
uSE_GLMatrix::~uSE_GLMatrix()
{
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void uSE_GLMatrix::identity()
{
    m_array[0] = 1; m_array[4] = 0; m_array[8] =  0; m_array[12] = 0;
    m_array[1] = 0; m_array[5] = 1; m_array[9] =  0; m_array[13] = 0;
    m_array[2] = 0; m_array[6] = 0; m_array[10] = 1; m_array[14] = 0;
    m_array[3] = 0; m_array[7] = 0; m_array[11] = 0; m_array[15] = 1;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
uSE_GLMatrix uSE_GLMatrix::operator*  ( const uSE_GLMatrix &inMatrix )
{
    // TODO
    return inMatrix;
}
