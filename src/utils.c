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

#include <string.h>
#include "utils.h"

int32_t lSwapLong(int32_t l, bool bIsBigEndian) {
    if (!bIsBigEndian) {
        return l;
    }
    int32_t ret;
    uint16_t tmp[2];
    uint16_t swapped[2];

    memcpy(tmp, &l, sizeof(l));

    swapped[0] = tmp[1];
    swapped[1] = tmp[0];

    memcpy(&ret, swapped, sizeof(ret));
    return ret;
}

float fSwapFloat(float f, bool bIsBigEndian) {
    if (!bIsBigEndian) {
        return f;
    }
    float ret;
    uint16_t tmp[2];
    uint16_t swapped[2];

    memcpy(tmp, &f, sizeof(f));

    swapped[0] = tmp[1];
    swapped[1] = tmp[0];

    memcpy(&ret, swapped, sizeof(ret));
    return ret;
}
