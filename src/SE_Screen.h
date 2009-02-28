#pragma once

#include <QGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>

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

        GLfloat m_position_x,
                m_position_y,
                m_position_z;

        SE_Generator m_generator;

    private: // methods
        void    draw();
        void    draw_axis();

};

