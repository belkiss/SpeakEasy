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
#include "SE_CLogManager.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
SE_CGUIGLFW::SE_CGUIGLFW()
{
    SE_CLogManager::getInstance()->log(kInformation, "SE_CGUIGLFW constructed");
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
SE_CGUIGLFW::~SE_CGUIGLFW()
{
    SE_CLogManager::getInstance()->log(kInformation, "SE_CGUIGLFW destroyed");
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool SE_CGUIGLFW::init()
{
    I32 initStatus = glfwInit();
    SE_CLogManager::getInstance()->log(kDebug, "initializing glfw version ", glfwGetVersionString());
    return initStatus == GL_TRUE;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool SE_CGUIGLFW::openWindow()
{
    m_GLFWWindow = glfwOpenWindow(300, 300, // window dimensions (width, height) in pixels
                                  GLFW_WINDOWED,
                                  "SpeakEasy",
                                  nullptr);

    // Ensure that we can capture the escape key being pressed below
    glfwSetInputMode(m_GLFWWindow, GLFW_STICKY_KEYS, GL_TRUE);

    // Enable vertical sync (on cards that supports it)
    //glfwSwapInterval(1);

    // Disable vertical sync
    glfwSwapInterval(0);

    return m_GLFWWindow != nullptr;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_CGUIGLFW::swapBuffers()
{
    glfwSwapBuffers();
    glfwPollEvents();
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool SE_CGUIGLFW::close()
{
    glfwTerminate();
    return true;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool SE_CGUIGLFW::quitPressed()
{
    SE_CLogManager::getInstance()->log(kDebug, "glfwGetKey(m_GLFWWindow, GLFW_KEY_ESCAPE) => ", glfwGetKey(m_GLFWWindow, GLFW_KEY_ESCAPE));
    return glfwGetKey(m_GLFWWindow, GLFW_KEY_ESCAPE);
}
