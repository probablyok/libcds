#include "unity/unity.h"

/* Handlers for how to setup and tear down current test */
void (*setupHandler)(void) = NULL;
void (*teardownHandler)(void) = NULL;

/* Module runners */
extern void run_linked_list_tests();

void setUp(void) {
    if (setupHandler) {
        curSetUp();
    }
}
void tearDown(void) {
    if (teardownHandler) {
        curTearDown();
    }
}

int main(void) {
    UNITY_BEGIN();

    run_linked_list_tests();

    return UNITY_END();
}