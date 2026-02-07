#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <setjmp.h>
#include <string.h>
#include "utils.h"

// Mock state
jmp_buf jump_buffer;
bool exit_expected = false;

// Mock vFailureExit
void vFailureExit (bool bHelp, const char *format, ...) {
    va_list va;
    va_start (va, format);
    printf("Mock vFailureExit called: ");
    vprintf(format, va);
    printf("\n");
    va_end (va);

    if (exit_expected) {
        longjmp(jump_buffer, 1);
    } else {
        printf("Unexpected exit!\n");
        exit(1);
    }
}

// Test harness
void test_iGetIntList_simple() {
    int len = 0;
    int *list = iGetIntList("test", "1,2,3", &len);
    if (len != 3) {
        printf("FAIL: simple list length mismatch: %d != 3\n", len);
        exit(1);
    }
    if (list[0] != 1 || list[1] != 2 || list[2] != 3) {
        printf("FAIL: simple list content mismatch\n");
        exit(1);
    }
    free(list);
    printf("PASS: simple list\n");
}

void test_iGetIntList_range() {
    int len = 0;
    int *list = iGetIntList("test", "1:3", &len);
    if (len != 3) {
        printf("FAIL: range list length mismatch: %d != 3\n", len);
        exit(1);
    }
    if (list[0] != 1 || list[1] != 2 || list[2] != 3) {
        printf("FAIL: range list content mismatch\n");
        exit(1);
    }
    free(list);
    printf("PASS: range list\n");
}

void test_iGetIntList_mixed() {
    int len = 0;
    int *list = iGetIntList("test", "1,5:7,10", &len);
    // 1, 5,6,7, 10 -> 5 items
    if (len != 5) {
        printf("FAIL: mixed list length mismatch: %d != 5\n", len);
        exit(1);
    }
    if (list[0] != 1 || list[1] != 5 || list[2] != 6 || list[3] != 7 || list[4] != 10) {
        printf("FAIL: mixed list content mismatch\n");
        exit(1);
    }
    free(list);
    printf("PASS: mixed list\n");
}

void test_iGetIntList_invalid_char() {
    int len = 0;
    exit_expected = true;
    if (setjmp(jump_buffer) == 0) {
        iGetIntList("test", "1,a,3", &len);
        printf("FAIL: invalid char did not exit\n");
        exit(1);
    } else {
        printf("PASS: invalid char exited as expected\n");
    }
    exit_expected = false;
}

void test_iGetIntList_invalid_syntax() {
    int len = 0;
    exit_expected = true;
    if (setjmp(jump_buffer) == 0) {
        iGetIntList("test", "1:2:3", &len); // double colon
        printf("FAIL: invalid syntax did not exit\n");
        exit(1);
    } else {
        printf("PASS: invalid syntax exited as expected\n");
    }
    exit_expected = false;
}

int main() {
    printf("Running tests...\n");
    test_iGetIntList_simple();
    test_iGetIntList_range();
    test_iGetIntList_mixed();
    test_iGetIntList_invalid_char();
    test_iGetIntList_invalid_syntax();
    printf("All tests passed.\n");
    return 0;
}
