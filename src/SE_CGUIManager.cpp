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
 * @file    SE_CGUIManager.cpp
 * @brief   2D GUI Manager
 *
 * @author  Lambert Clara <lambert.clara@yahoo.fr>
 * @date    Created : 2011-08-23
 */

#include "SE_CGUIManager.h"

#include "SE_CGUIGLFW.h"
#include "SE_CLogManager.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
SE_CGUIManager::SE_CGUIManager():
    m_pGUISystem(nullptr)
{
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_CGUIManager::startUp()
{
    SE_CLogManager::getInstance()->log(kInformation, "SE_CGUIManager successfully started");
    m_pGUISystem = new SE_CGUIGLFW();
    if(m_pGUISystem->init())
    {
        SE_CLogManager::getInstance()->log(kInformation, "GUI System successfully initialized");
        if(m_pGUISystem->openWindow())
        {
            SE_CLogManager::getInstance()->log(kInformation, "GUI System window successfully opened");
        }
    }
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_CGUIManager::shutDown()
{
    m_pGUISystem->close();
    delete m_pGUISystem;
    m_pGUISystem = nullptr;
    SE_CLogManager::getInstance()->log(kInformation, "SE_CGUIManager successfully shut downed");
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_CGUIManager::doWork()
{
    m_pGUISystem->swapBuffers();
}
