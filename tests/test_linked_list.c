#include "../include/linked_list.h"
#include "unity/unity.h"

/** Forward declare setup/teardown handlers */
extern void (*setupHandler)(void);
extern void (*teardownHandler)(void);

/** Global reference for tests */
LinkedList* list;

void setup_linked_list(void) {
    // Create shallow list of `uint32_t`
    list = linked_list_create(sizeof(uint32_t), NULL, NULL);
}

void teardown_linked_list(void) { linked_list_free(list); }

/**
 * Test pushing an element to the end of the of the linked list a certain
 * number of times.
 */
void test_linked_list_push_last(void) {
    bool pushError;
    size_t max = 1024;
    for (size_t i = 0; i < max; i++) {
        pushError = linked_list_push_last(list, (void*)&i);

        TEST_ASSERT_FALSE(pushError);
        TEST_ASSERT_EQUAL_size_t(i + 1, list->size);
        TEST_ASSERT_EQUAL_UINT32(i, *(uint32_t*)linked_list_get_last(list));
    }
}

/**
 * Test pushing an element to the start of the of the linked list a certain
 * number of times.
 */
void test_linked_list_push_first(void) {
    bool pushError;
    size_t max = 1024;
    for (size_t i = 0; i < max; i++) {
        pushError = linked_list_push_first(list, (void*)&i);

        TEST_ASSERT_FALSE(pushError);
        TEST_ASSERT_EQUAL_size_t(i + 1, list->size);
        TEST_ASSERT_EQUAL_UINT32(i, *(uint32_t*)linked_list_get_first(list));
    }
}

void run_linked_list_tests(void) {
    // Set handlers
    setupHandler = setup_linked_list;
    teardownHandler = teardown_linked_list;

    // Run tests
    RUN_TEST(test_linked_list_push_last);
    RUN_TEST(test_linked_list_push_first);

    // Cleanup handlers
    setupHandler = NULL;
    teardownHandler = NULL;
}