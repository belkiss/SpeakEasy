#include "SE_Screen.h"
#include <QTimer>
#include <cmath>
#include <cassert>
#include <fstream>

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
SE_Screen::SE_Screen(QWidget * inpParent):
    QGLWidget(inpParent),
    m_oldMousePosition(),  // X and Y init in constructor
    m_angle(0),
    m_camera_position(-5,-1,0),// relative to world position
    m_view_quaternion(1,uSE_GLVector(-0.5,0,0)),
    m_programID(0),
    m_vertexShaderID(0),
    m_pixelShaderID(0)
{

    m_view_quaternion.from_axis(uSE_GLVector(1,0,0),-90);

    ///////////////////////////////////////
    // QT Widget specific settings start //
    ///////////////////////////////////////

    // enable mouse tracking to send mouseMoveEvent at each movement instead of only at click
    setMouseTracking(true);

    ///////////////////////////////////////
    // QT Widget specific settings end   //
    ///////////////////////////////////////

    setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeOut()));
    timer->start(20);
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void SE_Screen::initializeGL()
{
    qglClearColor(Qt::gray);

    // will color all with one color instead of gradient
    // DEPRECATED with shaders...
//     glShadeModel(GL_FLAT); // GL_SMOOTH or GL_FLAT

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);  // enable backface culling
//     glCullFace(GL_BACK); // choose wich face to cull

    m_generator.generateGround();

    ///////////////////////////////////////////////////////
    ////////////// AXIS CODE ON ///////////////////////////
    ///////////////////////////////////////////////////////
    // generate axis
    std::vector<GLfloat> vl_vertices;
    std::vector<GLubyte> vl_indices;

    vl_vertices.push_back( 0 );// x
    vl_vertices.push_back( 0 );// y
    vl_vertices.push_back( 0 );// z

    vl_vertices.push_back( 0.25f );// x
    vl_vertices.push_back( 0 );// y
    vl_vertices.push_back( 0 );// z

    vl_vertices.push_back( 0 );// x
    vl_vertices.push_back( 0.25f );// y
    vl_vertices.push_back( 0 );// z

    vl_vertices.push_back( 0 );// x
    vl_vertices.push_back( 0 );// y
    vl_vertices.push_back( 0.25f );// z

    // note : the order is very important !!!!
    vl_indices.push_back(0);
    vl_indices.push_back(1);

    vl_indices.push_back(0);
    vl_indices.push_back(2);

    vl_indices.push_back(0);
    vl_indices.push_back(3);

    // Generate And Bind The Vertex Buffer
    glGenBuffers( 1, &m_vbovix );                  // Generate the name and store it in buffer ID
    glBindBuffer( GL_ARRAY_BUFFER, m_vbovix ); // Bind The Buffer
    glBufferData( GL_ARRAY_BUFFER, vl_vertices.size() * sizeof(GLfloat), &vl_vertices.front(), GL_STATIC_DRAW );    // Load The Data

    glGenBuffers( 1, &m_vboiix);                  // Get A Valid Name
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_vboiix ); // Bind The Buffer
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, vl_indices.size() * sizeof(GLubyte),&vl_indices.front(), GL_STATIC_DRAW );    // Load The Data

    ///////////////////////////////////////////////////////
    ////////////// AXIS CODE OFF //////////////////////////
    ///////////////////////////////////////////////////////

    #warning get the path from environment variable
    std::ifstream vsfileIn("shaders/vs_simple.glsl", std::ios::binary);
    if (!vsfileIn.good())
    {
        assert(false);// File does not exist
    }

    //This line reads in the whole file into a string
    std::string vertexShaderSource(std::istreambuf_iterator<char>(vsfileIn), (std::istreambuf_iterator<char>()));

    vsfileIn.close();

    #warning get the path from environment variable
    std::ifstream pixelfileIn("shaders/ps_simple.glsl", std::ios::binary);
    if (!pixelfileIn.good())
    {
        assert(false);// File does not exist
    }

    std::string pixelShaderSource(std::istreambuf_iterator<char>(pixelfileIn), (std::istreambuf_iterator<char>()));


    // get unique id for gl program
    m_programID = glCreateProgram();

    // get unique ids for gl shaders
    m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    m_pixelShaderID = glCreateShader(GL_FRAGMENT_SHADER);


    // read shaders files and put them into corresponding index
    const GLchar* tmp = static_cast<const GLchar*>(vertexShaderSource.c_str());
    glShaderSource(m_vertexShaderID,1,&tmp, NULL);

    const GLchar* tmpp = static_cast<const GLchar*>(pixelShaderSource.c_str());
    glShaderSource(m_pixelShaderID,1,&tmpp, NULL);


    // compile the shaders
    glCompileShader(m_vertexShaderID);
    glCompileShader(m_pixelShaderID);

    #warning check the result of the shader compilation
    // GLint result;
    // glGetShaderiv(m_pixelShaderID, GL_COMPILE_STATUS, &result);
    // std::cout<<"GL_COMPILE_STATUS "<<result<<std::endl;

    // attach the shaders
    glAttachShader(m_programID, m_vertexShaderID);
    glAttachShader(m_programID, m_pixelShaderID);

    // link GLSL program
    glLinkProgram(m_programID);
    #warning check the result of the link
    // GLint* reslink = new GLint[20];
    // glGetProgramiv(m_programID, GL_LINK_STATUS, reslink);
    // std::cout<<"GL_LINK_STATUS "<<reslink[0]<<std::endl;

    // glGetProgramiv(m_programID, GL_ATTACHED_SHADERS, reslink);
    // std::cout<<"GL_ATTACHED_SHADERS "<<reslink[0]<<std::endl;

    #warning check the result of the link
    // GLsizei sizelog;
    // GLchar * infoLog = new GLchar[1000];
    // glGetProgramInfoLog(m_programID, 1000, &sizelog, infoLog);
    // std::cout<<"log length "<<sizelog<<std::endl;
    // std::cout<<"LOG : "<<std::endl;
    // for(unsigned int i = 0; i < sizelog; i++)
    // std::cout<<infoLog[i];

    // enable the program
    glUseProgram(m_programID);

}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void SE_Screen::resizeGL(int inWidth, int inHeight)
{
    glViewport(0, 0, inWidth, inHeight);

    glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective( 45.0f, (GLfloat) inWidth / inHeight, 0.001f, 10000.f);

    glMatrixMode(GL_MODELVIEW);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // GL_FILL to fully paint the triangles, GL_LINE to draw only borders
        glLoadIdentity();
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void SE_Screen::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(m_view_quaternion.get_matrix().get_array());
    glTranslatef(m_camera_position.getX(),m_camera_position.getY(),m_camera_position.getZ());
    draw();

    glLoadIdentity();
    glTranslatef(0,0,-1);
    draw_axis();

}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void SE_Screen::draw_axis()
{
    float modelviewMatrix[16];
    float projectionMatrix[16];

    //Get the current matrices from OpenGL
    glGetFloatv(GL_MODELVIEW_MATRIX, modelviewMatrix);
    glGetFloatv(GL_PROJECTION_MATRIX, projectionMatrix);

    glEnableVertexAttribArray(0); //Enable the vertex attribute

    //Send the modelview and projection matrices to the shaders
    GLuint location = glGetUniformLocation(m_programID,"modelview_matrix");
    glUniformMatrix4fv(location, 1, false, modelviewMatrix);

// std::cout<< modelviewMatrix[0] << " " << modelviewMatrix[4]<< " "<< modelviewMatrix[8]<< " "<< modelviewMatrix[12]<<std::endl;
// std::cout<< modelviewMatrix[1] << " " << modelviewMatrix[5]<< " "<< modelviewMatrix[9]<< " "<< modelviewMatrix[13]<<std::endl;
// std::cout<< modelviewMatrix[2] << " " << modelviewMatrix[6]<< " "<< modelviewMatrix[10]<< " "<< modelviewMatrix[14]<<std::endl;
// std::cout<< modelviewMatrix[3] << " " << modelviewMatrix[7]<< " "<< modelviewMatrix[11]<< " "<< modelviewMatrix[15]<<std::endl<<std::endl;

    location = glGetUniformLocation(m_programID,"projection_matrix");
    glUniformMatrix4fv(location, 1, false, projectionMatrix);

    glBindBuffer( GL_ARRAY_BUFFER, m_vbovix ); // Bind The Buffer

    glVertexAttribPointer((GLint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_vboiix ); // Bind The Buffer

    #warning replace constant 6 by nb of vertices
    glDrawElements( GL_LINES, 6, GL_UNSIGNED_BYTE, (char*) 0 );

    glDisableVertexAttribArray(0);
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void SE_Screen::draw()
{
    float modelviewMatrix[16];
    float projectionMatrix[16];

    //Get the current matrices from OpenGL
    glGetFloatv(GL_MODELVIEW_MATRIX, modelviewMatrix);
    glGetFloatv(GL_PROJECTION_MATRIX, projectionMatrix);

    glEnableVertexAttribArray(0); //Enable the vertex attribute

    //Send the modelview and projection matrices to the shaders
    GLuint location = glGetUniformLocation(m_programID,"modelview_matrix");
    glUniformMatrix4fv(location, 1, false, modelviewMatrix);

// std::cout<< modelviewMatrix[0] << " " << modelviewMatrix[4]<< " "<< modelviewMatrix[8]<< " "<< modelviewMatrix[12]<<std::endl;
// std::cout<< modelviewMatrix[1] << " " << modelviewMatrix[5]<< " "<< modelviewMatrix[9]<< " "<< modelviewMatrix[13]<<std::endl;
// std::cout<< modelviewMatrix[2] << " " << modelviewMatrix[6]<< " "<< modelviewMatrix[10]<< " "<< modelviewMatrix[14]<<std::endl;
// std::cout<< modelviewMatrix[3] << " " << modelviewMatrix[7]<< " "<< modelviewMatrix[11]<< " "<< modelviewMatrix[15]<<std::endl<<std::endl;

    location = glGetUniformLocation(m_programID,"projection_matrix");
    glUniformMatrix4fv(location, 1, false, projectionMatrix);

    glBindBuffer( GL_ARRAY_BUFFER, m_generator.getVBOVerticesIndex() ); // Bind The Buffer

    // instead of (char*) there is a macro BUFFER_OFFSET (unverified)
    glVertexAttribPointer((GLint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_generator.getVBOIndicesIndex() ); // Bind The Buffer

    glDrawElements( GL_TRIANGLES, m_generator.getGroundIndicesNb(), GL_UNSIGNED_BYTE, (char*) 0 );

    glDisableVertexAttribArray(0);
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void SE_Screen::keyPressEvent(QKeyEvent * inpEvent)
{

    if ( inpEvent->isAutoRepeat() )
    {
        inpEvent->ignore();
        return;
    }

    switch(inpEvent->key())
    {
        case Qt::Key_W :
            {
                glMatrixMode(GL_MODELVIEW);
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // GL_FILL to fully paint the triangles, GL_LINE to draw only borders
            }
            break;
        case Qt::Key_X :
            {
                glMatrixMode(GL_MODELVIEW);
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // GL_FILL to fully paint the triangles, GL_LINE to draw only borders
            }
            break;
        case Qt::Key_Left :
            {
                uSE_Quaternion glq_rotvec;
                glq_rotvec.from_axis(uSE_GLVector(0,1,0),-10);
                m_view_quaternion = glq_rotvec * m_view_quaternion;
            }
            break;
        case Qt::Key_Right :
            {
                uSE_Quaternion glq_rotvec;
                glq_rotvec.from_axis(uSE_GLVector(0,1,0),10);
                m_view_quaternion = glq_rotvec * m_view_quaternion;
            }
            break;
        case Qt::Key_Up :
            {
                uSE_Quaternion glq_rotvec;
                glq_rotvec.from_axis(uSE_GLVector(1,0,0),10);
                m_view_quaternion = glq_rotvec * m_view_quaternion;
            }
            break;
        case Qt::Key_Down :
            {
                uSE_Quaternion glq_rotvec;
                glq_rotvec.from_axis(uSE_GLVector(1,0,0),-10);
                m_view_quaternion = glq_rotvec * m_view_quaternion;
            }
            break;
        case Qt::Key_Z :
                {
                    m_camera_position = uSE_GLVector(m_camera_position.getX(),m_camera_position.getY()-0.1,m_camera_position.getZ());
                }
                break;
        case Qt::Key_S :
                {
                    m_camera_position = uSE_GLVector(m_camera_position.getX(),m_camera_position.getY()+0.1,m_camera_position.getZ());
                }
                break;
        case Qt::Key_Q :
                {
                    m_camera_position = uSE_GLVector(m_camera_position.getX()+0.1,m_camera_position.getY(),m_camera_position.getZ());
                }
                break;
        case Qt::Key_D :
                {
                    m_camera_position = uSE_GLVector(m_camera_position.getX()-0.1,m_camera_position.getY(),m_camera_position.getZ());
                }
                break;
        case Qt::Key_Minus :
                {
                    m_camera_position = uSE_GLVector(m_camera_position.getX(),m_camera_position.getY(),m_camera_position.getZ()+0.1);
                }
                break;
        case Qt::Key_Plus :
                {
                    m_camera_position = uSE_GLVector(m_camera_position.getX(),m_camera_position.getY(),m_camera_position.getZ()-0.1);
                }
                break;
        default :
            break;
    }
    inpEvent->accept();
    updateGL();
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void SE_Screen::mousePressEvent(QMouseEvent * /*event*/)
{
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void SE_Screen::mouseMoveEvent(QMouseEvent * /*event*/)
{
//     if (event->button() & Qt::NoButton)
//     {
//         printf("x: %d y: %d\n",event->x(),event->y());
//         updateGL();
//     }

// //     GLfloat dx = GLfloat(event->x() - m_oldMousePosition.x()) / width();
// //     GLfloat dy = GLfloat(event->y() - m_oldMousePosition.y()) / height();

// event->pos()

//     m_oldMousePosition = event->pos();
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void SE_Screen::mouseDoubleClickEvent(QMouseEvent * /*event*/)
{
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void SE_Screen::timeOut()
{
    // do some stuff each 20ms
//     m_angle < 360 ? m_angle++ : m_angle = 0;
    updateGL();
}
