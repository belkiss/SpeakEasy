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
 * @file    SE_Types.h
 * @brief   Declare base types
 *
 * @author  Lambert Clara <lambert.clara@yahoo.fr>
 * @date    Created : 2011-08-19
 */

#pragma once

#include <cstdint>

/// @brief 32-bits IEEE-754 floating-point value
using F32 = float;

/// @brief 64-bits IEEE-754 floating-point value
using F64 = double;

/// @brief unsigned 8-bits integer
using U8 = uint8_t;

/// @brief signed 8-bits integer
using I8 = int8_t;

/// @brief unsigned 16-bits integer
using U16 = uint16_t;

/// @brief signed 16-bits integer
using I16 = int16_t;

/// @brief unsigned 32-bits integer
using U32 = uint32_t;

/// @brief signed 32-bits integer
using I32 = int32_t;

/// @brief unsigned 64-bits integer
using U64 = uint64_t;

/// @brief signed 64-bits integer
using I64 = int64_t;
