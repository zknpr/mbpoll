#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "serial.h"

void test_sSerialDataBitsToStr() {
    // Test known values
    assert(strcmp(sSerialDataBitsToStr(SERIAL_DATABIT_5), "5") == 0);
    assert(strcmp(sSerialDataBitsToStr(SERIAL_DATABIT_6), "6") == 0);
    assert(strcmp(sSerialDataBitsToStr(SERIAL_DATABIT_7), "7") == 0);
    assert(strcmp(sSerialDataBitsToStr(SERIAL_DATABIT_8), "8") == 0);

    // Test unknown value
    assert(strcmp(sSerialDataBitsToStr(SERIAL_DATABIT_UNKNOWN), "Unknown") == 0);

    // Test arbitrary unknown value
    assert(strcmp(sSerialDataBitsToStr((eSerialDataBits)123), "Unknown") == 0);

    printf("test_sSerialDataBitsToStr passed\n");
}

int main() {
    test_sSerialDataBitsToStr();
    printf("All tests passed!\n");
    return 0;
}
