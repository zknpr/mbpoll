#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "../src/utils.h"

void test_fSwapFloat() {
    float f_in = 1.0f; // 0x3F800000 on IEEE 754 Big Endian, or 00 00 80 3F on Little Endian

    // Case 1: No Swap
    float f_res = fSwapFloat(f_in, false);
    assert(f_res == f_in);

    // Case 2: Swap
    // We expect the 16-bit words of the float representation to be swapped.
    // e.g., if f_in is [A, B, C, D] (bytes), where (A,B) is word 0 and (C,D) is word 1
    // result should be [C, D, A, B] (assuming consistent endianness within words)
    // Actually, it swaps uint16_t words.

    uint16_t in_w[2];
    uint16_t out_w[2];

    memcpy(in_w, &f_in, sizeof(float));

    f_res = fSwapFloat(f_in, true);

    memcpy(out_w, &f_res, sizeof(float));

    // Check that words are swapped
    if (out_w[0] != in_w[1] || out_w[1] != in_w[0]) {
        fprintf(stderr, "fSwapFloat failed!\n");
        fprintf(stderr, "In:  %04X %04X\n", in_w[0], in_w[1]);
        fprintf(stderr, "Out: %04X %04X\n", out_w[0], out_w[1]);
        assert(0);
    }

    printf("test_fSwapFloat passed.\n");
}

void test_lSwapLong() {
    int32_t l_in = 0x12345678;

    // Case 1: No Swap
    int32_t l_res = lSwapLong(l_in, false);
    assert(l_res == l_in);

    // Case 2: Swap
    l_res = lSwapLong(l_in, true);

    uint16_t in_w[2];
    uint16_t out_w[2];

    memcpy(in_w, &l_in, sizeof(int32_t));
    memcpy(out_w, &l_res, sizeof(int32_t));

    // Check that words are swapped
    if (out_w[0] != in_w[1] || out_w[1] != in_w[0]) {
        fprintf(stderr, "lSwapLong failed!\n");
        fprintf(stderr, "In:  %04X %04X\n", in_w[0], in_w[1]);
        fprintf(stderr, "Out: %04X %04X\n", out_w[0], out_w[1]);
        assert(0);
    }

    printf("test_lSwapLong passed.\n");
}

int main() {
    test_fSwapFloat();
    test_lSwapLong();
    return 0;
}
