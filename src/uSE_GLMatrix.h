#pragma once
#ifdef _WIN32
#include <windows.h>
#endif
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
        GLfloat m_array[16];

    public: // methods
        void identity();

        const GLfloat* get_array() {return m_array;}

        uSE_GLMatrix operator*  ( const uSE_GLMatrix &inMatrix );
};

