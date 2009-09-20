#ifdef _WIN32
#include "GLee.h"
#endif
#include "SE_Screen.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <fstream>
#include <sstream>
#include "config.h"
#include <GL/glu.h>
#include <glibmm.h>

#include "misc.h"

#include <Eigen/Core>
using namespace Eigen;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
SE_Screen::SE_Screen():
    m_elapsed(0.f),
    m_anim_elapsed(0.f),
    m_speed(10.f),
    m_rotation_speed(5),
    m_camera_position(-5,-1,0),// relative to world position
    m_character_position(0,-0.2,-1),
    m_vbonbindices(0),
    m_vbovix(0),
    m_vboiix(0),
    m_programID(0),
    m_vertexShaderID(0),
    m_geometryShaderID(0),
    m_pixelShaderID(0),
    m_cursor_moved_by_us(true),
    m_mouse_old_pos(320,240), // init with width/2 and height/2
    m_frame_walk(0),
    m_frame_stand(0)
{
    m_camera_rotation.setIdentity();

    // TODO : put that in init
    m_view_quaternion    = Quaternionf(AngleAxisf( toRad(-90), Vector3f(1,0,0)));
    m_character_rotation = Quaternionf(AngleAxisf( toRad(-90), Vector3f(1,0,0)));
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
SE_Screen::~SE_Screen()
{
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void SE_Screen::initializeGL()
{
    glClearColor(160/255.f, 160/255.f, 164/255.f, 0.f);

    // will color all with one color instead of gradient
    // DEPRECATED with shaders...
//     glShadeModel(GL_FLAT); // GL_SMOOTH or GL_FLAT

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);  // enable backface culling
//     glCullFace(GL_BACK); // choose wich face to cull

    m_generator.generateGround();

    std::stringstream character_filename(std::stringstream::in | std::stringstream::out);

    character_filename << MD5_MODELS_DIR << "/humanoid";

    m_character_model.parsemd5mesh(character_filename.str() +           ".md5mesh");
    m_character_model.parsemd5anim(character_filename.str() + "walk"  + ".md5anim");
    m_character_model.parsemd5anim(character_filename.str() + "stand" + ".md5anim");

    // Generate And Bind The Vertex Buffer
    glGenBuffers( 1, &m_vbovix ); // Generate the name and store it in buffer ID
    glGenBuffers( 1, &m_vboiix ); // Get A Valid Name

    genCharAndAnimate();

    ////////////////////////////////////////////////////////////////////////////
    // Load vertex shader
    Glib::ustring vertexShaderSource;
    loadFileToString(Glib::ustring::compose("%1/%2",SHADERS_DIR,"vs_simple.glsl"),
                     vertexShaderSource);
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    // Load geometry shader
    Glib::ustring geometryShaderSource;
    loadFileToString(Glib::ustring::compose("%1/%2",SHADERS_DIR,"gs_simple.glsl"),
                     geometryShaderSource);
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    // Load pixel shader
    Glib::ustring pixelShaderSource;
    loadFileToString(Glib::ustring::compose("%1/%2",SHADERS_DIR,"ps_simple.glsl"),
                     pixelShaderSource);
    ////////////////////////////////////////////////////////////////////////////

    // get unique id for gl program
    m_programID = glCreateProgram();

    // get unique ids for gl shaders
    m_vertexShaderID   = glCreateShader(GL_VERTEX_SHADER);
    m_geometryShaderID = glCreateShader(GL_GEOMETRY_SHADER_EXT);
    m_pixelShaderID    = glCreateShader(GL_FRAGMENT_SHADER);


    // read shaders files and put them into corresponding index
    const GLchar* vs_tmp = static_cast<const GLchar*>(vertexShaderSource.c_str());
    glShaderSource(m_vertexShaderID,1,&vs_tmp, NULL);

//     const GLchar* gs_tmp = static_cast<const GLchar*>(geometryShaderSource.c_str());
//     glShaderSource(m_geometryShaderID,1,&gs_tmp, NULL);

    const GLchar* ps_tmp = static_cast<const GLchar*>(pixelShaderSource.c_str());
    glShaderSource(m_pixelShaderID,1,&ps_tmp, NULL);


    // compile the shaders
    glCompileShader(m_vertexShaderID);
//     glCompileShader(m_geometryShaderID);
    glCompileShader(m_pixelShaderID);

    // TODO: check the result of the shader compilation
    // GLint result;
    // glGetShaderiv(m_pixelShaderID, GL_COMPILE_STATUS, &result);
    // std::cout<<"GL_COMPILE_STATUS "<<result<<std::endl;

    // attach the shaders
    glAttachShader(m_programID, m_vertexShaderID);
//     glAttachShader(m_programID, m_geometryShaderID);
    glAttachShader(m_programID, m_pixelShaderID);

    // link GLSL program
    glLinkProgram(m_programID);
    // TODO: check the result of the link
    // GLint* reslink = new GLint[20];
    // glGetProgramiv(m_programID, GL_LINK_STATUS, reslink);
    // std::cout<<"GL_LINK_STATUS "<<reslink[0]<<std::endl;

    // glGetProgramiv(m_programID, GL_ATTACHED_SHADERS, reslink);
    // std::cout<<"GL_ATTACHED_SHADERS "<<reslink[0]<<std::endl;

    // TODO: check the result of the link
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


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
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


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_Screen::paintGL()
{
    m_elapsed = m_clock.GetElapsedTime();
    m_anim_elapsed += m_elapsed;
    m_clock.Reset();
    process_keyboard();
    if(m_anim_elapsed >= 0.0417f)
    {
        genCharAndAnimate();
        m_anim_elapsed = 0.f;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Matrix4f cam_rot_m4 = Matrix4f::Identity();
    cam_rot_m4.minor(3,3) = m_camera_rotation.toRotationMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(m_character_position.getX(),m_character_position.getY(),m_character_position.getZ());
    glMultMatrixf(cam_rot_m4.data());
    glPushMatrix();

    Matrix4f char_rot_m4 = Matrix4f::Identity();
    char_rot_m4.minor(3,3) = m_character_rotation.toRotationMatrix();
    glMultMatrixf(char_rot_m4.data());
    draw_axis();
    glPopMatrix();

    Matrix4f view_rot_m4 = Matrix4f::Identity();
    view_rot_m4.minor(3,3) = m_view_quaternion.toRotationMatrix();

    glMultMatrixf(view_rot_m4.data());
    glTranslatef(m_camera_position.getX(),m_camera_position.getY(),m_camera_position.getZ());
    draw();
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
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

    glDrawElements( GL_TRIANGLES, m_vbonbindices, GL_UNSIGNED_INT, (char*) 0 );

    glDisableVertexAttribArray(0);
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
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

    glDrawElements( GL_TRIANGLES, m_generator.getGroundIndicesNb(), GL_UNSIGNED_INT, (char*) 0 );

    glDisableVertexAttribArray(0);
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_Screen::keyPressEvent (const sf::Key::Code &inEvent)
{
    switch(inEvent)
    {
        case sf::Key::W :
            {
                glMatrixMode(GL_MODELVIEW);
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // GL_FILL to fully paint the triangles, GL_LINE to draw only borders
            }
            break;
        case sf::Key::X :
            {
                glMatrixMode(GL_MODELVIEW);
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // GL_FILL to fully paint the triangles, GL_LINE to draw only borders
            }
            break;
        default :
            {
                m_pressed_keys[inEvent] = true;
            }
            break;
    }

}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_Screen::keyReleaseEvent(const sf::Key::Code &inEvent)
{
    m_pressed_keys[inEvent] = false;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_Screen::mouseMoveEvent (sf::Window * inApp, const int &inX, const int &inY)
{
    if(!m_cursor_moved_by_us)
    {
        int move_x = inX - m_mouse_old_pos.first;

        if(move_x != 0) // turn right / left
        {
            Quaternionf eiq_rotvec(AngleAxisf( toRad(move_x * m_rotation_speed * m_elapsed), Vector3f(0,1,0) ));
            m_camera_rotation = m_camera_rotation * eiq_rotvec;
            m_camera_rotation.normalize();
        }

        int move_y = inY - m_mouse_old_pos.second;
        if(move_y != 0) // look up / down
        {
            Quaternionf eiq_rotvec(AngleAxisf( toRad(move_y * m_rotation_speed * m_elapsed), Vector3f(1,0,0) ));
            m_camera_rotation = eiq_rotvec * m_camera_rotation;
            m_camera_rotation.normalize();
        }

        m_mouse_old_pos = std::make_pair(inX,inY);

        m_cursor_moved_by_us = true;
        inApp->SetCursorPosition(320,240);
    }
    else
    {
        m_mouse_old_pos = std::make_pair(320,240);
        m_cursor_moved_by_us = false;
    }
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_Screen::process_keyboard()
{
    Quaternionf cam_lookat_quat(AngleAxisf( toRad(-90), Vector3f(1,0,0)));
    cam_lookat_quat.normalize();

    Quaternionf new_lookat_quat = m_camera_rotation.conjugate() * cam_lookat_quat * m_camera_rotation;
    new_lookat_quat.normalize();

    Vector3f dir_vec = new_lookat_quat.vec();
    dir_vec.normalize();

    // compute the right vec from vector product between dir and up
    Vector3f right_vec = dir_vec.cross(Vector3f(0,1,0));

    for( std::map<sf::Key::Code, bool>::iterator it = m_pressed_keys.begin(); it != m_pressed_keys.end(); ++it)
    {
        if(it->second)
        {
            switch(it->first)
            {
                case sf::Key::Divide :
                    {
                        m_generator.subdivideGround();
                        it->second = false; // to avoid too many repetitions of subdivision
                    }
                    break;
                case sf::Key::Left :
                    {
                        Quaternionf glq_rotvec(AngleAxisf( toRad( m_rotation_speed * m_elapsed ), Vector3f(0,0,1)));
                        m_character_rotation = m_character_rotation * glq_rotvec;
                    }
                    break;
                case sf::Key::Right :
                    {
                        Quaternionf glq_rotvec(AngleAxisf( toRad(-m_rotation_speed * m_elapsed ), Vector3f(0,0,1)));
                        m_character_rotation = m_character_rotation * glq_rotvec;
                    }
                    break;
                case sf::Key::Up :
                    {
                        Quaternionf glq_rotvec(AngleAxisf( toRad( m_rotation_speed * m_elapsed ), Vector3f(1,0,0)));
                        m_view_quaternion = glq_rotvec * m_view_quaternion;
                    }
                    break;
                case sf::Key::Down :
                    {
                        Quaternionf glq_rotvec(AngleAxisf( toRad(-m_rotation_speed * m_elapsed ), Vector3f(1,0,0)));
                        m_view_quaternion = glq_rotvec * m_view_quaternion;
                    }
                    break;
                case sf::Key::Z :
                    {
                        m_camera_position = uSE_GLVector(m_camera_position.getX()+dir_vec.z()*m_speed * m_elapsed, m_camera_position.getY()+dir_vec.x()*m_speed * m_elapsed, m_camera_position.getZ());
                    }
                    break;
                case sf::Key::S :
                    {
                        m_camera_position = uSE_GLVector(m_camera_position.getX()-dir_vec.z()*m_speed * m_elapsed, m_camera_position.getY()-dir_vec.x()*m_speed * m_elapsed, m_camera_position.getZ());
                    }
                    break;
                case sf::Key::Q :
                    {
                        m_camera_position = uSE_GLVector(m_camera_position.getX()-right_vec.z()*m_speed * m_elapsed, m_camera_position.getY()-right_vec.x()*m_speed * m_elapsed, m_camera_position.getZ());
                    }
                    break;
                case sf::Key::D :
                    {
                        m_camera_position = uSE_GLVector(m_camera_position.getX()+right_vec.z()*m_speed * m_elapsed, m_camera_position.getY()+right_vec.x()*m_speed * m_elapsed, m_camera_position.getZ());
                    }
                    break;
                case sf::Key::LControl :
                    {
                        m_camera_position = uSE_GLVector(m_camera_position.getX(), m_camera_position.getY(), m_camera_position.getZ() + m_speed * m_elapsed);
                    }
                    break;
                case sf::Key::Space :
                    {
                        m_camera_position = uSE_GLVector(m_camera_position.getX(), m_camera_position.getY(), m_camera_position.getZ() - m_speed * m_elapsed);
                    }
                    break;
                default :
                    break;
            }
        }
    }
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_Screen::genCharAndAnimate()
{
    if( !m_pressed_keys[sf::Key::Z] && !m_pressed_keys[sf::Key::S])
    {
        m_frame_stand + 2 > m_character_model.getNbFramesFromAnim(1) ? m_frame_stand = 0 : m_frame_stand++;
        m_character_model.generateVerticesIndicesFromAnimAtFrame(1, m_frame_stand);
    }
    else
    {
        m_frame_walk + 2 > m_character_model.getNbFramesFromAnim(0) ? m_frame_walk = 0 : m_frame_walk++;
        m_character_model.generateVerticesIndicesFromAnimAtFrame(0, m_frame_walk);
    }

    m_character_model.generateVerticesIndicesPose();

    glBindBuffer( GL_ARRAY_BUFFER, m_vbovix ); // Bind The Buffer
    glBufferData( GL_ARRAY_BUFFER, m_character_model.get_nb_pose_vertices() * sizeof(GLfloat), &m_character_model.get_pose_vertices().front(), GL_STATIC_DRAW );    // Load The Data

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_vboiix ); // Bind The Buffer
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, m_character_model.get_nb_pose_indices() * sizeof(GLuint),&m_character_model.get_pose_indices().front(), GL_STATIC_DRAW );    // Load The Data

    m_vbonbindices =  m_character_model.get_nb_pose_indices();
}
