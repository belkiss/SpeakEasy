#pragma once
#include "uSE_GLVector.h"
#include <Eigen/Core>

class uSE_Quaternion
{
    public:
        uSE_Quaternion         ();
        uSE_Quaternion         ( float inReal, uSE_GLVector inVector );
        virtual ~uSE_Quaternion();

    private: //members
        float        m_real;
        uSE_GLVector m_vector;

    public: //methods
        void         set_real( const float inReal );
        void         set_vector( const uSE_GLVector inVector ) { m_vector = inVector; }

        void         from_axis(uSE_GLVector inAxis, float inDegrees);
        uSE_GLVector to_axis();

        float        get_real() const { return m_real;}
        const uSE_GLVector & get_vector() const { return m_vector;}

        void         get_matrix( Eigen::Matrix4f & outMat4f );

        uSE_Quaternion opposite();
        uSE_Quaternion conjugation();
        uSE_Quaternion reciprocal();

        void getNormSquared( float &outNorm );
        void getNorm( float &outNorm );

        void computeReal();

        void normalize();

        uSE_Quaternion  operator+  ( const uSE_Quaternion &inQuaternion );
        uSE_Quaternion  operator*  ( const float &inValue);
        uSE_Quaternion  operator*  ( const uSE_Quaternion &inQuaternion );
        bool            operator== ( const uSE_Quaternion &inQuaternion );
};

