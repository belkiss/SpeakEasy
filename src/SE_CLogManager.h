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

#include "config.h"
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

/**
 * @brief This log management class MUST be used as singleton
 **/
class SE_CLogManager
{
    public:
        /**
         * @brief Creates a log manager that will output on the given stream
         *
         * @param inOutStream The wanted output stream, Defaults to std::clog.
         **/
        SE_CLogManager(std::ostream& inOutStream = std::clog);

        /**
         * @brief Destroys the log manager, no need for virtual
         *
         **/
        ~SE_CLogManager();

        /**
         * @brief Starts up the manager at the given log level
         *
         * @param inLogLevel The wanted log level
         * @return void
         **/
        void startUp(const U8 inLogLevel);

        void shutDown();

#ifdef VARIADIC_TEMPLATES_SUPPORTED
        /**
         * @brief Log something to the output stream
         *
         * @param inLevel The level of the log
         * @param inLogs The data to output
         * @return void
         **/
        template <typename... Types>
        void log(const U8 inLevel, const Types&... inLogs);

    private:
        template <typename T, typename... Args>
        void appendLogs(std::ostringstream &outStringStream, const T& inLog, const Args&... inLogs);

        inline void appendLogs(std::ostringstream &outStringStream);
#else
        void log(const U8 /*inLevel*/, ...)
        {

        }
#endif

    public: // static methods
        static SE_CLogManager* getInstance() {return m_pInstance;}

    private:
        std::ostream& m_outputStream;
        U8            m_currentLogLevel;

        // explicit padding
        U8 _pad[7];

    private: // static members
        static SE_CLogManager *m_pInstance;
};


#ifdef VARIADIC_TEMPLATES_SUPPORTED
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
#endif // VARIADIC_TEMPLATES_SUPPORTED

#endif // SE_CLOGMANAGER_H
