#pragma once

class SE_Generator
{
    public:
        SE_Generator();
        virtual ~SE_Generator();

    public: //methods
        const unsigned int getVBOVerticesIndex() { return m_VBOVerticesIndex; }
        const unsigned int getVBOIndicesIndex () { return m_VBOIndicesIndex; }

        void generateGround();

    private: //members
        unsigned int m_VBOVerticesIndex;
        unsigned int m_VBOIndicesIndex;
};

