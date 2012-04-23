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
 * @file    SE_CLogManager.h
 * @brief   Logging class
 *
 * @author  Lambert Clara <lambert.clara@yahoo.fr>
 * @date    Created : 2011-08-21
 */

#ifndef SE_CLOGMANAGER_H
#define SE_CLOGMANAGER_H

#include <iostream>
#include <sstream>

#include "config.h"
#include "SE_CClock.h"
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
    public:
        /**
         * @brief Log something to the output stream
         *
         * @param inLevel The level of the log
         * @param inLogs The data to output
         **/
        template <typename... Types>
        void log(const U8 inLevel, const Types&... inLogs);

    private:
        template <typename T, typename... Args>
        void appendLogs(std::ostringstream &outStringStream, const T& inLog, const Args&... inLogs);

#else
    public:
        /**
         * @brief Log something to the output stream
         * @note We need as many functions as the max number of log data we want
         *
         * @param inLevel The level of the log
         * @param inLog The data to output
        **/
        template <typename T>
        void log(const U8 inLevel, const T &inLog);

        /**
         * @brief Log something to the output stream
         * @note We need as many functions as the max number of log data we want
         *
         * @param inLevel The level of the log
         * @param inLog1 First data to output
         * @param inLog2 Second data to output
        **/
        template <typename T, typename U>
        void log(const U8 inLevel, const T &inLog1, const U &inLog2);
#endif

    private:
        void logLevelToSStream(const U8 inLevel, std::ostringstream &ioStringStream);

        inline void appendLogs(std::ostringstream &outStringStream);

    public: // static methods
        static SE_CLogManager* getInstance() {return ms_pInstance;}

    private:
        std::ostream& m_outputStream;
        U8            m_currentLogLevel;

        // explicit padding
        U8 _pad[7];

    private: // static members
        static SE_CLogManager *ms_pInstance;
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
        logLevelToSStream(inLevel, displayStream);
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

#else // VARIADIC_TEMPLATES_SUPPORTED
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
template <typename T>
void SE_CLogManager::log(const U8 inLevel, const T &inLog)
{
    // kNone is 0
    if(!inLevel || inLevel >= m_currentLogLevel)
    {
        std::ostringstream displayStream;
        SE_CClock::localtimeToSStream(displayStream);
        displayStream << " ";
        logLevelToSStream(inLevel, displayStream);
        displayStream << " " << inLog;
        m_outputStream << displayStream.str() << std::endl;
    }
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
template <typename T, typename U>
void SE_CLogManager::log(const U8 inLevel, const T &inLog1, const U &inLog2)
{
    // kNone is 0
    if(!inLevel || inLevel >= m_currentLogLevel)
    {
        std::ostringstream displayStream;
        displayStream << inLog1 << " " << inLog2;
        log(inLevel, displayStream.str());
    }
}
#endif // VARIADIC_TEMPLATES_SUPPORTED

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
inline void SE_CLogManager::appendLogs(std::ostringstream &outStringStream)
{
    m_outputStream << outStringStream.str() << std::endl;
};


#endif // SE_CLOGMANAGER_H
