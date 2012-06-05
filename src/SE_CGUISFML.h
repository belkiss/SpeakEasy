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
 * @file    SE_CGUISFML.h
 * @brief   Wrapper for SFML library
 *
 * @author  Lambert Clara <lambert.clara@yahoo.fr>
 * @date    Created : 2012-04-23
 */

#ifndef SE_CGUISFML_H
#define SE_CGUISFML_H

#include "config.h"

#include <SFML/Window.hpp>
#include "SE_CGUIInterface.h"

class SE_CGUISFML : public SE_CGUIInterface
{
    public:
        SE_CGUISFML();
        ~SE_CGUISFML();

        bool init();
        bool openWindow();
        bool quitPressed();
        void swapBuffers();
        bool close();

        sf::Window *m_pSFMLWindow;
        sf::Event   m_event;
};

#endif // SE_CGUISFML_H
