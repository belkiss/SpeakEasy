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
#include "SE_Types.h"

//! Possible log levels.
//! When used has filter ELL_DEBUG means => log everything and ELL_NONE means => log (nearly) nothing.
//! When used to print logging information ELL_DEBUG will have lowest priority while ELL_NONE
//! messages are never filtered and always printed.
enum ELOG_LEVEL
{
    //! Used for printing information helpful in debugging
    ELL_DEBUG,

    //! Useful information to print. For example hardware infos or something started/stopped.
    ELL_INFORMATION,

    //! Warnings that something isn't as expected and can cause oddities
    ELL_WARNING,

    //! Something did go wrong.
    ELL_ERROR,

    //! Logs with ELL_NONE will never be filtered.
    //! And used as filter it will remove all logging except ELL_NONE messages.
    ELL_NONE
};

class SE_CLogManager
{
    public:
        SE_CLogManager();
        virtual ~SE_CLogManager();

        void startUp(const U8 inLogLevel);
        void shutDown();

        template <class T>
        void log(const U8 inLevel, const T &inLog);

    private:
        U8 m_currentLogLevel;

        // explicit padding
        U8 _pad[3];
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
template <class T>
void SE_CLogManager::log(const U8 inLevel, const T &inLog)
{
    if(inLevel <= m_currentLogLevel)
    {
        std::cout << (int)inLevel << ": " << inLog << std::endl;
    }
}

#endif // SE_CLOGMANAGER_H
