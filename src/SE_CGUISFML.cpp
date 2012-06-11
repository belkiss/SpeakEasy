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
 * @file    SE_CGUISFML.cpp
 * @brief   Wrapper for SFML library
 *
 * @author  Lambert Clara <lambert.clara@yahoo.fr>
 * @date    Created : 2012-04-23
 */

#include "SE_CGUISFML.h"
#include "SE_CLogManager.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
SE_CGUISFML::SE_CGUISFML():
    m_pSFMLWindow(nullptr)
{
    SE_CLogManager::getInstance()->log(kInformation, "SE_CGUISFML constructed");
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
SE_CGUISFML::~SE_CGUISFML()
{
    SE_CLogManager::getInstance()->log(kInformation, "SE_CGUISFML destroyed");
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool SE_CGUISFML::init()
{
    return true;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool SE_CGUISFML::openWindow()
{
    m_pSFMLWindow = new sf::Window(sf::VideoMode(300, 300, 32),  // window dim (width, height, color_depth) in px
                                   "SpeakEasy",
                                   sf::Style::Default,
                                   sf::ContextSettings(32));
    return m_pSFMLWindow != nullptr;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_CGUISFML::swapBuffers()
{
    // Process events
    m_pSFMLWindow->pollEvent(m_event);

    // Finally, display the rendered frame on screen
    m_pSFMLWindow->display();
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool SE_CGUISFML::close()
{
    m_pSFMLWindow->close();
    delete m_pSFMLWindow;
    m_pSFMLWindow = nullptr;
    return true;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool SE_CGUISFML::quitPressed()
{
    return (m_event.type == sf::Event::KeyPressed) && (m_event.key.code == sf::Keyboard::Escape);
}
