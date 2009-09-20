#pragma once
#ifndef _WIN32
#define GL_GLEXT_PROTOTYPES
#endif

#include <map>

#include <Eigen/Geometry>
#include "SE_Generator.h"
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Window.hpp>
#include "uSE_MD5Model.h"

class SE_Screen
{
    public:
        SE_Screen();
        virtual ~SE_Screen();

        void initializeGL();
        void resizeGL    (int width, int height);
        void paintGL     ();

        void keyPressEvent (const sf::Key::Code &inEvent);
        void keyReleaseEvent (const sf::Key::Code &inEvent);

        void mouseMoveEvent (sf::Window * inApp, const int &inX, const int &inY);

    private: // members
        sf::Clock m_clock;
        float     m_elapsed;
        float     m_anim_elapsed;

        float m_speed;
        float m_rotation_speed;

        uSE_GLVector   m_camera_position;

        Eigen::Quaternionf m_camera_rotation;
        Eigen::Quaternionf m_view_quaternion;

        uSE_GLVector       m_character_position;
        Eigen::Quaternionf m_character_rotation;

        SE_Generator m_generator;

        GLuint m_vbonbindices;
        GLuint m_vbovix;
        GLuint m_vboiix;

        // shader members
        GLuint m_programID;

        GLuint m_vertexShaderID;
        GLuint m_geometryShaderID;
        GLuint m_pixelShaderID;

        std::map < sf::Key::Code, bool > m_pressed_keys;

        bool m_cursor_moved_by_us;
        std::pair<int,int> m_mouse_old_pos;

        uSE_MD5Model m_character_model;
        int          m_frame_walk;
        int          m_frame_stand;

    private: // methods
        void    draw();
        void    draw_character();

        void    process_keyboard();

        void    genCharAndAnimate();

};

