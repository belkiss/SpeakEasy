/*
 * This file is part of SpeakEasy.
 * Copyright (C) 2011-2013  Lambert Clara <lambert.clara@yahoo.fr>
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
#endif // WIN32 && !NDEBUG

#include <cstdlib>
#include <thread>

#include "SE_CGUIManager.h"
#include "SE_CLogManager.h"
#include "SE_CMemoryManager.h"
#include "SE_CRenderManager.h"

#include "SE_CClock.h"

const U32 g_IdealFPS = 60;
const F32 g_IdealFrameTime = 1000.f/g_IdealFPS;

static SE_CLogManager      gs_LogManager;
static SE_CMemoryManager   gs_MemoryManager;
static SE_CGUIManager      gs_GUIManager;
static SE_CRenderManager   gs_RenderManager;

static SE_CClock           gs_MainClock;

// AudioManager
// InputManager
// ErrorManager
// ResourceManager
// PhysicsManager
// SceneManager

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void handleCommandLineArguments(I32 const inArgc,
								const char * const * const inpArgv)
{
    for(I32 i = 0; i < inArgc; ++i)
    {
		seLogDebug("inpArgv[", i, "] = ", inpArgv[i]);
    }
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
I32 main(I32 const inArgc,
         char const * const * const inpArgv)
{
#ifdef WIN32
    // get the arguments usually set by WinMain
    HINSTANCE const hInstance = GetModuleHandle(nullptr);
    int const       nCmdShow  = SW_SHOWDEFAULT;
    (void)hInstance;
    (void)nCmdShow;
#endif // WIN32

    // Start up engine systems in the correct order, starting with log manager
    bool startUpSuccess = gs_LogManager.startUp(kDebug);

    // handle the command line arguments
    handleCommandLineArguments(inArgc, inpArgv);

    startUpSuccess = startUpSuccess && gs_MemoryManager.startUp();
    startUpSuccess = startUpSuccess && gs_GUIManager.startUp();
    startUpSuccess = startUpSuccess && gs_RenderManager.startUp();

    if(startUpSuccess)
    {
        // Start the main clock
        gs_MainClock.start();

		seLogDebug("SpeakEasy subsystems successfully started"
        );
#ifdef SE_DEBUG
		seLogDebug("SE_DEBUG defined");
#endif // SE_DEBUG

        bool keepRunning = true;
        while(keepRunning) // main game loop
        {
            F32 const deltaSeconds = gs_MainClock.update()/1000;
            {
                gs_RenderManager.render(deltaSeconds);
                keepRunning = gs_GUIManager.doWork();
            }
        }
    }
    else
    {
		seLogDebug("SpeakEasy subsystems failed to start");
    }

    seLogDebug("Exiting...");

    // Shut everything down, in reverse order
    bool shutDownSuccess = gs_RenderManager.shutDown();
    shutDownSuccess &= gs_GUIManager.shutDown();
    shutDownSuccess &= gs_MemoryManager.shutDown();
    shutDownSuccess &= gs_LogManager.shutDown();

    return shutDownSuccess ? EXIT_SUCCESS : EXIT_FAILURE;
}
