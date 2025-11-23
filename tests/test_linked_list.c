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
 * number of times. Aditionally tests getting the last element on each push.
 */
void test_linked_list_push_get_last(void) {
    bool pushError;
    uint32_t max = 1024;
    for (uint32_t i = 0; i < max; i++) {
        pushError = linked_list_push_last(list, (void*)&i);

        TEST_ASSERT_FALSE(pushError);
        TEST_ASSERT_EQUAL_size_t((size_t)(i + 1), list->size);
        TEST_ASSERT_EQUAL_UINT32(i, *(uint32_t*)linked_list_get_last(list));
    }
}

/**
 * Test pushing an element to the start of the of the linked list a certain
 * number of times. Aditionally tests getting the first element on each push.
 */
void test_linked_list_push_get_first(void) {
    bool pushError;
    uint32_t max = 1024;
    for (uint32_t i = 0; i < max; i++) {
        pushError = linked_list_push_first(list, (void*)&i);

        TEST_ASSERT_FALSE(pushError);
        TEST_ASSERT_EQUAL_size_t((size_t)(i + 1), list->size);
        TEST_ASSERT_EQUAL_UINT32(i, *(uint32_t*)linked_list_get_first(list));
    }
}

/**
 * Test pushing an element at specific index of a list already containing two
 * elements (in the middle). Aditionally tests getting the second element on
 * each push.
 */
void test_linked_list_push_get_index(void) {
    // Insert between two existing elements
    uint32_t add = 0;
    linked_list_push_last(list, (void*)&add);
    linked_list_push_last(list, (void*)&add);

    bool pushError;
    uint32_t max = 1024;

    for (uint32_t i = 1; i <= max; i++) {
        // Push after first index
        pushError = linked_list_push_index(list, (void*)&i, 1);

        TEST_ASSERT_FALSE(pushError);
        TEST_ASSERT_EQUAL_size_t((size_t)(i + 2), list->size);
        TEST_ASSERT_EQUAL_UINT32(i, *(uint32_t*)linked_list_get_index(list, 1));
    }
}

void run_linked_list_tests(void) {
    // Set handlers
    setupHandler = setup_linked_list;
    teardownHandler = teardown_linked_list;

    // Run tests
    RUN_TEST(test_linked_list_push_get_last);
    RUN_TEST(test_linked_list_push_get_first);
    RUN_TEST(test_linked_list_push_get_index);

    // Cleanup handlers
    setupHandler = NULL;
    teardownHandler = NULL;
}