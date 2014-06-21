/*
 * This file is part of SpeakEasy.
 * Copyright (C) 2011-2014 Lambert Clara <lambert.clara@yahoo.fr>
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

#pragma once

#include <chrono>
#include <iosfwd>

#ifdef WIN32
#   include <windows.h>
#endif // WIN32

extern F32 const g_IdealFrameTime;

class SE_CClock
{
    using ChronoClock = std::chrono::high_resolution_clock;
    public:
        explicit SE_CClock();
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
                std::chrono::time_point<ChronoClock> const nowTimePoint =
                    getNowTimePoint();
                delta = getDeltaInMs(m_previousTimePoint, nowTimePoint) * m_timeScale;
                m_previousTimePoint = nowTimePoint;
            }
            return delta;
        }

        /// @brief Returns the time delta between begin and end in milliseconds
        /// @param inBegin older time point
        /// @param inEnd earlier time point
        /// @return F32 delta in ms
        static F32 getDeltaInMs(
            std::chrono::time_point<ChronoClock> const &inBegin,
            std::chrono::time_point<ChronoClock> const &inEnd
        )
        {
            return std::chrono::duration_cast<std::chrono::microseconds>(inEnd - inBegin).count()/1000.f;
        }

        void setPaused   (bool const inPaused) {m_isPaused = inPaused;}
        void setTimeScale(F32  const inScale)  {m_timeScale = inScale;}

        bool isPaused()     const {return m_isPaused;}
        F32  getTimeScale() const {return m_timeScale;}

    public: // static methods
        static std::chrono::time_point<ChronoClock> getNowTimePoint()
        {
            return ChronoClock::now();
        }

        static void localtimeToSStream(std::ostringstream &ioStringStream);

    private:
        std::chrono::time_point<ChronoClock> m_previousTimePoint; // 8 bytes
        F32  m_timeScale;
        bool m_isPaused;
        U8 _pad[3];
};
