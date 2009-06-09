#pragma once
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

        void set(GLfloat inX, GLfloat inY, GLfloat inZ);

        void getNorm( GLfloat &outNorm );
        void getNormSquared( GLfloat &outNorm );

        void normalize();

        uSE_GLVector getOpposite() const;

        uSE_GLVector operator+  ( const uSE_GLVector &inVector );
        uSE_GLVector operator-  ( const uSE_GLVector &inVector );
        uSE_GLVector operator*  ( const float &inValue ); 
        GLfloat      operator*  ( const uSE_GLVector &inVector ); // scalar product (dot product)
        uSE_GLVector operator^  ( const uSE_GLVector &inVector ); // vector product (cross product)
        bool         operator== ( const uSE_GLVector &inVector );
};
