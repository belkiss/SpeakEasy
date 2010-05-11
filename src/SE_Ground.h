#pragma once

#include <cmath>
#include <vector>
#include <cstdlib>

inline float random(float _x)
{
    float t=(float(rand()%23536)/23536.0f);
    return t*_x;
}

inline float random2(float _x)
{
    float t=(float(rand()%23536)/23536.0f);
    return 2.0f*(t-0.5f)*_x;
}

class SE_Ground
{
    public:
        SE_Ground(unsigned int _p2, float _x1y1, float _x2y1, float _x1y2, float _x2y2 );
        virtual ~SE_Ground();

        void initialize(float _x1y1, float _x2y1, float _x1y2, float _x2y2);
        void computeheights(unsigned int depth, int _x1, int _y1, int _x2, int _y2, float _attenuation);

        std::vector< std::vector<float> > get_z(){return m_z;}

    private:
        unsigned int m_p2;
        unsigned int m_width;
        unsigned int m_height;

        std::vector< std::vector<float> > m_z;
};
