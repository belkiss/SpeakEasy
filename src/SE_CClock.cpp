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

#include <iomanip>
#include <sstream>

// define the static member
F32 SE_CClock::ms_cyclesPerSecond = 0.f;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_CClock::localtimeToSStream(std::ostringstream &ioStringStream)
{
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
}
