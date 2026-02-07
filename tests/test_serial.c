#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "serial.h"

// Simple unit test for sSerialStopBitsToStr

void test_sSerialStopBitsToStr() {
    printf("Testing sSerialStopBitsToStr...\n");

    // Test SERIAL_STOPBIT_ONE -> "1"
    const char * result1 = sSerialStopBitsToStr(SERIAL_STOPBIT_ONE);
    assert(result1 != NULL);
    assert(strcmp(result1, "1") == 0);
    printf("SERIAL_STOPBIT_ONE -> %s [PASS]\n", result1);

    // Test SERIAL_STOPBIT_TWO -> "2"
    const char * result2 = sSerialStopBitsToStr(SERIAL_STOPBIT_TWO);
    assert(result2 != NULL);
    assert(strcmp(result2, "2") == 0);
    printf("SERIAL_STOPBIT_TWO -> %s [PASS]\n", result2);

    // Test SERIAL_STOPBIT_ONEHALF -> "1.5"
    const char * result3 = sSerialStopBitsToStr(SERIAL_STOPBIT_ONEHALF);
    assert(result3 != NULL);
    assert(strcmp(result3, "1.5") == 0);
    printf("SERIAL_STOPBIT_ONEHALF -> %s [PASS]\n", result3);

    // Test SERIAL_STOPBIT_UNKNOWN -> "Unknown"
    const char * result4 = sSerialStopBitsToStr(SERIAL_STOPBIT_UNKNOWN);
    assert(result4 != NULL);
    assert(strcmp(result4, "Unknown") == 0);
    printf("SERIAL_STOPBIT_UNKNOWN -> %s [PASS]\n", result4);

    // Test Invalid Value -> "Unknown"
    const char * result5 = sSerialStopBitsToStr((eSerialStopBits)999);
    assert(result5 != NULL);
    assert(strcmp(result5, "Unknown") == 0);
    printf("Invalid (999) -> %s [PASS]\n", result5);

    printf("All sSerialStopBitsToStr tests passed.\n");
}

int main() {
    test_sSerialStopBitsToStr();
    return 0;
}
