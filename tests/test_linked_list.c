#include "../include/linked_list.h"
#include "unity/unity.h"

/** Forward declare setup/teardown handlers */
extern void (*setupHandler)(void);
extern void (*teardownHandler)(void);

void setup_linked_list(void) { return; }

void teardown_linked_list(void) { return; }

void test_linked_list_dummy(void) { TEST_ASSERT(1); }

void run_linked_list_tests(void) {
    // Set handlers
    setupHandler = setup_linked_list;
    teardownHandler = teardown_linked_list;

    // Run tests
    RUN_TEST(test_linked_list_dummy);

    // Cleanup handlers
    setupHandler = NULL;
    teardownHandler = NULL;
}