/*
 * This file is part of SpeakEasy.
 * Copyright (C) 2011-2013 Lambert Clara <lambert.clara@yahoo.fr>
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
 * @file    SE_CGUIGLFW.h
 * @brief   Wrapper for GLFW library
 *
 * @author  Lambert Clara <lambert.clara@yahoo.fr>
 * @date    Created : 2011-08-23
 */

#ifndef SE_CGUIGLFW_H
#define SE_CGUIGLFW_H

#include "SE_CGUIInterface.h"
#include "SE_Types.h"

class SE_CGUIGLFW final : public SE_CGUIInterface
{
    public:
        SE_CGUIGLFW();
        ~SE_CGUIGLFW();

        bool init()         override;
        bool openWindow()   override;
        void swapBuffers()  override;
        bool windowClosed() const override;
        bool quitPressed()  const override;
        bool close()        override;

    private: // static methods
        static void logGLFWerror(I32 const          inErrorCode,
                                 char const * const inpDescriptionText);

    private:
        struct GLFWwindow *m_pGLFWWindow;
};

#endif // SE_CGUIGLFW_H
