/*
 * This file is part of SpeakEasy.
 * Copyright (C) 2012  Lambert Clara <lambert.clara@yahoo.fr>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file    SE_CRenderManager.cpp
 * @brief   3d Rendering Manager
 *
 * @author  Lambert Clara <lambert.clara@yahoo.fr>
 * @date    Created : 2012-07-01
 */

#include "SE_CRenderManager.h"

#include <string>
#include <fstream>

// GLEW *MUST* be included before GLFW
#include <GL/glew.h>

#define GLFW_INCLUDE_GLU
#include <GL/glfw3.h>

#include "config.h"
#include "SE_CGUIGLFW.h"
#include "SE_CLogManager.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void loadFileToString(char const * const inpFileName,
                      std::string &outFileSource)
{
    ////////////////////////////////////////////////////////////////////////////
    std::ifstream fileStream(inpFileName, std::ios::binary);
    if (!fileStream.good())
    {
        SE_CLogManager::getInstance()->log(
            kError, "Shader file", inpFileName, "could not be found"
        );
        assert(false);// File does not exist
    }

    //This line reads in the whole file into a string
    outFileSource = std::string( std::istreambuf_iterator<char>(fileStream),
                                (std::istreambuf_iterator<char>()));

    fileStream.close();
    ////////////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
SE_CRenderManager::SE_CRenderManager():
    m_vertexShaderId(0),
    m_pixelShaderId(0),
    m_programId(0),
    m_vertexArrayObjectId(0),
    m_vertexBufferObjectId(0),
    m_colorBufferId(0),
    m_rotationAngle(0.f)
{
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool SE_CRenderManager::startUp()
{
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Clear color buffer to white
    glClearColor(1.f, 1.f, 1.f, 0.f);

    // We need to set this to GL_TRUE to overcome a glew bug
    glewExperimental = GL_TRUE;
    // Explanation :
    // GLEW calls glGetString(GL_EXTENSIONS) which causes GL_INVALID_ENUM on
    // GL 3.2 core context when glewInit() is called, causing a crash
    // We need to set glewExperimental to GL_TRUE in order to workaround the
    // problem until a proper fix (use glGetStringi instead of glGetString) is
    // issued by GLEW

    GLenum glewInitStatus = glewInit();
    if(glewInitStatus == GLEW_OK)
    {
        SE_CLogManager::getInstance()->log(
            kDebug, "Initializing GLEW", glewGetString(GLEW_VERSION)
        );

        // HACK unset the GL error GL_INVALID_ENUM caused by glew bug
        glGetError();

        createShaders();
        createVBO();

        m_initSuccess = true;
        SE_CLogManager::getInstance()->log(
            kInformation, "SE_CRenderManager successfully started"
        );
    }
    else
    {
        SE_CLogManager::getInstance()->log(
            kError, "glewInit failed :", glewGetErrorString(glewInitStatus)
        );
    }
    return m_initSuccess;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool SE_CRenderManager::shutDown()
{
    if(m_initSuccess)
    {
        destroyShaders();
        destroyVBO();
    }
    SE_CLogManager::getInstance()->log(
        kInformation, "SE_CRenderManager successfully shut downed"
    );
    return true;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_CRenderManager::render(const F32 /*inElapsedMs*/)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // mode, the type of array data that's going to be drawn
    // first, specifies the first index that we want to draw
    // count, specifies how many of the enabled indices to draw
    // NOTE this is *not* the number of triangles !
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_CRenderManager::createVBO()
{
    F32 const vertices[] =
    {
        -0.8f,  0.8f, 0.0f, 1.0f,
         0.8f,  0.8f, 0.0f, 1.0f,
        -0.8f, -0.8f, 0.0f, 1.0f,
         0.8f, -0.8f, 0.0f, 1.0f
    };

    // generate 1 vertex array object in the GPU's memory
    // A Vertex Array Object (or VAO) is an object that describes how the vertex
    // attributes are stored in a Vertex Buffer Object (or VBO)
    // Vertex attributes can be described by the glVertexAttribPointer function
    // and its two sister functions glVertexAttribIPointer and
    // glVertexAttribLPointer
    glGenVertexArrays(1, &m_vertexArrayObjectId);
    glBindVertexArray(m_vertexArrayObjectId);

    // generate 1 vertex buffer object in the GPU's memory
    // The generated buffers are of an undefined type until they are bound to a
    // specific target.
    glGenBuffers(1, &m_vertexBufferObjectId);

    // Buffers can be bound to several different targets, in our case
    // GL_ARRAY_BUFFER, which signifies that the data provided contains
    // vertex attributes.
    // Not only does glBindBuffer bind the buffer to the specified target,
    // it also activates the current buffer object as the target
    // This means that any buffer-related operations that involve the specified
    // target will be executed on the buffer identified by the buffer parameter
    // until another buffer is bound with a call to glBindBuffer.
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObjectId);

    // Copy our vertex data over to the GPU’s memory
    // the size (2nd parameter) is in bytes
    // The usage (4th parameter) is set to GL_STATIC_DRAW, which signifies to
    // OpenGL that the data uploaded to the memory will not be modified (static)
    // and used for image generation purposes (draw).
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // tell OpenGL what types of data we just sent to the GPU
    //
    // The first parameter is index, which is a user-maintained number.
    // This number is not generated by a function call of any kind, but must be
    // maintained by you. It is used to identify those parameters marked with a
    // layout qualifier in a GLSL shader program ex: layout(location = 0)
    // NOTE You can create many vertex attributes, as long as you keep their
    // index values less than the value of GL_MAX_VERTEX_ATTRIBS
    //
    // Unlike the size parameter that we used in our call to glBufferData,
    // this one does not represent the size of the data in bytes, but rather
    // the amount of components that make up a vertex. In our case, the size
    // parameter is set to 4, signifying the X, Y, Z, and W components of our
    // vertices.
    //
    // To calculate the size in bytes of each component, OpenGL needs to know
    // the data-type of each component passed to the type parameter, in our case
    // GL_FLOAT since each component is a floating point number.
    //
    // The values we pass are normalized, so there is no need to normalize them
    // again, hence the GL_FALSE
    //
    // We leave the stride parameter at 0
    //
    // The pointer parameter (the last one), when the current target is set to
    // GL_ARRAY_BUFFER, is a numerical offset in bytes in the block of data
    // supplied in glBufferData to where the significant data starts.
    // In our case we set it to 0.
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    // When we’re done providing vertex attributes, enable the attribute by
    // passing its index
    glEnableVertexAttribArray(0);

    // NOTE When you’re done drawing the buffer object, a call to
    // glDisableVertexAttribArray should be made.

    // NOTE Since we’re only drawing a single triangle in our program, the
    // glEnableVertexAttribArray and glDisableVertexAttribArray calls are made
    // in the CreateVBO and DestroyVBO functions, respectively. This means that
    // the vertex attributes created in CreateVBO are enabled throughout the
    // execution of the entire program; this would normally not be the case if
    // there was more than a single object to draw.


    // Now repeat the same steps but this time for the color data
    F32 const colors[] =
    {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f
    };

    glGenBuffers(1, &m_colorBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    logGLerror("creating VBO");
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_CRenderManager::destroyVBO()
{
    // disable the vertex attributes that we enabled in CreateVBO
    // NOTE in reverse order of creation !
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    // call glBindBuffer with the buffer parameter set to zero to indicate that
    // no buffers should be tied to the GL_ARRAY_BUFFER target
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // the previous line call allowed us to safely delete the buffers
    glDeleteBuffers(1, &m_colorBufferId);
    glDeleteBuffers(1, &m_vertexBufferObjectId);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &m_vertexArrayObjectId);

    logGLerror("destroying VBO");
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_CRenderManager::createShaders()
{
    std::string vertexShader;
    loadFileToString(SHADERS_DIR "simple_vs.glsl", vertexShader);

    GLchar const *pTmpVS = vertexShader.c_str();
    m_vertexShaderId = glCreateShader(GL_VERTEX_SHADER);

    // we set 1 as count because we only have one long string in pTmpVS
    //
    // The last parameter length is an array of integers denoting the lengths of
    // the strings in the string parameter. We leave this parameter at nullptr
    // because we use normal null-terminated strings.
    glShaderSource(m_vertexShaderId, 1, &pTmpVS, nullptr);
    glCompileShader(m_vertexShaderId);

    // repeat the steps for the pixel/fragment shader
    std::string pixelShader;
    loadFileToString(SHADERS_DIR "simple_ps.glsl", pixelShader);

    GLchar const *pTmpPS = pixelShader.c_str();
    m_pixelShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(m_pixelShaderId, 1, &pTmpPS, nullptr);
    glCompileShader(m_pixelShaderId);

    // now we need to combine the two shaders in a shader program object
    // so, we create such a program with glCreateProgram
    m_programId = glCreateProgram();

    // then we attach the shaders to the program
    glAttachShader(m_programId, m_vertexShaderId);
    glAttachShader(m_programId, m_pixelShaderId);

    // then link everything together
    glLinkProgram(m_programId);

    // finally, make the shader program object current
    // The current program remains active until glUseProgram is called with
    // another shader program object’s identifier.
    glUseProgram(m_programId);

    logGLerror("creating the shaders");
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_CRenderManager::destroyShaders()
{
    // tell OpenGL to stop using our shader program
    glUseProgram(0);

    // now we can safely detach the pixel and vertex shaders
    glDetachShader(m_programId, m_vertexShaderId);
    glDetachShader(m_programId, m_pixelShaderId);

    // and since the shaders are no longer in use by the shader program,
    // we can safely delete them
    glDeleteShader(m_pixelShaderId);
    glDeleteShader(m_vertexShaderId);

    // now that the shaders are detached, and the program is no longer in use,
    // we can delete the shader program
    glDeleteProgram(m_programId);

    logGLerror("destroying the shaders");
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_CRenderManager::logGLerror(char const * const inpDescriptionText) const
{
    GLenum errorStatus = glGetError();
    if(errorStatus != GL_NO_ERROR)
    {
        SE_CLogManager::getInstance()->log(
            kError, "gl error detected when", inpDescriptionText, ":",
            gluErrorString(errorStatus)
        );
    }
}
