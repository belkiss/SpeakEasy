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
 * \file    SE_CStackAllocator.cpp
 * \brief   Stack Allocator class implementation
 *
 * \author  Lambert CLARA <lambert.clara@yahoo.fr>
 * \date    Created : 2011-8-19 21:13:54
 * \date    Updated : 2011-8-19 21:13:54
 */


#include "SE_CStackAllocator.h"
#include <cstdlib>


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
SE_CStackAllocator::SE_CStackAllocator(const U32 inStackSizeInBytes)
{
    m_stackMemory = reinterpret_cast<Marker>(std::malloc(inStackSizeInBytes));
    m_topMarker = m_stackMemory;
    m_bottomMarker = m_stackMemory - inStackSizeInBytes;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
SE_CStackAllocator::~SE_CStackAllocator()
{
    free(reinterpret_cast<void*>(m_stackMemory));
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void* SE_CStackAllocator::allocate(const U32 inSizeInBytes)
{
    // get the topMarker position
    Marker position = m_topMarker;

    // move the top stack
    m_topMarker += inSizeInBytes;

    // return the address
    return reinterpret_cast<void*>(position);
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
SE_CStackAllocator::Marker SE_CStackAllocator::getMarker()
{
    return m_topMarker;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_CStackAllocator::rewindToMarker(const Marker inMarker)
{
    m_topMarker = inMarker;
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SE_CStackAllocator::clear()
{
    m_topMarker = m_bottomMarker;
}
