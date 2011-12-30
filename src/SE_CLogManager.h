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
 * \file    SE_CLogManager.h
 * \brief   Logging class
 *
 * \author  Lambert CLARA <lambert.clara@yahoo.fr>
 * \date    Created : 2011-8-21 22:52:05
 */

#ifndef SE_CLOGMANAGER_H
#define SE_CLOGMANAGER_H

#include <iostream>
#include <sstream>

#include "SE_Types.h"

/**
 * @brief Log levels
 **/
enum ELogLevels
{
    /// No category, always displayed
    kNone,

    /// Used for printing information helpful in debugging
    kDebug,

    /// Useful information to print. For example hardware infos or something started/stopped.
    kInformation,

    /// Warnings that something isn't as expected and can cause oddities
    kWarning,

    /// Something did go wrong.
    kError
};

class SE_CLogManager
{
    public:
        SE_CLogManager(std::ostream& inOutStream = std::clog);
        virtual ~SE_CLogManager();

        void startUp(const U8 inLogLevel);
        void shutDown();

        template <typename... Types>
        void log(const U8 inLevel, const Types&... inLogs);

    private:
        template <typename T, typename... Args>
        void appendLogs(std::ostringstream &outStringStream, const T& inLog, const Args&... inLogs);

        inline void appendLogs(std::ostringstream &outStringStream);


    private:
        std::ostream& m_outputStream;
        U8            m_currentLogLevel;

        // explicit padding
        U8 _pad[7];
};



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
template <typename... Types>
void SE_CLogManager::log(const U8 inLevel, const Types&... inLogs)
{
    // kNone is 0
    if(!inLevel || inLevel >= m_currentLogLevel)
    {
        std::ostringstream displayStream;
        switch(inLevel)
        {
            case kNone:
                {
                    displayStream << "   kNone    ";
                }
                break;
            case kDebug:
                {
                    displayStream << "   kDebug   ";
                }
                break;
            case kInformation:
                {
                    displayStream << "kInformation";
                }
                break;
            case kWarning:
                {
                    displayStream << "  kWarning  ";
                }
                break;
            case kError:
                {
                    displayStream << "   kError   ";
                }
                break;
            default:
                {
                    displayStream << "  Unknown ! ";
                }
                break;
        }
        appendLogs(displayStream, inLogs...);
    }
};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
template <typename T, typename... Args>
void SE_CLogManager::appendLogs(std::ostringstream &outStringStream,
                                const T& inLog,
                                const Args&... inLogs)
{
    outStringStream << " " << inLog;
    appendLogs(outStringStream, inLogs...);
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
inline void SE_CLogManager::appendLogs(std::ostringstream &outStringStream)
{
    m_outputStream << outStringStream.str() << std::endl;
};

#endif // SE_CLOGMANAGER_H
