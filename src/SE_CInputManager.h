/*
 * This file is part of SpeakEasy.
 * Copyright (C) 2012  Lambert Clara <lambert.clara@yahoo.fr>
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
 * @file    SE_CInputManager.h
 * @brief   Input devices manager
 *
 * @author  Lambert Clara <lambert.clara@yahoo.fr>
 * @date    Created : 2012-04-23
 */

#ifndef SE_CINPUTMANAGER_H
#define SE_CINPUTMANAGER_H

#include "SE_IBaseManager.h"

class SE_CInputManager : public SE_IBaseManager
{
    public:
        explicit SE_CInputManager();
        ~SE_CInputManager();

        void startUp()  override;
        void shutDown() override;
};

#endif // SE_CINPUTMANAGER_H

