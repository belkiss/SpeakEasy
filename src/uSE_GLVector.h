#pragma once
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include "uSE_GLMatrix.h"

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
        GLfloat getX() const {return m_x;}
        GLfloat getY() const {return m_y;}
        GLfloat getZ() const {return m_z;}

        void setX( const GLfloat inX ) { m_x = inX; }
        void setY( const GLfloat inY ) { m_y = inY; }
        void setZ( const GLfloat inZ ) { m_z = inZ; }

        void set(GLfloat inX, GLfloat inY, GLfloat inZ);

        void getNormSquared( GLfloat &outNorm );
        void getNorm( GLfloat &outNorm );

        void normalize();

        uSE_GLVector getOpposite() const;

        uSE_GLVector operator+  ( const uSE_GLVector &inVector );
        uSE_GLVector operator-  ( const uSE_GLVector &inVector );
        uSE_GLVector operator*  ( const float &inValue ); 
        GLfloat      operator*  ( const uSE_GLVector &inVector ); // scalar product (dot product)
        uSE_GLVector operator^  ( const uSE_GLVector &inVector ); // vector product (cross product)
        bool         operator== ( const uSE_GLVector &inVector );
};
