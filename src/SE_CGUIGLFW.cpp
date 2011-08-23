/*
 * This file is part of SpeakEasy.
 * Copyright (C) 2011  Lambert CLARA <lambert.clara@yahoo.fr>
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
 * \file    SE_CGUIGLFW.cpp
 * \brief   Wrapper for GLFW library
 *
 * \author  Lambert CLARA <lambert.clara@yahoo.fr>
 * \date    Created : 2011-8-23 21:35:09
 * \date    Updated : 2011-8-23 21:35:09
 */

#include "SE_CGUIGLFW.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
SE_CGUIGLFW::SE_CGUIGLFW()
{
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
SE_CGUIGLFW::~SE_CGUIGLFW()
{
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool SE_CGUIGLFW::init()
{
    return glfwInit();
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool SE_CGUIGLFW::openWindow()
{
    m_GLFWWindow = glfwOpenWindow(300, 300, GLFW_WINDOWED, "SpeakEasy", NULL);
    return m_GLFWWindow;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_CGUIGLFW::swapBuffers()
{
    glfwSwapBuffers();
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool SE_CGUIGLFW::close()
{
    glfwTerminate();
    return true;
}
