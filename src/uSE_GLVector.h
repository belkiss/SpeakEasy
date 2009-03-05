#pragma once
#include <GL/gl.h>

class uSE_GLVector
{
    public:
        uSE_GLVector();
        uSE_GLVector(GLfloat inX, GLfloat inY, GLfloat inZ);
        virtual ~uSE_GLVector();

    private: // members
        GLfloat m_x,
                m_y,
                m_z;

    public: //methods
        const GLfloat getX(){return m_x;}
        const GLfloat getY(){return m_y;}
        const GLfloat getZ(){return m_z;}

        void set(GLfloat inX, GLfloat inY, GLfloat inZ);

        void getLength( GLfloat &outLength );

        void normalize();

        GLfloat      operator*  ( const uSE_GLVector &inVector ); // scalar product (dot product)
        uSE_GLVector operator^  ( const uSE_GLVector &inVector ); // vector product (cross product)
        bool         operator== ( const uSE_GLVector &inVector );
};
