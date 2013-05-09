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

#include <csignal>
#include <cstdlib>
#include <thread>

#include "SE_CGUIManager.h"
#include "SE_CLogManager.h"
#include "SE_CMemoryManager.h"
#include "SE_CRenderManager.h"

#include "SE_CClock.h"

const U32 g_IdealFPS = 60;
const F32 g_IdealFrameTime = 1000.f/g_IdealFPS;

static bool gs_EngineRunning = true;

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
void signalHandler(const I32 inSignalCode)
{
	seLogDebug("Caught signal ", inSignalCode);
	gs_EngineRunning = false;
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

	// Setup signal catching
	struct sigaction currentAction;
	currentAction.sa_handler = signalHandler;
	sigaction(SIGINT, &currentAction, NULL);

    // Start up engine systems in the correct order, starting with log manager
    bool startUpSuccess = gs_LogManager.startUp(kDebug);
	seLogDebug("SE_DEBUG defined");

    // handle the command line arguments
    handleCommandLineArguments(inArgc, inpArgv);

    startUpSuccess = startUpSuccess && gs_MemoryManager.startUp();
    startUpSuccess = startUpSuccess && gs_GUIManager.startUp();
    startUpSuccess = startUpSuccess && gs_RenderManager.startUp();

    if(startUpSuccess)
    {
        // Start the main clock
        gs_MainClock.start();

		seLogDebug("SpeakEasy subsystems successfully started");

		U32 framesCount = 0;
		F32 timeSeconds = 0.f;
		while(gs_EngineRunning) // main game loop
        {
            F32 const deltaSeconds = gs_MainClock.update();
            {
                gs_RenderManager.render();
				++framesCount;
				gs_EngineRunning &= gs_GUIManager.doWork();
            }

            // Output FPS to command line
            timeSeconds += deltaSeconds;
			if(timeSeconds > 1000)
			{
				seLogDebug("FPS:", (1000*framesCount)/timeSeconds);
				timeSeconds = 0.f;
				framesCount = 0;
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
