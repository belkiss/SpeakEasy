/*
 * This file is part of SpeakEasy.
 * Copyright (C) 2011-2012  Lambert CLARA <lambert.clara@yahoo.fr>
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
 * \file    SE_CGUIGLFW.h
 * \brief   Wrapper for GLFW library
 *
 * \author  Lambert CLARA <lambert.clara@yahoo.fr>
 * \date    Created : 2011-8-23 21:34:52
 */

#ifndef SE_CGUIGLFW_H
#define SE_CGUIGLFW_H

#include <GL/glfw3.h>

#include "SE_CGUIInterface.h"

class SE_CGUIGLFW : public SE_CGUIInterface
{
    public:
        SE_CGUIGLFW();
        ~SE_CGUIGLFW();

        bool init();
        bool openWindow();
        void swapBuffers();
        bool close();

    private:
        GLFWwindow m_GLFWWindow;
};

#endif // SE_CGUIGLFW_H
