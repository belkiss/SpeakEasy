#pragma once
#define GL_GLEXT_PROTOTYPES

#include <map>

#include "uSE_Quaternion.h"
#include "SE_Generator.h"
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Window.hpp>

class SE_Screen
{
    public:
        SE_Screen();

        void initializeGL();
        void resizeGL    (int width, int height);
        void paintGL     ();

        void keyPressEvent (const sf::Key::Code &inEvent);
        void keyReleaseEvent (const sf::Key::Code &inEvent);

        void mouseMoveEvent (sf::Window * inApp, const int &inX, const int &inY);

    private: // members
        sf::Clock m_clock;
        float     m_elapsed;

        float m_speed;
        float m_rotation_speed;

        uSE_GLVector m_camera_position;
        uSE_Quaternion m_view_quaternion;

        SE_Generator m_generator;

        GLuint m_vbovix;
        GLuint m_vboiix;

        // shader members
        GLuint m_programID;
        GLuint m_vertexShaderID;
        GLuint m_pixelShaderID;

        std::map < sf::Key::Code, bool > m_pressed_keys;

        bool m_cursor_moved_by_us;
        std::pair<int,int> m_mouse_old_pos;

    private: // methods
        void    draw();
        void    draw_axis();

        void    process_keyboard();

};

