#pragma once
#include "uSE_GLVector.h"
#include "uSE_GLMatrix.h"

class uSE_Quaternion
{
    public:
        uSE_Quaternion();
        uSE_Quaternion( float inReal, uSE_GLVector inVector );
        virtual ~uSE_Quaternion();

    private: //members
        float m_real;
        uSE_GLVector m_vector;

    public: //methods
        void from_axis(uSE_GLVector inAxis, float inDegrees);

        float get_real() const { return m_real;}
        const uSE_GLVector & get_vector() const { return m_vector;}

        uSE_GLMatrix get_matrix();

        uSE_Quaternion opposite();
        uSE_Quaternion conjugation();
        uSE_Quaternion reciprocal();

        void getNorm( float &outNorm );

        void normalize();

        uSE_Quaternion  operator+  ( const uSE_Quaternion &inQuaternion );
        uSE_Quaternion  operator*  ( const float &inValue);
        uSE_Quaternion  operator*  ( const uSE_Quaternion &inQuaternion );
        bool            operator== ( const uSE_Quaternion &inQuaternion );
};

