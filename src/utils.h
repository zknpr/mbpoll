/* Copyright (c) 2015-2025 Pascal JEAN, All rights reserved.
 *
 * mbpoll is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * mbpoll is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with mbpoll.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _MBPOLL_UTILS_H_
#define _MBPOLL_UTILS_H_

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Swaps the two 16-bit words of a 32-bit integer if big endian flag is set.
 *
 * @param l The 32-bit integer to process.
 * @param bIsBigEndian If true, the two 16-bit halves are swapped.
 * @return The processed 32-bit integer.
 */
int32_t lSwapLong(int32_t l, bool bIsBigEndian);

/**
 * @brief Swaps the two 16-bit words of a 32-bit float if big endian flag is set.
 *
 * @param f The float to process.
 * @param bIsBigEndian If true, the two 16-bit halves are swapped.
 * @return The processed float.
 */
float fSwapFloat(float f, bool bIsBigEndian);

#endif /* _MBPOLL_UTILS_H_ */
