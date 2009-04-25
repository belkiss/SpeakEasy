#pragma once
#include <GL/gl.h>

class uSE_GLMatrix
{
    public:
        uSE_GLMatrix();
        uSE_GLMatrix(   GLfloat inOne,  GLfloat inFive,  GLfloat inNine,   GLfloat inThirteen,
                        GLfloat inTwo,  GLfloat inSix,   GLfloat inTen,    GLfloat inFourteen,
                        GLfloat inThree,GLfloat inSeven, GLfloat inEleven, GLfloat inFifteen,
                        GLfloat inFour, GLfloat inEight, GLfloat inTwelve, GLfloat inSixteen);


        virtual ~uSE_GLMatrix();

    private: // members
        GLfloat m_One,      m_Two,      m_Three,   m_Four,
                m_Five,     m_Six,      m_Seven,   m_Eight,
                m_Nine,     m_Ten,      m_Eleven,  m_Twelve,
                m_Thirteen, m_Fourteen, m_Fifteen, m_Sixteen;

    public: // methods
        void identity();

        uSE_GLMatrix operator*  ( const uSE_GLMatrix &inMatrix );
};

