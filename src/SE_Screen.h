#pragma once

#include <QGLWidget>
#include <QMouseEvent>

class SE_Screen: public QGLWidget
{
    Q_OBJECT public:
        SE_Screen(QWidget * inpParent = 0);

    protected:
        void initializeGL();
        void resizeGL(int width, int height);
        void paintGL();
        void mousePressEvent(QMouseEvent * event);
        void mouseMoveEvent(QMouseEvent * event);
        void mouseDoubleClickEvent(QMouseEvent * event);

    private:
        void draw();
        int faceAtPosition(const QPoint & pos);
        GLfloat rotationX;
        GLfloat rotationY;
        GLfloat rotationZ;
        QColor faceColors[4];
        QPoint lastPos;
};

