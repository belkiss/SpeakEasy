/*
 * This file is part of SpeakEasy.
 * Copyright (C) 2011  Lambert Clara <lambert.clara@yahoo.fr>
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
 * @mainpage SpeakEasy documentation
 * @file    main.cpp
 * @brief   SpeakEasy main
 *
 * @author  Lambert Clara <lambert.clara@yahoo.fr>
 * @date    Created : 2011-08-19
 */

#include <cstdlib>

#include "SE_CGUIManager.h"
#include "SE_CLogManager.h"
#include "SE_CMemoryManager.h"

#include "SE_CClock.h"

static SE_CLogManager      gs_LogManager;
static SE_CMemoryManager   gs_MemoryManager;
static SE_CGUIManager      gs_GUIManager;

int main()
{
    SE_CClock::init();

    // Prime the pump by reading the current time
    U64 tBegin = SE_CClock::readHiResTimer();

    // Start up engine systems in the correct order
    gs_LogManager.startUp(kDebug);
    gs_MemoryManager.startUp();
    gs_GUIManager.startUp();

    while(true) // main game loop
    {
        gs_GUIManager.doWork();
        // Read the current time again, and calculate the delta
        U64 tEnd = SE_CClock::readHiResTimer();

        SE_CLogManager::getInstance()->log(kDebug, (F32)SE_CClock::getHiResTimerFrequency()/(F32)(tEnd - tBegin));

        // Use tEnd as the new tBegin for the next frame
        tBegin = tEnd;
    }

    // Shut everything down, in reverse order
    gs_GUIManager.shutDown();
    gs_MemoryManager.shutDown();
    gs_LogManager.shutDown();

    return EXIT_SUCCESS;
}
