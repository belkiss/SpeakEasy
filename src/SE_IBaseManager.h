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
 * @file    SE_IBaseManager.h
 * @brief   Base interface for managers
 *
 * @author  Lambert Clara <lambert.clara@yahoo.fr>
 * @date    Created : 2012-06-09
 */

#ifndef SE_IBASEMANAGER_H
#define SE_IBASEMANAGER_H

class SE_IBaseManager
{
    public:
        SE_IBaseManager(){};
        virtual ~SE_IBaseManager(){};

        /// @TODO : make those methods return boolean status
        virtual void startUp()  = 0;
        virtual void shutDown() = 0;
};

#endif // SE_IBASEMANAGER_H
