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

#include "config.h"

#define GLFW_INCLUDE_GLU
#include <GL/glfw3.h>

#include "SE_CLogManager.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
SE_CRenderManager::SE_CRenderManager():
    m_rotationAngle(0.f)
{
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_CRenderManager::startUp()
{
    SE_CLogManager::getInstance()->log(kInformation, "SE_CRenderManager successfully started");
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_CRenderManager::shutDown()
{
    SE_CLogManager::getInstance()->log(kInformation, "SE_CRenderManager successfully shut downed");
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_CRenderManager::render(const F32 inElapsedMs)
{
    const U32 rotationSpeed = 180; // degrees per second
    m_rotationAngle += inElapsedMs * rotationSpeed;
    if(m_rotationAngle > 360.f)
    {
        m_rotationAngle = 0.f;
    }

    static const U16 width  = 640;
    static const U16 height = 480;
    glViewport(0, 0, width, height);

    // Clear color buffer to white
    glClearColor(1.f, 1.f, 1.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT);

    glShadeModel(GL_SMOOTH); // GL_FLAT

    // Select and setup the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.f, (F32)width/height, 1.f, 100.f);

    // Select and setup the modelview matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(0.f, 1.f, 0.f,    // Eye-position
              0.f, 20.f, 0.f,   // View-point
              0.f, 0.f, 1.f);   // Up-vector

    // Draw a rotating colorful triangle
    glTranslatef(0.f, 14.f, 0.f);
    glRotatef(m_rotationAngle, // angle in degrees
              0.f,  // x
              0.f,  // y
              1.f); // z

    glBegin(GL_TRIANGLES);
    {
        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(-5.f, 0.f, -4.f);
        glColor3f(0.f, 1.f, 0.f);
        glVertex3f(5.f, 0.f, -4.f);
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(0.f, 0.f, 6.f);
    }
    glEnd();
}
