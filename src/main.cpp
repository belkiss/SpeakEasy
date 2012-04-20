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
 * @date    Created : 2011-8-19 21:14:47
 */

#include <cstdlib>

#include "SE_CGUIManager.h"
#include "SE_CLogManager.h"
#include "SE_CMemoryManager.h"

static SE_CLogManager      g_LogManager;
static SE_CMemoryManager   g_MemoryManager;
static SE_CGUIManager      g_GUIManager;

int main()
{
    // Start up engine systems in the correct order
    g_LogManager.startUp(kDebug);
    g_MemoryManager.startUp();
    g_GUIManager.startUp();

    unsigned int i = 10000;
    while(--i)
    {
        g_GUIManager.doWork();
    }

    // Shut everything down, in reverse order
    g_GUIManager.shutDown();
    g_MemoryManager.shutDown();
    g_LogManager.shutDown();

    return EXIT_SUCCESS;
}
