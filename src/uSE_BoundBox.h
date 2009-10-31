#pragma once
#include "uSE_GLVector.h"

class uSE_BoundBox
{
    public:
        uSE_BoundBox();
        uSE_BoundBox( const uSE_GLVector & inMin, const uSE_GLVector & inMax );
        virtual ~uSE_BoundBox();

    private://members
        uSE_GLVector m_min;
        uSE_GLVector m_max;

    public://methods
        uSE_GLVector getMin();
        uSE_GLVector getMax();
};
