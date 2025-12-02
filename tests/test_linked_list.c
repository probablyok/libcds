#include "../include/linked_list.h"
#include "unity/unity.h"

/* Forward declare setup/teardown handlers */
extern void (*setupHandler)(void);
extern void (*teardownHandler)(void);

/* Global reference for tests */
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

/**
 * Test pushing an element to an out of bounds index in an empty list. Ensure
 * the list remains empty and the push function indicates an error.
 */
void test_linked_list_push_out_of_bounds(void) {
    uint32_t add = 0;
    bool pushError = linked_list_push_index(list, (void*)&add, 1);

    TEST_ASSERT_TRUE(pushError);
    TEST_ASSERT_EQUAL_size_t(0, list->size);
}

/**
 * Test verifying that `NULL` is returned when getting head and tail in an
 * empty list, as well as some out of bounds index after a push.
 */
void test_linked_list_get_out_of_bounds(void) {
    void* ret;

    // Check first
    ret = linked_list_get_first(list);
    TEST_ASSERT_NULL(ret);

    // Check last
    ret = linked_list_get_last(list);
    TEST_ASSERT_NULL(ret);

    // Check out of bounds index
    uint32_t add = 0;
    linked_list_push_first(list, (void*)&add);

    ret = linked_list_get_index(list, 1);
    TEST_ASSERT_NULL(ret);
}

/**
 * Tests pushing element to start of the list a certain number of times. Also
 * then updates/sets the value after each push.
 */
void test_linked_list_push_set_first(void) {
    bool pushError;
    bool setError;

    uint32_t max = 1024;
    uint32_t add = 0;
    uint32_t set = 1;

    for (uint32_t i = 0; i < max; i++) {
        pushError = linked_list_push_first(list, (void*)&add);

        // Push checks
        TEST_ASSERT_FALSE(pushError);
        TEST_ASSERT_EQUAL_size_t((size_t)(i + 1), list->size);
        TEST_ASSERT_EQUAL_UINT32(add, *(uint32_t*)linked_list_get_first(list));

        setError = linked_list_set_first(list, (void*)&set);

        // Set checks
        TEST_ASSERT_FALSE(setError);
        TEST_ASSERT_EQUAL_size_t((size_t)(i + 1), list->size);
        TEST_ASSERT_EQUAL_UINT32(set, *(uint32_t*)linked_list_get_first(list));
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
    RUN_TEST(test_linked_list_push_out_of_bounds);
    RUN_TEST(test_linked_list_get_out_of_bounds);
    RUN_TEST(test_linked_list_push_set_first);

    // Cleanup handlers
    setupHandler = NULL;
    teardownHandler = NULL;
}