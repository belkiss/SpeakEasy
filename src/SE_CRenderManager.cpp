/*
 * This file is part of SpeakEasy.
 * Copyright (C) 2012-2014 Lambert Clara <lambert.clara@yahoo.fr>
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
#include <cmath>

// GLEW *MUST* be included before GLFW
#include "SE_GLEW_Include.h"
#include "SE_GLFW3_Include.h"

#include "config.h"
#include "SE_CGUIGLFW.h"
#include "SE_CLogManager.h"
#include "shaders/simple_fs.h"
#include "shaders/simple_vs.h"



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool SE_CRenderManager::startUp()
{
    // Tell OpenGL what area of the available area we are rendering to
    // NOTE Window coordinates are in a lower-left coordinate system, so the
    // point (0, 0) is the bottom left of the window
    // TODO: check if a call to glViewport is really necessary here


    // Clear color buffer to white
    glClearColor(0xa1 / 255.f, 0xbe / 255.f, 0xd0 / 255.f, 0.f);

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
        seLogDebug("Initializing GLEW ", glewGetString(GLEW_VERSION));

        // HACK unset the GL error GL_INVALID_ENUM caused by glew bug
        glGetError();

        if(createShaders())
        {
            createVBO();
            m_initSuccess = true;

            seLogInfo("SE_CRenderManager successfully started");
        }
    }
    else
    {
        seLogError("glewInit failed : ", glewGetErrorString(glewInitStatus));
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
    seLogInfo("SE_CRenderManager successfully shut downed");
    return true;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_CRenderManager::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    F32 offsetX = 0.f;
    F32 offsetY = 0.f;
    computePositionOffsets(offsetX, offsetY);
    adjustVertexData      (offsetX, offsetY);

    glUseProgram(m_programId);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObjectId);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

    // mode, the type of array data that's going to be drawn
    // first, specifies the first index that we want to draw
    // count, specifies how many of the enabled indices to draw
    // NOTE this is *not* the number of triangles !
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(0);
    glUseProgram(0);
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_CRenderManager::createVBO()
{
    m_vertices =
    {
         0.0f,  0.5f,   0.0f, 1.0f,
         0.5f, -0.366f, 0.0f, 1.0f,
        -0.5f, -0.366f, 0.0f, 1.0f,
         1.0f,  0.0f,   0.0f, 1.0f,
         0.0f,  1.0f,   0.0f, 1.0f,
         0.0f,  0.0f,   1.0f, 1.0f
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
    //
    // GL_STREAM_DRAW tells OpenGL that you intend to set this data constantly,
    // generally once per frame.
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<GLsizeiptr>(m_vertices.size() * sizeof(F32)),
                 m_vertices.data(),
                 GL_STREAM_DRAW);

    // tell OpenGL what types of data we just sent to the GPU
    //
    // glVertexAttribPointer always refers to whatever buffer is bound to
    // GL_ARRAY_BUFFER at the time that the function is called
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
    static U32 const vs_inPositionAttribIndex = 0;
    glVertexAttribPointer(vs_inPositionAttribIndex, 4, GL_FLOAT, GL_FALSE, 0, nullptr );
    // When we’re done providing vertex attributes, enable the attribute by
    // passing its index
    glEnableVertexAttribArray(vs_inPositionAttribIndex);

    static U32 const vs_inColorAttribIndex = 1;
    glVertexAttribPointer(vs_inColorAttribIndex, 4, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(4*3*4));
    glEnableVertexAttribArray(vs_inColorAttribIndex);

    // NOTE When you’re done drawing the buffer object, a call to
    // glDisableVertexAttribArray should be made.

    // NOTE Since we’re only drawing a single triangle in our program, the
    // glEnableVertexAttribArray and glDisableVertexAttribArray calls are made
    // in the CreateVBO and DestroyVBO functions, respectively. This means that
    // the vertex attributes created in CreateVBO are enabled throughout the
    // execution of the entire program; this would normally not be the case if
    // there was more than a single object to draw.

    // call glBindBuffer with the buffer parameter set to zero to indicate that
    // no buffers should be tied to the GL_ARRAY_BUFFER target
    glBindBuffer(GL_ARRAY_BUFFER, 0);

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
    glDeleteBuffers(1, &m_vertexBufferObjectId);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &m_vertexArrayObjectId);

    logGLerror("destroying VBO");
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool SE_CRenderManager::createShader(U32          const inShaderType,
                                     char const *       inpShaderString,
                                     U32               &outShaderId)
{
    bool success = false;

    seAssert(outShaderId == 0, "The shaderId passed to createShader must be == 0 !");
    outShaderId = glCreateShader(inShaderType);

    // we set 1 as count because we only have one long string in inpShaderString
    //
    // The last parameter length is an array of integers denoting the lengths of
    // the strings in the string parameter. We leave this parameter at nullptr
    // because we use normal null-terminated strings.
    glShaderSource(outShaderId, 1, &inpShaderString, nullptr);
    glCompileShader(outShaderId);

    I32 compileStatus;
    glGetShaderiv(outShaderId, GL_COMPILE_STATUS, &compileStatus);
    if(compileStatus == GL_TRUE)
    {
        success = true;
    }
    else
    {
        I32 infoLogLength;
        glGetShaderiv(outShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar *pStrInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(outShaderId, infoLogLength, nullptr, pStrInfoLog);

        seLogError("Error compiling shader :\n", pStrInfoLog);

        delete [] pStrInfoLog;
    }

    return success;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool SE_CRenderManager::createShaders()
{
    bool success = true;

    success = success && createShader(GL_VERTEX_SHADER,   simple_vs, m_vertexShaderId);
    success = success && createShader(GL_FRAGMENT_SHADER, simple_fs, m_fragmentShaderId);

    if(success)
    {
        // now we need to combine the two shaders in a shader program object
        // so, we create such a program with glCreateProgram
        m_programId = glCreateProgram();

        // then we attach the shaders to the program
        glAttachShader(m_programId, m_vertexShaderId);
        glAttachShader(m_programId, m_fragmentShaderId);

        // then link everything together
        glLinkProgram(m_programId);

        I32 linkStatus;
        glGetProgramiv(m_programId, GL_LINK_STATUS, &linkStatus);
        if(linkStatus == GL_TRUE)
        {
            // finally, make the shader program object current
            // The current program remains active until glUseProgram is called with
            // another shader program object’s identifier.
            glUseProgram(m_programId);

            // now we can safely detach the pixel and vertex shaders
            glDetachShader(m_programId, m_vertexShaderId);
            glDetachShader(m_programId, m_fragmentShaderId);

            // and since the shaders are no longer in use by the shader program,
            // we can safely delete them
            glDeleteShader(m_fragmentShaderId);
            glDeleteShader(m_vertexShaderId);
        }
        else
        {
            I32 infoLogLength;
            glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &infoLogLength);

            GLchar *pStrInfoLog = new GLchar[infoLogLength + 1];
            glGetProgramInfoLog(m_programId, infoLogLength, nullptr, pStrInfoLog);

            seLogError("Error linking program :\n", pStrInfoLog);

            delete [] pStrInfoLog;
        }
    }

    logGLerror("creating the shaders");

    return success;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_CRenderManager::destroyShaders()
{
    // tell OpenGL to stop using our shader program
    glUseProgram(0);

//     // now we can safely detach the pixel and vertex shaders
//     glDetachShader(m_programId, m_vertexShaderId);
//     glDetachShader(m_programId, m_fragmentShaderId);

//     // and since the shaders are no longer in use by the shader program,
//     // we can safely delete them
//     glDeleteShader(m_fragmentShaderId);
//     glDeleteShader(m_vertexShaderId);

    // now that the shaders are detached, and the program is no longer in use,
    // we can delete the shader program
    glDeleteProgram(m_programId);

    logGLerror("destroying the shaders");
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_CRenderManager::logGLerror(char const * const inpDescriptionText) const
{
    const GLenum errorStatus = glGetError();
    if(errorStatus != GL_NO_ERROR)
    {
        seLogError("gl error detected when ", inpDescriptionText, ": ", errorStatus);
    }
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_CRenderManager::computePositionOffsets(F32 &outXOffset, F32 &outYOffset)
{
    F32 const loopDuration = 5.0f;
    F32 const scale = 3.14159f * 2.0f / loopDuration;

    F32 elapsedTime = static_cast<F32>(glfwGetTime());//std::chrono::duration_cast<std::chrono::milliseconds>(SE_CClock::getNowTimePoint()).count() / 1000.0f;

    F32 currentTimeThroughLoop = fmodf(elapsedTime, loopDuration);

    outXOffset = cosf(currentTimeThroughLoop * scale) * 0.5f;
    outYOffset = sinf(currentTimeThroughLoop * scale) * 0.5f;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_CRenderManager::adjustVertexData(F32 const inXOffset,
                                         F32 const inYOffset)
{
    std::vector<F32> newData = m_vertices;
    newData.resize(12);

    for(U32 i = 0; i < newData.size(); i += 4)
    {
        newData.at(i)     += inXOffset;
        newData.at(i + 1) += inYOffset;
    }

    // As always, bind the buffer we want to work on, in this case, the one
    // containing the vertex positions)
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObjectId);

    // The difference between glBufferData and glBufferSubData is that the SubData
    // function does *not* allocate memory. It only transfers data the already
    // existing memory.
    //
    // Calling glBufferData on a buffer object that has already been allocated
    // tells OpenGL to *reallocate* this memory, throwing away the previous data
    // and allocating a fresh block of memory.
    // Whereas calling glBufferSubData on a buffer object that has not yet had
    // memory allocated by glBufferData is an error.
    //
    // Think of glBufferData as malloc and memcpy, while glBufferSubData is just memcpy.
    //
    //
    // glBufferSubData can update only a portion of the buffer object's memory.
    // The 2nd parameter is the byte offset into the buffer object to begin copying to
    // The 3rd parameter is number of bytes to copy.
    // The 4th paramter is our array of bytes to be copied into that location
    // of the buffer object.
    glBufferSubData(
        GL_ARRAY_BUFFER,
        0,
        static_cast<GLsizeiptr>(newData.size() * sizeof(F32)),
        newData.data()
    );

    // call glBindBuffer with the buffer parameter set to zero to indicate that
    // no buffers should be tied to the GL_ARRAY_BUFFER target
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

