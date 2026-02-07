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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include "../src/utils.h"

void test_lSwapLong_identity() {
    int32_t val = 0x12345678;
    int32_t res = lSwapLong(val, false);
    assert(res == val);
    printf("test_lSwapLong_identity passed\n");
}

void test_lSwapLong_swap() {
    int32_t val = 0x12345678;
    // 0x12345678. Low 16: 0x5678. High 16: 0x1234.
    // Swapped: High=0x5678, Low=0x1234.
    // Result: 0x56781234.
    int32_t expected = 0x56781234;
    int32_t res = lSwapLong(val, true);
    assert(res == expected);
    printf("test_lSwapLong_swap passed\n");
}

void test_lSwapLong_swap_negative() {
    int32_t val = -2; // 0xFFFFFFFE
    // Low: 0xFFFE, High: 0xFFFF
    // Swapped: High=0xFFFE, Low=0xFFFF -> 0xFFFEFFFF
    int32_t expected = (int32_t)0xFFFEFFFF;
    int32_t res = lSwapLong(val, true);
    assert(res == expected);
    printf("test_lSwapLong_swap_negative passed\n");
}

void test_fSwapFloat_identity() {
    float val = 1.2345f;
    float res = fSwapFloat(val, false);
    assert(res == val);
    printf("test_fSwapFloat_identity passed\n");
}

void test_fSwapFloat_swap() {
    float val = 1.0f;

    uint16_t parts[2];
    memcpy(parts, &val, 4);

    uint16_t swapped_parts[2];
    swapped_parts[0] = parts[1];
    swapped_parts[1] = parts[0];

    float expected;
    memcpy(&expected, swapped_parts, 4);

    float res = fSwapFloat(val, true);

    // Memcmp is safer for bitwise equality.
    assert(memcmp(&res, &expected, 4) == 0);
    printf("test_fSwapFloat_swap passed\n");
}

int main() {
    test_lSwapLong_identity();
    test_lSwapLong_swap();
    test_lSwapLong_swap_negative();
    test_fSwapFloat_identity();
    test_fSwapFloat_swap();
    printf("All tests passed!\n");
    return 0;
}
