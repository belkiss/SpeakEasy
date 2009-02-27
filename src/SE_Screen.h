#pragma once

#include <QGLWidget>
#include <QMouseEvent>

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

    private slots:
        void timeOut();

    private: // members
        GLfloat m_rotation_factor;

    private: // methods
        void    draw();
        void    draw_axis();

};

