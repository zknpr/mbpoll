#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Swaps the two 16-bit words of a 32-bit float if bSwap is true.
 * @param f The input float.
 * @param bSwap If true, swap the words.
 * @return The (potentially swapped) float.
 */
float fSwapFloat(float f, bool bSwap);

/**
 * @brief Swaps the two 16-bit words of a 32-bit integer if bSwap is true.
 * @param l The input integer.
 * @param bSwap If true, swap the words.
 * @return The (potentially swapped) integer.
 */
int32_t lSwapLong(int32_t l, bool bSwap);

#endif /* UTILS_H */
