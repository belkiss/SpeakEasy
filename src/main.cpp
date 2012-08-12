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
 * @mainpage SpeakEasy documentation
 * @file    main.cpp
 * @brief   SpeakEasy main
 *
 * @author  Lambert Clara <lambert.clara@yahoo.fr>
 * @date    Created : 2011-08-19
 */

// activate debug console output on WIN32 and debug target
#if defined(WIN32) && ! defined(NDEBUG)
#    pragma comment(linker, "/SUBSYSTEM:CONSOLE")
#endif

#include <cstdlib>
#include <thread>

#include "SE_CGUIManager.h"
#include "SE_CLogManager.h"
#include "SE_CMemoryManager.h"
#include "SE_CRenderManager.h"

#include "SE_CClock.h"

static SE_CLogManager      gs_LogManager;
static SE_CMemoryManager   gs_MemoryManager;
static SE_CGUIManager      gs_GUIManager;
static SE_CRenderManager   gs_RenderManager;

// AudioManager
// InputManager
// ErrorManager
// ResourceManager
// PhysicsManager
// SceneManager


int main()
{
#ifdef WIN32
    // get the arguments usually set by WinMain
    HINSTANCE const hInstance = GetModuleHandle(nullptr);
    int const       nCmdShow  = SW_SHOWDEFAULT; // TODO: remove the apparent usage.
    (void)hInstance;
    (void)nCmdShow;
#endif

    SE_CClock::init();

    // Prime the pump by reading the current time
    std::chrono::system_clock::time_point tBegin = SE_CClock::readHiResTimer();
    std::chrono::system_clock::time_point tEnd   = tBegin;

    // Start up engine systems in the correct order
    gs_LogManager.startUp(kDebug);
    gs_MemoryManager.startUp();
    gs_GUIManager.startUp();
    gs_RenderManager.startUp();

    SE_CLogManager::getInstance()->log(kDebug, "SpeakEasy subsystems successfully started");
#ifdef SE_DEBUG
    SE_CLogManager::getInstance()->log(kDebug, "SE_DEBUG defined");
#endif

    F32 elapsedTime = 0.f;

    bool keepRunning = true;
    while(keepRunning) // main game loop
    {
        // Read the current time again, and calculate the delta
        tEnd = SE_CClock::readHiResTimer();

        const F32 deltaMs = std::chrono::duration_cast<std::chrono::microseconds>(tEnd - tBegin).count()/1000.f;
        if(deltaMs >= 1000.f/60)
        {
            SE_CLogManager::getInstance()->log(kDebug, deltaMs, " ms");

            elapsedTime += deltaMs;

            gs_RenderManager.render(elapsedTime);
            keepRunning = gs_GUIManager.doWork();

            // Use tEnd as the new tBegin for the next frame
            tBegin = tEnd;
        }
    }

    SE_CLogManager::getInstance()->log(kDebug, "Exiting...");

    // Shut everything down, in reverse order
    gs_RenderManager.shutDown();
    gs_GUIManager.shutDown();
    gs_MemoryManager.shutDown();
    gs_LogManager.shutDown();

    return EXIT_SUCCESS;
}
