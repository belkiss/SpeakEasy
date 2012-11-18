/*
 * This file is part of SpeakEasy.
 * Copyright (C) 2011-2012  Lambert Clara <lambert.clara@yahoo.fr>
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
 * @file    SE_CGUIGLFW.cpp
 * @brief   Wrapper for GLFW library
 *
 * @author  Lambert Clara <lambert.clara@yahoo.fr>
 * @date    Created : 2011-08-23
 */

#include "SE_CGUIGLFW.h"
#include <GL/glfw3.h>
#include "config.h"
#include "SE_CGUIManager.h"
#include "SE_CLogManager.h"

extern I32 const WINDOW_WIDTH  = 640;
extern I32 const WINDOW_HEIGHT = 480;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool SE_CGUIGLFW::init()
{
    bool initSuccess = false;
    SE_CLogManager::getInstance()->log(
        kDebug, "Initializing GLFW", glfwGetVersionString()
    );
    I32 const initStatus = glfwInit();
    if(initStatus == GL_TRUE)
    {
        initSuccess = true;
    }
    else
    {
        logGLFWerror("glfwInit failed :");
    }
    return initSuccess;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool SE_CGUIGLFW::openWindow()
{
    bool windowOpened = false;

    glfwWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

#ifdef SE_DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif // SE_DEBUG

    // only enable NON-deprecated features
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_OPENGL_ROBUSTNESS, GLFW_OPENGL_NO_ROBUSTNESS);

    m_GLFWWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
                                    GLFW_WINDOWED,
                                    "SpeakEasy" " - " GIT_INFORMATIONS " - built on " __DATE__ " " __TIME__,
                                    nullptr);

    if(m_GLFWWindow != nullptr)
    {
        windowOpened = true;

        // Make the context of the newly created window current
        glfwMakeContextCurrent(m_GLFWWindow);

        // Ensure that we can capture the escape key being pressed below
        glfwSetInputMode(m_GLFWWindow, GLFW_STICKY_KEYS, GL_TRUE);

        // Enable vertical sync (on cards that supports it)
        //glfwSwapInterval(1);

        // Disable vertical sync
        glfwSwapInterval(0);

        SE_CLogManager::getInstance()->log(kDebug, "OpenGL context version :", glGetString(GL_VERSION));
    }
    else
    {
        glfwTerminate();
        logGLFWerror("glfwCreateWindow failed :");
    }

    return windowOpened;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_CGUIGLFW::swapBuffers()
{
    glfwSwapBuffers(m_GLFWWindow);
    glfwPollEvents();
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool SE_CGUIGLFW::windowClosed() const
{
    bool const windowCloseRequested = glfwGetWindowParam(m_GLFWWindow, GLFW_CLOSE_REQUESTED) == GL_TRUE;
    if(windowCloseRequested)
    {
        SE_CLogManager::getInstance()->log(kInformation, "GLFW window has been closed");
    }
    return windowCloseRequested;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool SE_CGUIGLFW::close()
{
    if(m_GLFWWindow)
    {
        glfwDestroyWindow(m_GLFWWindow);
        m_GLFWWindow = nullptr;
    }
    glfwTerminate();
    return true;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool SE_CGUIGLFW::quitPressed() const
{
    // TODO only quit once escape is released ??
    bool shouldQuit = false;
    I32 const escapeKeyStatus = glfwGetKey(m_GLFWWindow, GLFW_KEY_ESCAPE);
    if(escapeKeyStatus == GLFW_PRESS)
    {
        shouldQuit = true;
        SE_CLogManager::getInstance()->log(kInformation, "GLFW window received escape key");
    }
    return shouldQuit;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_CGUIGLFW::logGLFWerror(char const * const inpDescriptionText) const
{
    I32 const errorCode = glfwGetError();
    SE_CLogManager::getInstance()->log(kError, inpDescriptionText, glfwErrorString(errorCode));
}
