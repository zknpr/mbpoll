#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "serial.h"

void test_standard_case() {
    xSerialIos ios;
    ios.baud = 9600;
    ios.dbits = SERIAL_DATABIT_8;
    ios.parity = SERIAL_PARITY_NONE;
    ios.sbits = SERIAL_STOPBIT_ONE;
    ios.flow = SERIAL_FLOW_NONE;

    const char *result = sSerialAttrToStr(&ios);
    // Format: BBBBBBBBBB-DPSF
    // "      9600-8N1 "
    printf("Test Standard Case: '%s'\n", result);
    assert(strcmp(result, "      9600-8N1 ") == 0);
}

void test_complex_case() {
    xSerialIos ios;
    ios.baud = 115200;
    ios.dbits = SERIAL_DATABIT_8;
    ios.parity = SERIAL_PARITY_EVEN;
    ios.sbits = SERIAL_STOPBIT_TWO;
    ios.flow = SERIAL_FLOW_RTSCTS;

    const char *result = sSerialAttrToStr(&ios);
    // "    115200-8E2H"
    printf("Test Complex Case: '%s'\n", result);
    assert(strcmp(result, "    115200-8E2H") == 0);
}

void test_rs485_case() {
    xSerialIos ios;
    ios.baud = 19200;
    ios.dbits = SERIAL_DATABIT_8;
    ios.parity = SERIAL_PARITY_NONE;
    ios.sbits = SERIAL_STOPBIT_ONE;
    ios.flow = SERIAL_FLOW_RS485_RTS_AFTER_SEND;

    const char *result = sSerialAttrToStr(&ios);
    // "     19200-8N1R"
    printf("Test RS485 Case: '%s'\n", result);
    assert(strcmp(result, "     19200-8N1R") == 0);
}

void test_stopbit_onehalf_case() {
    xSerialIos ios;
    ios.baud = 9600;
    ios.dbits = SERIAL_DATABIT_8;
    ios.parity = SERIAL_PARITY_NONE;
    ios.sbits = SERIAL_STOPBIT_ONEHALF;
    ios.flow = SERIAL_FLOW_NONE;

    const char *result = sSerialAttrToStr(&ios);
    // "      9600-8N3 "  (Wait, 1.5 is enum value 3)
    printf("Test StopBit 1.5 Case: '%s'\n", result);
    assert(strcmp(result, "      9600-8N3 ") == 0);
}

void test_truncation_case() {
    xSerialIos ios;
    ios.baud = 1234567890; // 10 digits
    ios.dbits = SERIAL_DATABIT_8;
    ios.parity = SERIAL_PARITY_NONE;
    ios.sbits = SERIAL_STOPBIT_ONE;
    ios.flow = SERIAL_FLOW_NONE;

    const char *result = sSerialAttrToStr(&ios);
    // "1234567890-8N1 "
    printf("Test Truncation Case (10 digits): '%s'\n", result);
    assert(strcmp(result, "1234567890-8N1 ") == 0);
}

void test_overflow_case() {
    xSerialIos ios;
    ios.dbits = SERIAL_DATABIT_8;
    ios.parity = SERIAL_PARITY_NONE;
    ios.sbits = SERIAL_STOPBIT_ONE;
    ios.flow = SERIAL_FLOW_NONE;

    // Check if long is large enough to hold the value
    if (sizeof(long) > 4) {
        ios.baud = 12345678901L; // 11 digits (if long is 64-bit)
        const char *result = sSerialAttrToStr(&ios);
        printf("Test Overflow Case (11 digits): '%s'\n", result);
        // Expected: "12345678901-8N1" (15 chars)
        // because snprintf truncates to size-1.
        assert(strcmp(result, "12345678901-8N1") == 0);
    } else {
        printf("Skipping Test Overflow Case (long is 32-bit)\n");
    }
}

int main() {
    test_standard_case();
    test_complex_case();
    test_rs485_case();
    test_stopbit_onehalf_case();
    test_truncation_case();
    test_overflow_case();

    printf("All tests passed!\n");
    return 0;
}
