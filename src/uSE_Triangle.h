#pragma once

class uSE_Triangle
{
    public:
        uSE_Triangle();
        uSE_Triangle( const int inFirstPositionIndex, const int inSecondPositionIndex, const int inThirdPositionIndex);
        virtual ~uSE_Triangle();

    private: //members
        int m_first_position_index;
        int m_second_position_index;
        int m_third_position_index;

    public: //methods
        int getFirstPositionIndex() { return m_first_position_index; }
        int getSecondPositionIndex() { return m_second_position_index; }
        int getThirdPositionIndex() { return m_third_position_index; }
};
