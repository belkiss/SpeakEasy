#include "SE_Ground.h"

const float attenuation = 50;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
SE_Ground::SE_Ground( unsigned int _p2, float _x1y1, float _x2y1, float _x1y2, float _x2y2 ) :
    m_p2(_p2)
{
    m_height = m_width = pow(2.f,float( m_p2));
    initialize(_x1y1, _x2y1, _x1y2, _x2y2);
    computeheights(m_p2, 0, 0, m_width, m_height, attenuation);
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
SE_Ground::~SE_Ground()
{
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_Ground::initialize(float _x1y1, float _x2y1, float _x1y2, float _x2y2)
{
    for (unsigned int i = 0; i <= m_width; i++)
    {
        std::vector<float> tmp( m_height, -1.f);
        m_z.push_back(tmp);
    }

    m_z[0][0] = _x1y1;
    m_z[0][m_height] = _x2y1;
    m_z[m_width][0] = _x1y2;
    m_z[m_width][m_height] = _x2y2;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_Ground::computeheights( unsigned int depth, int _x1, int _y1, int _x2, int _y2, float _attenuation )
{
    if (depth > 0)
    {
        float opp = random2(_attenuation);
        if ( m_z[(_x1+_x2)/2][_y1] == -1)
            m_z[(_x1+_x2)/2][_y1] = ( m_z[_x1][_y1]+m_z[_x2][_y1])/2.f + opp;

        opp = random2(_attenuation);
        if ( m_z[_x1][(_y1+_y2)/2] == -1)
            m_z[_x1][(_y1+_y2)/2] = ( m_z[_x1][_y1] + m_z[_x1][_y2])/2.f + opp;

        opp = random2(_attenuation);
        if ( m_z[(_x1+_x2)/2][_y2] == -1)
            m_z[(_x1+_x2)/2][_y2]  = ( m_z[_x1][_y2] + m_z[_x2][_y2])/2.f + opp;

        opp = random2(_attenuation);
        if ( m_z[_x2][(_y1+_y2)/2] == -1)
            m_z[_x2][(_y1+_y2)/2] = ( m_z[_x2][_y1] + m_z[_x2][_y2])/2.f + opp;

        opp = random2(_attenuation);
        if ( m_z[(_x1+_x2)/2][(_y1+_y2)/2] == -1)
        {
            m_z[(_x1+_x2)/2][(_y1+_y2)/2] = ( m_z[_x1][_y1] + m_z[_x2][_y1] + m_z[_x1][_y2] + m_z[_x2][_y2])/4.f + opp;
        }

        computeheights(depth - 1, _x1, _y1, (_x1+_x2)/2,(_y1+_y2)/2, _attenuation/2);
        computeheights(depth - 1, (_x1+_x2)/2, _y1, _x2, (_y1+_y2)/2 ,_attenuation/2);
        computeheights(depth - 1, _x1, (_y1+_y2)/2, (_x1+_x2)/2,_y2 ,_attenuation/2);
        computeheights(depth - 1, (_x1+_x2)/2, (_y1+_y2)/2, _x2, _y2,_attenuation/2);
    }
}
