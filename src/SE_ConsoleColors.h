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
 * @file    SE_ConsoleColors.h
 * @brief   Helper class to allow colored output in terminal
 *
 * @author  Lambert Clara <lambert.clara@yahoo.fr>
 * @date    Created : 2012-04-22
 */

#pragma once

#ifdef WIN32

#include <iostream>
#include <windows.h>

enum Color
{
    Black       = 0,
    Grey        = FOREGROUND_INTENSITY,
    LightGrey   = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE,
    White       = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
    Blue        = FOREGROUND_BLUE,
    Green       = FOREGROUND_GREEN,
    Cyan        = FOREGROUND_GREEN | FOREGROUND_BLUE,
    Red         = FOREGROUND_RED,
    Purple      = FOREGROUND_RED   | FOREGROUND_BLUE,
    LightBlue   = FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
    LightGreen  = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    LightCyan   = FOREGROUND_GREEN | FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
    LightRed    = FOREGROUND_RED   | FOREGROUND_INTENSITY,
    LightPurple = FOREGROUND_RED   | FOREGROUND_BLUE  | FOREGROUND_INTENSITY,
    Orange      = FOREGROUND_RED   | FOREGROUND_GREEN,
    Yellow      = FOREGROUND_RED   | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
inline std::ostream& COL_BEGIN(std::ostream &ioStr)
{
    // only redirect the stream, needed for unix compatibility
    return ioStr;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
inline std::ostream& COL_END(std::ostream &ioStr)
{
    // only redirect the stream, needed for unix compatibility
    return ioStr;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
inline std::ostream& BLUE(std::ostream &ioStr)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute(hStdout, LightCyan);
    return ioStr;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
inline std::ostream& RED(std::ostream &ioStr)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute(hStdout, Red);
    return ioStr;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
inline std::ostream& GREEN(std::ostream &ioStr)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute(hStdout, LightGreen);
    return ioStr;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
inline std::ostream& ORANGE(std::ostream &ioStr)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute(hStdout, Orange);
    return ioStr;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
inline std::ostream& YELLOW(std::ostream &ioStr)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute(hStdout, Yellow);
    return ioStr;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
inline std::ostream& WHITE(std::ostream &ioStr)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute(hStdout, White);
    return ioStr;
}

#else
// colorized output defines
const std::string COL_BEGIN = "\33[";
const std::string COL_END   = "\33[m";

const std::string RED       = "0;31m";
const std::string BOLD_RED  = "1;31m";
const std::string ORANGE    = "0;32m";
const std::string GREEN     = "1;32m";
const std::string BROWN     = "0;33m";
const std::string YELLOW    = "1;33m";
const std::string BLUE      = "0;34m";
const std::string BOLD_BLUE = "1;34m";
const std::string PURPLE    = "0;35m";
const std::string PINK      = "1;35m";
const std::string CYAN      = "0;36m";
const std::string BOLD_CYAN = "1;36m";
const std::string GREY      = "0;37m";
const std::string WHITE     = "1;37m";
#endif
