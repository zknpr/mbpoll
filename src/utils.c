#include "utils.h"
#include <string.h>

float fSwapFloat(float f, bool bSwap) {
    if (!bSwap) {
        return f;
    }

    float ret;
    uint16_t in[2];
    uint16_t out[2];

    memcpy(in, &f, sizeof(float));
    out[0] = in[1];
    out[1] = in[0];
    memcpy(&ret, out, sizeof(float));

    return ret;
}

int32_t lSwapLong(int32_t l, bool bSwap) {
    if (!bSwap) {
        return l;
    }

    int32_t ret;
    uint16_t in[2];
    uint16_t out[2];

    memcpy(in, &l, sizeof(int32_t));
    out[0] = in[1];
    out[1] = in[0];
    memcpy(&ret, out, sizeof(int32_t));

    return ret;
}
