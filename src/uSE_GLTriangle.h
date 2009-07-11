#pragma once

class uSE_GLTriangle
{
    public:
        uSE_GLTriangle();
        uSE_GLTriangle( unsigned int inPositionIndex_1, unsigned int inPositionIndex_2, unsigned int inPositionIndex_3);
        virtual ~uSE_GLTriangle();

    private: //members
        unsigned int m_position_index_1;
        unsigned int m_position_index_2;
        unsigned int m_position_index_3;

        unsigned int m_normal_index_1;
        unsigned int m_normal_index_2;
        unsigned int m_normal_index_3;


    public: //methods
        void display();
};
