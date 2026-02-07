#include <stdio.h>
#include <string.h>
#include "serial.h"

int main(void) {
    struct {
        eSerialFlow flow;
        const char *expected;
    } test_cases[] = {
        {SERIAL_FLOW_NONE, "none"},
        {SERIAL_FLOW_RTSCTS, "hardware"},
        {SERIAL_FLOW_XONXOFF, "software"},
        {SERIAL_FLOW_RS485_RTS_AFTER_SEND, "rs485 rts after send"},
        {SERIAL_FLOW_RS485_RTS_ON_SEND, "rs485 rts on send"},
        {SERIAL_FLOW_UNKNOWN, "Unknown"},
        {(eSerialFlow)99, "Unknown"}
    };

    int num_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    int failed = 0;

    for (int i = 0; i < num_cases; i++) {
        const char *result = sSerialFlowToStr(test_cases[i].flow);
        if (strcmp(result, test_cases[i].expected) != 0) {
            fprintf(stderr, "Test failed for flow %d: expected '%s', got '%s'\n",
                    (int)test_cases[i].flow, test_cases[i].expected, result);
            failed = 1;
        }
    }

    if (failed) {
        return 1;
    }

    printf("All tests passed\n");
    return 0;
}
