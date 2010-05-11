#include "SE_Ground.h"

const float attenuation = 50;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
SE_Ground::SE_Ground( unsigned int _p2, float _x1y1, float _x2y1, float _x1y2, float _x2y2 ) : p2(_p2)
{
    height = width = pow(2.f,float(p2));
    initialize(_x1y1, _x2y1, _x1y2, _x2y2);
    computeheights(p2,0, 0, width, height, attenuation);
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
    for (unsigned int i = 0; i <= width; i++)
    {
        std::vector<float> tmp(height, -1.f);
        z.push_back(tmp);
    }

    z[0][0] = _x1y1;
    z[0][height] = _x2y1;
    z[width][0] = _x1y2;
    z[width][height] = _x2y2;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_Ground::computeheights( unsigned int depth, int _x1, int _y1, int _x2, int _y2, float _attenuation )
{
    if (depth > 0)
    {
        float opp = random2(_attenuation);
        if (z[(_x1+_x2)/2][_y1] == -1)
            z[(_x1+_x2)/2][_y1] = (z[_x1][_y1]+z[_x2][_y1])/2.f + opp;

        opp = random2(_attenuation);
        if (z[_x1][(_y1+_y2)/2] == -1)
            z[_x1][(_y1+_y2)/2] = (z[_x1][_y1] + z[_x1][_y2])/2.f + opp;

        opp = random2(_attenuation);
        if (z[(_x1+_x2)/2][_y2] == -1)
            z[(_x1+_x2)/2][_y2]  = (z[_x1][_y2] + z[_x2][_y2])/2.f + opp;

        opp = random2(_attenuation);
        if (z[_x2][(_y1+_y2)/2] == -1)
            z[_x2][(_y1+_y2)/2] = (z[_x2][_y1] + z[_x2][_y2])/2.f + opp;

        opp = random2(_attenuation);
        if (z[(_x1+_x2)/2][(_y1+_y2)/2] == -1)
        {
            z[(_x1+_x2)/2][(_y1+_y2)/2] = (z[_x1][_y1] + z[_x2][_y1] + z[_x1][_y2] + z[_x2][_y2])/4.f + opp;
        }

        computeheights(depth - 1, _x1, _y1, (_x1+_x2)/2,(_y1+_y2)/2, _attenuation/2);
        computeheights(depth - 1, (_x1+_x2)/2, _y1, _x2, (_y1+_y2)/2 ,_attenuation/2);
        computeheights(depth - 1, _x1, (_y1+_y2)/2, (_x1+_x2)/2,_y2 ,_attenuation/2);
        computeheights(depth - 1, (_x1+_x2)/2, (_y1+_y2)/2, _x2, _y2,_attenuation/2);
    }
}
