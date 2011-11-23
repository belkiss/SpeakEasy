/*
 * This file is part of SpeakEasy.
 * Copyright (C) 2011  Lambert CLARA <lambert.clara@yahoo.fr>
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
 * \file    SE_CGUIManager.h
 * \brief   2D GUI Manager
 *
 * \author  Lambert CLARA <lambert.clara@yahoo.fr>
 * \date    Created : 2011-8-23 21:20:16
 */

#ifndef SE_CGUIMANAGER_H
#define SE_CGUIMANAGER_H

class SE_CGUIInterface;
class SE_CGUIManager
{
    public:
        SE_CGUIManager();
        virtual ~SE_CGUIManager();

        void startUp();
        void shutDown();

        void doWork();

    private:
        SE_CGUIInterface *m_pGUISystem;
};

#endif // SE_CGUIMANAGER_H