#pragma once

class uSE_Vertex
{
    public:
        uSE_Vertex();
        uSE_Vertex( const float inS, const float inT, const int inStartWeightIndex, const int inCountWeight);
        virtual ~uSE_Vertex();

    private://members
        // texture coordinates
        float m_s;
        float m_t;
        int   m_startweight_index;
        int   m_countweight;

    public://methods
        float getSCoord() { return m_s; }
        float getTCoord() { return m_t; }

        int   getStartWeightIndex() { return m_startweight_index; }
        int   getCountWeight() { return m_countweight; }
};
