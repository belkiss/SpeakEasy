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
#endif

#include "SE_Types.h"

class SE_CClock
{
    public:
        // Construct a clock
        explicit SE_CClock(F32 inStartTimeSeconds = 0.f) :
            m_timeCycles(secondsToCycles(inStartTimeSeconds)),
            m_timeScale(1.f),  // default to unscaled
            m_isPaused(false)  // default to running
        {
        }

        // Call this when the game first starts up
        static void init()
        {
        }

        // Return the current time in cycles. NOTE that we do not return
        // absolute time measurements in floating point seconds, because a
        // 32-bit float doesn't have enough precision. See calcDeltaSeconds()
        U64 getTimeCycles() const
        {
            return m_timeCycles;
        }

        // Determine the difference between this clock's absolute time and that
        // of another clock, in seconds. We only return time deltas as floating
        // point seconds, due to the precision limitations of a 32-bit float
        F32 calcDeltaSeconds(const SE_CClock &inOther)
        {
            U64 dt = m_timeCycles - inOther.m_timeCycles;
            return cyclesToSeconds(dt);
        }

        // This function should be called once per frame,
        // with the real measured frame time delta in seconds
        void update(F32 inDtRealSeconds)
        {
            if(!m_isPaused)
            {
                U64 dtScaledCycles = secondsToCycles(inDtRealSeconds * m_timeScale);

                m_timeCycles += dtScaledCycles;
            }
        }

        inline void setPaused(bool inPaused)
        {
            m_isPaused = inPaused;
        }

        inline bool isPaused() const
        {
            return m_isPaused;
        }

        inline void setTimeScale(F32 inScale)
        {
            m_timeScale = inScale;
        }

        inline F32 getTimeScale() const
        {
            return m_timeScale;
        }

        void singleStep()
        {
            if(m_isPaused)
            {
                // Add one ideal frame interval; don't forget
                // to scale it by our current time scale !
                U64 dtScaledCycles = secondsToCycles((1.f/30.f) * m_timeScale);

                m_timeCycles += dtScaledCycles;
            }
        }

    public: // static methods
        /**
         * @brief Reads the high resolution timer value from the CPU
         * @note Platform dependent
         * @todo Specify the core for multi cores
         *
         * @return I64 the timer frequency
        **/
        static std::chrono::system_clock::time_point readHiResTimer()
        {
            return std::chrono::high_resolution_clock::now();
        }

        /**
         * @brief Reads the frequency of the high resolution timer from the CPU
         * @note Platform dependent
         * @todo Specify the core for multi cores
         *
         * @return I64 the timer frequency
        **/
        static U64 readHiResTimerFrequency()
        {
            return 0;
        }

        /**
         * @brief Returns the stored frequency of the high resolution timer
         *
         * @return U64 the timer frequency
        **/
        static U64 getHiResTimerFrequency()
        {
            return ms_cyclesPerSecond;
        }

        static void localtimeToSStream(std::ostringstream &ioStringStream);

    private: // static methods
        static inline U64 secondsToCycles(F32 inTimeSeconds)
        {
            return (U64)(inTimeSeconds * ms_cyclesPerSecond);
        }

        // WARNING : Dangerous -- only use to convert small durations into seconds
        static inline F32 cyclesToSeconds(U64 inTimeCycles)
        {
            return (F32)inTimeCycles/ms_cyclesPerSecond;
        }

    private:
        U64  m_timeCycles;
        F32  m_timeScale;
        bool m_isPaused;
        U8   _pad[3]; // explicit padding

    private: // static members
        static F32 ms_cyclesPerSecond;
};

#endif  // SE_CCLOCK_H
