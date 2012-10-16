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
 * \file    SE_CClock.cpp
 * \brief   class to handle time
 *
 * \author  Lambert Clara <lambert.clara@yahoo.fr>
 * \date    Created : 2011-8-19
 */

#include "SE_CClock.h"

#include <ctime>
#include <iomanip>
#include <sstream>

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_CClock::localtimeToSStream(std::ostringstream &ioStringStream)
{
#ifdef WIN32
    SYSTEMTIME systemTime;
    GetLocalTime(&systemTime);

    // Format like this : YYYYMMDD_HH:MM:SS.MSS
    ioStringStream << std::setfill('0')
                   << systemTime.wYear
                   << std::setw(2) << systemTime.wMonth
                   << std::setw(2) << systemTime.wDay    << "_"
                   << std::setw(2) << systemTime.wHour   << ":"
                   << std::setw(2) << systemTime.wMinute << ":"
                   << std::setw(2) << systemTime.wSecond << "."
                   << std::setw(3)
                   << systemTime.wMilliseconds;
#else // WIN32
    std::chrono::steady_clock::time_point systemTime = std::chrono::steady_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(systemTime);
    std::tm *pCurrentTime = std::localtime(&currentTime);

    // Format like this : YYYY-MM-DD_HH:MM:SS
    ioStringStream << std::setfill('0')
                   << pCurrentTime->tm_year + 1900             << "-"
                   << std::setw(2) << pCurrentTime->tm_mon + 1 << "-"
                   << std::setw(2) << pCurrentTime->tm_mday    << "_"
                   << std::setw(2) << pCurrentTime->tm_hour    << ":"
                   << std::setw(2) << pCurrentTime->tm_min     << ":"
                   << std::setw(2) << pCurrentTime->tm_sec     << "."
                   << std::setw(3)
                   << std::chrono::duration_cast<std::chrono::milliseconds>(systemTime.time_since_epoch()).count() -
                      (1000*std::chrono::duration_cast<std::chrono::seconds>(systemTime.time_since_epoch()).count());
#endif // WIN32
}
