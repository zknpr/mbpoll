/**
 * @file test_serial.c
 * @brief Unit tests for serial.c functions
 *
 * Tests the string conversion functions for serial port configuration.
 * Based on Jules AI contributions, reviewed by Gemini Code Assist.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "serial.h"

/* Test result tracking */
static int g_tests_run = 0;
static int g_tests_failed = 0;

/* Test assertion macro */
#define TEST_ASSERT(condition, msg) do { \
    g_tests_run++; \
    if (!(condition)) { \
        fprintf(stderr, "FAIL: %s\n", msg); \
        g_tests_failed++; \
    } \
} while(0)

#define TEST_ASSERT_STR_EQ(actual, expected, msg) do { \
    g_tests_run++; \
    if (strcmp((actual), (expected)) != 0) { \
        fprintf(stderr, "FAIL: %s - expected '%s', got '%s'\n", msg, expected, actual); \
        g_tests_failed++; \
    } \
} while(0)

/* -------------------------------------------------------------------------- */
/*                          sSerialFlowToStr tests                            */
/* -------------------------------------------------------------------------- */
static void test_sSerialFlowToStr(void) {
    printf("Testing sSerialFlowToStr...\n");

    /* Test all valid flow control types */
    TEST_ASSERT_STR_EQ(sSerialFlowToStr(SERIAL_FLOW_NONE), "none",
                       "SERIAL_FLOW_NONE");
    TEST_ASSERT_STR_EQ(sSerialFlowToStr(SERIAL_FLOW_RTSCTS), "hardware",
                       "SERIAL_FLOW_RTSCTS");
    TEST_ASSERT_STR_EQ(sSerialFlowToStr(SERIAL_FLOW_XONXOFF), "software",
                       "SERIAL_FLOW_XONXOFF");
    TEST_ASSERT_STR_EQ(sSerialFlowToStr(SERIAL_FLOW_RS485_RTS_AFTER_SEND),
                       "rs485 rts after send", "SERIAL_FLOW_RS485_RTS_AFTER_SEND");
    TEST_ASSERT_STR_EQ(sSerialFlowToStr(SERIAL_FLOW_RS485_RTS_ON_SEND),
                       "rs485 rts on send", "SERIAL_FLOW_RS485_RTS_ON_SEND");
    TEST_ASSERT_STR_EQ(sSerialFlowToStr(SERIAL_FLOW_UNKNOWN), "Unknown",
                       "SERIAL_FLOW_UNKNOWN");

    /* Test invalid value returns Unknown */
    TEST_ASSERT_STR_EQ(sSerialFlowToStr((eSerialFlow)99), "Unknown",
                       "Invalid flow value");
}

/* -------------------------------------------------------------------------- */
/*                        sSerialDataBitsToStr tests                          */
/* -------------------------------------------------------------------------- */
static void test_sSerialDataBitsToStr(void) {
    printf("Testing sSerialDataBitsToStr...\n");

    /* Test all valid data bits values */
    TEST_ASSERT_STR_EQ(sSerialDataBitsToStr(SERIAL_DATABIT_5), "5",
                       "SERIAL_DATABIT_5");
    TEST_ASSERT_STR_EQ(sSerialDataBitsToStr(SERIAL_DATABIT_6), "6",
                       "SERIAL_DATABIT_6");
    TEST_ASSERT_STR_EQ(sSerialDataBitsToStr(SERIAL_DATABIT_7), "7",
                       "SERIAL_DATABIT_7");
    TEST_ASSERT_STR_EQ(sSerialDataBitsToStr(SERIAL_DATABIT_8), "8",
                       "SERIAL_DATABIT_8");
    TEST_ASSERT_STR_EQ(sSerialDataBitsToStr(SERIAL_DATABIT_UNKNOWN), "Unknown",
                       "SERIAL_DATABIT_UNKNOWN");

    /* Test invalid value returns Unknown */
    TEST_ASSERT_STR_EQ(sSerialDataBitsToStr((eSerialDataBits)99), "Unknown",
                       "Invalid databits value");
}

/* -------------------------------------------------------------------------- */
/*                        sSerialStopBitsToStr tests                          */
/* -------------------------------------------------------------------------- */
static void test_sSerialStopBitsToStr(void) {
    printf("Testing sSerialStopBitsToStr...\n");

    /* Test all valid stop bits values */
    TEST_ASSERT_STR_EQ(sSerialStopBitsToStr(SERIAL_STOPBIT_ONE), "1",
                       "SERIAL_STOPBIT_ONE");
    TEST_ASSERT_STR_EQ(sSerialStopBitsToStr(SERIAL_STOPBIT_TWO), "2",
                       "SERIAL_STOPBIT_TWO");
    TEST_ASSERT_STR_EQ(sSerialStopBitsToStr(SERIAL_STOPBIT_ONEHALF), "1.5",
                       "SERIAL_STOPBIT_ONEHALF");
    TEST_ASSERT_STR_EQ(sSerialStopBitsToStr(SERIAL_STOPBIT_UNKNOWN), "Unknown",
                       "SERIAL_STOPBIT_UNKNOWN");

    /* Test invalid value returns Unknown */
    TEST_ASSERT_STR_EQ(sSerialStopBitsToStr((eSerialStopBits)99), "Unknown",
                       "Invalid stopbits value");
}

/* -------------------------------------------------------------------------- */
/*                         sSerialParityToStr tests                           */
/* -------------------------------------------------------------------------- */
static void test_sSerialParityToStr(void) {
    printf("Testing sSerialParityToStr...\n");

    /* Test all valid parity values */
    TEST_ASSERT_STR_EQ(sSerialParityToStr(SERIAL_PARITY_NONE), "none",
                       "SERIAL_PARITY_NONE");
    TEST_ASSERT_STR_EQ(sSerialParityToStr(SERIAL_PARITY_EVEN), "even",
                       "SERIAL_PARITY_EVEN");
    TEST_ASSERT_STR_EQ(sSerialParityToStr(SERIAL_PARITY_ODD), "odd",
                       "SERIAL_PARITY_ODD");
    TEST_ASSERT_STR_EQ(sSerialParityToStr(SERIAL_PARITY_UNKNOWN), "Unknown",
                       "SERIAL_PARITY_UNKNOWN");

    /* Test invalid value returns Unknown */
    TEST_ASSERT_STR_EQ(sSerialParityToStr((eSerialParity)99), "Unknown",
                       "Invalid parity value");
}

/* -------------------------------------------------------------------------- */
/*                        sSerialAttrToStr tests                              */
/* -------------------------------------------------------------------------- */
static void test_sSerialAttrToStr(void) {
    printf("Testing sSerialAttrToStr...\n");

    xSerialIos ios;
    const char *result;

    /* Test standard configuration */
    ios.baud = 9600;
    ios.dbits = SERIAL_DATABIT_8;
    ios.parity = SERIAL_PARITY_NONE;
    ios.sbits = SERIAL_STOPBIT_ONE;
    ios.flow = SERIAL_FLOW_NONE;

    /* Format: %10ld-%1d%c%1d%c */
    /* "      9600-8N1 " */
    /* 9600 (4 digits) -> 6 spaces padding + 9600 */
    result = sSerialAttrToStr(&ios);
    TEST_ASSERT_STR_EQ(result, "      9600-8N1 ", "Standard 9600-8N1");

    /* Test max baud rate (6 digits) */
    ios.baud = 921600;
    /* "    921600-8N1 " */
    result = sSerialAttrToStr(&ios);
    TEST_ASSERT_STR_EQ(result, "    921600-8N1 ", "Max baud 921600-8N1");

    /* Test large baud rate (10 digits - fits) */
    ios.baud = 1234567890;
    /* "1234567890-8N1 " */
    result = sSerialAttrToStr(&ios);
    TEST_ASSERT_STR_EQ(result, "1234567890-8N1 ", "10-digit baud");

    /* Test various other params */
    ios.baud = 19200;
    ios.dbits = SERIAL_DATABIT_7;
    ios.parity = SERIAL_PARITY_EVEN;
    ios.sbits = SERIAL_STOPBIT_TWO;
    ios.flow = SERIAL_FLOW_RTSCTS; /* 'H' */

    /* "     19200-7E2H" */
    result = sSerialAttrToStr(&ios);
    TEST_ASSERT_STR_EQ(result, "     19200-7E2H", "19200-7E2H");
}

/* -------------------------------------------------------------------------- */
/*                              Main entry point                              */
/* -------------------------------------------------------------------------- */
int main(void) {
    printf("=== Serial Module Unit Tests ===\n\n");

    test_sSerialFlowToStr();
    test_sSerialDataBitsToStr();
    test_sSerialStopBitsToStr();
    test_sSerialParityToStr();
    test_sSerialAttrToStr();

    printf("\n=== Test Summary ===\n");
    printf("Tests run: %d\n", g_tests_run);
    printf("Tests failed: %d\n", g_tests_failed);

    if (g_tests_failed > 0) {
        printf("FAILED\n");
        return 1;
    }

    printf("ALL TESTS PASSED\n");
    return 0;
}
