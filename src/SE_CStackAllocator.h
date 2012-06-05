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
 * @file    SE_CStackAllocator.h
 * @brief   Stack Allocator class definition
 *
 * @author  Lambert Clara <lambert.clara@yahoo.fr>
 * @date    Created : 2011-08-19
 */

#ifndef SE_CSTACKALLOCATOR_H
#define SE_CSTACKALLOCATOR_H

#include "SE_Types.h"

class SE_CStackAllocator
{
    public:
        /**
         * @brief Stack marker: Represents the current top of the stack.
         *
         * You can only roll back to a marker, not to arbitrary locations within
         * the stack.
         **/
        typedef U64 Marker;

        /**
         * @brief Constructs a stack allocator with the given total size.
         *
         * @param inStackSizeInBytes the size in bytes
         **/
        explicit SE_CStackAllocator(const U32 inStackSizeInBytes);

        /**
         * @brief Destructor, no need for virtual
         *
         **/
        ~SE_CStackAllocator();

        /**
         * @brief Allocates a new block of the given size from stack top.
         *
         * @param inSizeInBytes the size in bytes
         * @return void*, the newly allocated block
         **/
        void* allocate(const U32 inSizeInBytes);

        /**
         * @brief Returns a marker to the current stack top.
         *
         * @return :Marker, the marker at the top
         **/
        Marker getMarker();

        /**
         * @brief Rolls the stack back to a previous marker.
         *
         * @param inMarker the marker we want
         **/
        void rewindToMarker(const Marker inMarker);

        /**
         * @brief Clears the entire stack (rolls the stack back to zero).
         **/
        void clear();

    private:
        Marker m_topMarker;
        Marker m_bottomMarker;
        Marker m_stackMemory;
};

#endif  // SE_CSTACKALLOCATOR_H
