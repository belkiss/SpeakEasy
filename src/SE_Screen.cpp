#include "SE_Screen.h"
#include <QTimer>
#include <GL/glx.h>

// VBO Extension Function Pointers
PFNGLGENBUFFERSARBPROC    glGenBuffersARB    = 0; // VBO Name Generation Procedure
PFNGLBINDBUFFERARBPROC    glBindBufferARB    = 0; // VBO Bind Procedure
PFNGLBUFFERDATAARBPROC    glBufferDataARB    = 0; // VBO Data Loading Procedure
PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB = 0; // VBO Deletion Procedure


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
SE_Screen::SE_Screen(QWidget * inpParent):
    QGLWidget(inpParent),
    m_rotation_factor(0.f),
    m_position_x(0.5f),
    m_position_y(0.5f),
    m_position_z(0.5f)
{
    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeOut()));
    timer->start(20);

    // avoid inclusion of GLee
    glGenBuffersARB = (PFNGLGENBUFFERSARBPROC) glXGetProcAddressARB((const unsigned char*)"glGenBuffersARB");
    glBindBufferARB = (PFNGLBINDBUFFERARBPROC) glXGetProcAddressARB((const unsigned char*)"glBindBufferARB");
    glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC) glXGetProcAddressARB((const unsigned char*)"glDeleteBuffersARB");

}


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
void SE_Screen::initializeGL()
{
    qglClearColor(Qt::gray);

    // will color all with one color instead of gradient
    glShadeModel(GL_FLAT);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    m_generator.generateGround();

}


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
void SE_Screen::resizeGL(int inWidth, int inHeight)
{
    glViewport(0, 0, inWidth, inHeight);

    glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
//         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        gluPerspective( 45.0f, (GLfloat) inWidth / inHeight, 0.001f, 10000.f);
        gluLookAt(  m_position_x,m_position_y,m_position_z,
                    0,0,0,
                    0,0,1);

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

        qglColor(Qt::yellow);
        glEnableClientState( GL_VERTEX_ARRAY ); // Enable Vertex Arrays
        glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_generator.getVBOVerticesIndex() ); // Bind The Buffer
        glVertexPointer( 3, GL_FLOAT, 0, (char *) 0 ); // Set The Vertex Pointer To The Vertex Buffer

        glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_generator.getVBOIndicesIndex() ); // Bind The Buffer

        glDrawElements( GL_QUADS, m_generator.getGroundIndicesNb(), GL_UNSIGNED_BYTE, (char*) 0 );

        glDisableClientState( GL_VERTEX_ARRAY ); // Disable Vertex Arrays
        glBindBufferARB ( GL_ARRAY_BUFFER_ARB, 0 ); // disable vbos
}


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
void SE_Screen::keyPressEvent(QKeyEvent * inpEvent)
{
    switch(inpEvent->key())
    {
        case Qt::Key_Up :
            {
                m_position_y += 0.1f;
            }
            break;
        case Qt::Key_Down :
            {
                m_position_y -= 0.1f;
            }
            break;
        case Qt::Key_Left :
            {
                m_position_x -= 0.1f;
            }
            break;
        case Qt::Key_Right :
            {
                m_position_x += 0.1f;
            }
            break;
        default :
            {
            }
    }

    glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective( 45.0f, (GLfloat) 640 / 480, 0.001f, 10000.f);
        gluLookAt(  m_position_x,m_position_y,m_position_z,
                    0,0,0,
                    0,0,1);
    glMatrixMode(GL_MODELVIEW);
    updateGL();
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
    m_rotation_factor += 0.01f;
    updateGL();
}
