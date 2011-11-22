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
 * \file    SE_CMemoryManager.cpp
 * \brief   Memory manager
 *
 * \author  Lambert CLARA <lambert.clara@yahoo.fr>
 * \date    Created : 2011-8-22 01:21:19
 */

#include "SE_CMemoryManager.h"
#include "SE_CLogManager.h"

extern SE_CLogManager g_LogManager;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
SE_CMemoryManager::SE_CMemoryManager()
{
    g_LogManager.log(ELL_DEBUG, "SE_CMemoryManager constructed");
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
SE_CMemoryManager::~SE_CMemoryManager()
{
    g_LogManager.log(ELL_DEBUG, "SE_CMemoryManager destroyed");
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_CMemoryManager::startUp()
{
    g_LogManager.log(ELL_DEBUG, "SE_CMemoryManager successfully started");
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_CMemoryManager::shutDown()
{
    g_LogManager.log(ELL_DEBUG, "SE_CMemoryManager successfully shut downed");
}
