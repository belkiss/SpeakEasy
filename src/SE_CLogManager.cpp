/*
 * This file is part of SpeakEasy.
 * Copyright (C) 2011-2014  Lambert Clara <lambert.clara@yahoo.fr>
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
 * @file    SE_CLogManager.cpp
 * @brief   Logging class
 *
 * @author  Lambert Clara <lambert.clara@yahoo.fr>
 * @date    Created : 2011-08-21
 */

#include "SE_CLogManager.h"

#include "SE_ConsoleColors.h"

#include <cassert>

// define the static member
SE_CLogManager *SE_CLogManager::ms_pInstance = nullptr;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
SE_CLogManager::SE_CLogManager(std::ostream &inOutStream):
    m_outputStream(inOutStream)
{
    // because this class is meant to be used as singleton,
    // m_pInstance MUST be nullptr here
    assert(!ms_pInstance);

    // set the static instance to this
    ms_pInstance = this;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
SE_CLogManager::~SE_CLogManager()
{
    ms_pInstance = nullptr;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool SE_CLogManager::startUp(const ELogLevel inLogLevel)
{
    m_currentLogLevel = inLogLevel;
    seLogInfo("SE_CLogManager successfully started with logLevel set to ",
              static_cast<U32>(inLogLevel));
    m_initSuccess = true;
    return m_initSuccess;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool SE_CLogManager::shutDown()
{
    seLogInfo("SE_CLogManager successfully shut downed");
    return true;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_CLogManager::logLevelToSStream(const ELogLevel inLevel,
                                       std::ostringstream &ioStringStream)
{
    ioStringStream << COL_BEGIN;
    switch(inLevel)
    {
        case ELogLevel::None:        ioStringStream << WHITE  << "  NONE   "; break;
        case ELogLevel::Debug:       ioStringStream << BLUE   << "  DEBUG  "; break;
        case ELogLevel::Information: ioStringStream << GREEN  << "  INFO   "; break;
        case ELogLevel::Warning:     ioStringStream << YELLOW << " WARNING "; break;
        case ELogLevel::Error:       ioStringStream << RED    << "  ERROR  "; break;
#ifndef __clang__
        // prevent clang to emit a warning when all enum values are covered
        // but a default case is also present
        default:           ioStringStream << WHITE  << "   Unknown !  "; break;
#endif // ifndef __clang__
    }
    ioStringStream << COL_END;
}

