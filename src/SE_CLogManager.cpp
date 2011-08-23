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
 * \file    SE_CLogManager.cpp
 * \brief   Logging class
 *
 * \author  Lambert CLARA <lambert.clara@yahoo.fr>
 * \date    Created : 2011-8-21 22:52:31
 * \date    Updated : 2011-8-21 22:52:31
 */

#include "SE_CLogManager.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
SE_CLogManager::SE_CLogManager()
{
    // Do nothing
    log(ELL_DEBUG, "SE_CLogManager constructed");
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
SE_CLogManager::~SE_CLogManager()
{
    // Do nothing
    log(ELL_DEBUG, "SE_CLogManager destroyed");
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_CLogManager::startUp(const U8 inLogLevel)
{
    m_currentLogLevel = inLogLevel;
    log(ELL_DEBUG, "SE_CLogManager successfully started");
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_CLogManager::shutDown()
{
    log(ELL_DEBUG, "SE_CLogManager successfully shut downed");
}
