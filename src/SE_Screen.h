#pragma once
#define GL_GLEXT_PROTOTYPES
#include <QGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>

#include "uSE_Quaternion.h"
#include "SE_Generator.h"

class SE_Screen: public QGLWidget
{
    Q_OBJECT public:
        SE_Screen(QWidget * inpParent = 0);

    protected:
        void initializeGL();
        void resizeGL    (int width, int height);
        void paintGL     ();

        void mousePressEvent      (QMouseEvent * event);
        void mouseMoveEvent       (QMouseEvent * event);
        void mouseDoubleClickEvent(QMouseEvent * event);

        void keyPressEvent        (QKeyEvent * inpEvent);

    private slots:
        void timeOut();

    private: // members
        GLfloat m_rotation_factor;

        QPoint m_oldMousePosition;

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

