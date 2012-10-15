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
 * \file    SE_CClock.h
 * \brief   class to handle time
 *
 * \author  Lambert Clara <lambert.clara@yahoo.fr>
 * \date    Created : 2011-08-19
 */

#ifndef SE_CCLOCK_H
#define SE_CCLOCK_H

#include <cassert>
#include <chrono> // TODO: wrap it with some ifdefs
#include <ctime>
#include <sstream>

#ifdef WIN32
#include <windows.h>
#endif // WIN32

#include "SE_Types.h"

extern F32 const g_IdealFrameTime;

/// @TODO use steady_clock to guarantee the clock to never be readjusted
class SE_CClock
{
    public:
        SE_CClock(void) :
            m_timeScale(1.f),
            m_delta(0.f),
            m_isPaused(true)
        {
        }

        ~SE_CClock() = default;

        void start()
        {
            m_isPaused = false;
            m_previousTimePoint = getNowTimePoint();
        }

        // This function should be called once per frame,
        // with the real measured frame time delta in seconds
        F32 update()
        {
            F32 delta = 0.f;
            if(!m_isPaused)
            {
                std::chrono::system_clock::time_point const nowTimePoint = getNowTimePoint();
                delta = (getDeltaInMs(m_previousTimePoint, nowTimePoint) * m_timeScale);
                m_previousTimePoint = nowTimePoint;
            }
            return delta;
        }

        /**
         * @brief Returns the time delta between begin and end in milliseconds
         *
         * @param inBegin older time point
         * @param inEnd earlier time point
         * @return F32 delta in ms
         **/
        inline static F32 getDeltaInMs(std::chrono::system_clock::time_point const &inBegin,
                                       std::chrono::system_clock::time_point const &inEnd)
        {
            return std::chrono::duration_cast<std::chrono::microseconds>(inEnd - inBegin).count()/1000.f;
        }

        inline void setPaused(bool const inPaused)
        {
            m_isPaused = inPaused;
        }

        inline bool isPaused() const
        {
            return m_isPaused;
        }

        inline void setTimeScale(F32 const inScale)
        {
            m_timeScale = inScale;
        }

        inline F32 getTimeScale() const
        {
            return m_timeScale;
        }

    public: // static methods
        static std::chrono::system_clock::time_point getNowTimePoint()
        {
            return std::chrono::high_resolution_clock::now();
        }

        static void localtimeToSStream(std::ostringstream &ioStringStream);

    private:
        std::chrono::system_clock::time_point m_previousTimePoint; // 8 bytes
        F32  m_timeScale;
        F32  m_delta;
        bool m_isPaused;
        char _pad[7];
};

#endif // SE_CCLOCK_H
