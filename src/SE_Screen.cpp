#include "SE_Screen.h"
#include <QTimer>

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
SE_Screen::SE_Screen(QWidget * inpParent):
    QGLWidget(inpParent),
    m_rotation_factor(0.f)
{
    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeOut()));
    timer->start(20);
}


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
void SE_Screen::initializeGL()
{
    qglClearColor(Qt::black);

    // will color all with one color instead of gradient
    glShadeModel(GL_FLAT);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
void SE_Screen::resizeGL(int inWidth, int inHeight)
{
    glViewport(0, 0, inWidth, inHeight);

    glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluLookAt(0.5,0.5,0.5, 0,0,0, 0,0,1);

    glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
}


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
void SE_Screen::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw_axis();
    draw();
}


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
void SE_Screen::draw_axis()
{
    static const GLint vl_orig[3] = { 0, 0, 0};
    static const GLint vl_x   [3] = { 1, 0, 0};
    static const GLint vl_y   [3] = { 0, 1, 0};
    static const GLint vl_z   [3] = { 0, 0, 1};

    glMatrixMode(GL_MODELVIEW);
        glBegin(GL_LINES);
            qglColor(Qt::red);
            glVertex3i(vl_orig[0], vl_orig[1], vl_orig[2]);
            glVertex3i(vl_x   [0], vl_x   [1], vl_x[2]);

            qglColor(Qt::green);
            glVertex3i(vl_orig[0], vl_orig[1], vl_orig[2]);
            glVertex3i(vl_y   [0], vl_y   [1], vl_y[2]);

            qglColor(Qt::white);
            glVertex3i(vl_orig[0], vl_orig[1], vl_orig[2]);
            glVertex3i(vl_z   [0], vl_z   [1], vl_z[2]);
        glEnd();
}


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
void SE_Screen::draw()
{
    glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef(m_rotation_factor*180/3.14159265, 0.f, 0.f, 1.f);
}


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
void SE_Screen::mousePressEvent(QMouseEvent * event)
{
}


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
void SE_Screen::mouseMoveEvent(QMouseEvent * event)
{
//     GLfloat dx = GLfloat(event->x() - lastPos.x()) / width();
//     GLfloat dy = GLfloat(event->y() - lastPos.y()) / height();
    if (event->buttons() & Qt::LeftButton)
    {
        updateGL();
    }
    else if (event->buttons() & Qt::RightButton)
    {
        updateGL();
    }
//     lastPos = event->pos();
}


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
void SE_Screen::mouseDoubleClickEvent(QMouseEvent * event)
{
}


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
void SE_Screen::timeOut()
{
    m_rotation_factor += 0.1f;
    updateGL();
}
