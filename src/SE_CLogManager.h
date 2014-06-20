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
 * @file    SE_CLogManager.h
 * @brief   Logging class
 *
 * @author  Lambert Clara <lambert.clara@yahoo.fr>
 * @date    Created : 2011-08-21
 */

#pragma once

#include <iostream>
#include <sstream>

#include "config.h"
#include "SE_IBaseManager.h"
#include "SE_CClock.h"

////////////////////////////////////////////////////////////////////////////////
// Useful macros
//
#if defined(SE_DEBUG)
#   define seLogDebug(...)   SE_CLogManager::getInstance()->log(ELogLevel::kDebug,       __VA_ARGS__)
#   define seLogInfo(...)    SE_CLogManager::getInstance()->log(ELogLevel::kInformation, __VA_ARGS__)
#   define seLogWarning(...) SE_CLogManager::getInstance()->log(ELogLevel::kWarning,     __VA_ARGS__)
#   define seLogError(...)   SE_CLogManager::getInstance()->log(ELogLevel::kError,       __VA_ARGS__)
#   define seAssert(inCondition, ...) \
        do \
        { \
            if(!(inCondition)) \
            { \
                seLogError(__FILE__":", __LINE__); \
                seLogError("Assert ! (" #inCondition ") failed"); \
                seLogError(__VA_ARGS__); \
            } \
        } \
        while(0)
#else
#   define seLogDebug(...)
#   define seLogInfo(...)
#   define seLogWarning(...)
#   define seLogError(...)
#   define seAssert(inCondition) do{sizeof(inCondition);}while(0)
#endif // SE_DEBUG
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Log levels
 **/
enum class ELogLevel : U8
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
class SE_CLogManager : public SE_IBaseManager
{
    public:
        /**
         * @brief Creates a log manager that will output on the given stream
         *
         * @param inOutStream The wanted output stream, Defaults to std::clog.
         **/
        explicit SE_CLogManager(std::ostream &inOutStream = std::clog);

        /**
         * @brief Destroys the log manager, no need for virtual
         *
         **/
        ~SE_CLogManager();

        /**
         * @brief Starts up the manager at the given log level
         * @note The inherited method (without the parameter) is private
         *
         * @param inLogLevel The wanted log level
         **/
        bool startUp(const ELogLevel inLogLevel);

        bool shutDown() override;

    public:
        /**
         * @brief Log something to the output stream
         *
         * @param inLevel The level of the log
         * @param inLogs The data to output
         **/
        template <typename... Types>
        void log(const ELogLevel inLevel, const Types&... inLogs);

    private:
        template <typename T, typename... Args>
        void appendLogs(std::ostringstream &outStringStream, const T &inLog, const Args&... inLogs);

    private:
        void logLevelToSStream(const ELogLevel inLevel, std::ostringstream &ioStringStream);

        // inherited startUp method, leave it empty
        bool startUp() override {return true;}

        inline void appendLogs(std::ostringstream &outStringStream);

    public: // static methods
        static SE_CLogManager* getInstance() {return ms_pInstance;}

    private:
        std::ostream& m_outputStream;
        ELogLevel     m_currentLogLevel;

        // explicit padding
        U8 _pad[7];

    private: // static members
        static SE_CLogManager *ms_pInstance;
};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
template <typename... Types>
void SE_CLogManager::log(const ELogLevel inLevel, const Types&... inLogs)
{
    // kNone is 0
    if(!inLevel || inLevel >= m_currentLogLevel)
    {
        std::ostringstream displayStream;
        SE_CClock::localtimeToSStream(displayStream);
        logLevelToSStream(inLevel, displayStream);
        appendLogs(displayStream, inLogs...);
    }
};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
template <typename T, typename... Args>
void SE_CLogManager::appendLogs(std::ostringstream &outStringStream,
                                const T &inLog,
                                const Args&... inLogs)
{
    outStringStream << inLog;
    appendLogs(outStringStream, inLogs...);
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
inline void SE_CLogManager::appendLogs(std::ostringstream &outStringStream)
{
    m_outputStream << outStringStream.str() << std::endl;
};
