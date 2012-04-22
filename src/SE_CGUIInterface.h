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
 * @file    SE_CGUIInterface.h
 * @brief   Abstract class to wrap GUI libraries
 *
 * @author  Lambert Clara <lambert.clara@yahoo.fr>
 * @date    Created : 2011-08-23
 */

#ifndef SE_CGUIINTERFACE_H
#define SE_CGUIINTERFACE_H

class SE_CGUIInterface
{
    public:
        SE_CGUIInterface();
        virtual ~SE_CGUIInterface();

        virtual bool init();
        virtual bool openWindow();
        virtual void swapBuffers() = 0;
        virtual bool close();
};

#endif // SE_CGUIINTERFACE_H
