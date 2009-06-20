#pragma once
#define GL_GLEXT_PROTOTYPES

#include "uSE_Quaternion.h"
#include "SE_Generator.h"
#include <SFML/Window/Event.hpp>

class SE_Screen
{
    public:
        SE_Screen();

        void initializeGL();
        void resizeGL    (int width, int height);
        void paintGL     ();

        void keyPressEvent (const sf::Key::Code &inEvent);

    private: // members
        GLfloat m_rotation_factor;

        GLfloat m_angle;

        uSE_GLVector m_camera_position;
        uSE_Quaternion m_view_quaternion;

        SE_Generator m_generator;

        GLuint m_vbovix;
        GLuint m_vboiix;

        // shader members
        GLuint m_programID;
        GLuint m_vertexShaderID;
        GLuint m_pixelShaderID;

    private: // methods
        void    draw();
        void    draw_axis();

};

