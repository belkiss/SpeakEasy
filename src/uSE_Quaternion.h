#pragma once
#include "uSE_GLVector.h"

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
        uSE_Quaternion opposite();
        uSE_Quaternion conjugation();
        uSE_Quaternion reciprocal();

        void getNorm( float &outNorm );

        uSE_Quaternion  operator+  ( const uSE_Quaternion &inQuaternion );
        uSE_Quaternion  operator*  ( const float &inValue);
        uSE_Quaternion  operator*  ( const uSE_Quaternion &inQuaternion );
        bool            operator== ( const uSE_Quaternion &inQuaternion );
};

