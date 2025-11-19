#include "linked_list.h"

#include <stdlib.h>
#include <string.h>

LinkedList* linked_list_create(size_t elemSize,
                               void* (*clone_elem)(const void*),
                               void (*free_elem)(void*)) {
    LinkedList* list = malloc(sizeof(LinkedList));
    // Malloc failed
    if (!list) {
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    list->elemSize = elemSize;
    list->size = 0;
    list->clone_elem = clone_elem;
    list->free_elem = free_elem;

    return list;
}

/**
 * Helper function for adding nodes to a given list. It initializes a list node
 * which copies `elemSize` bytes at `elem`. It performs the a shallow copy if
 * `clone_elem` is NULL, and uses `clone_elem` to do a deep copy if specified.
 * @param elemSize The size (in bytes) of the data list node holds
 * @param elem A void pointer representing to data that is copied into node.
 * @param clone_elem A function pointer that performs a user-specified deep copy
 * of the given element into the linked list.
 * @return NULL if memory allocation fails and the node could not be created, or
 * a pointer to the list node on the heap, otherwise.
 */
static ListNode* linked_list_create_node(size_t elemSize, const void* elem,
                                         void* (*clone_elem)(const void*)) {
    ListNode* node = malloc(sizeof(ListNode));
    // Malloc failed
    if (!node) {
        return NULL;
    }

    if (clone_elem) {
        node->data = clone_elem(elem);
        if (!node->data) {  // Deep copy
            free(node);
            return NULL;
        }
    } else {
        node->data = malloc(elemSize);  // Shallow copy
        // Malloc failed
        if (!node->data) {
            free(node);
            return NULL;
        }
        memcpy(node->data, elem, elemSize);
    }

    node->next = NULL;
    node->prev = NULL;

    return node;
}

void* linked_list_get_index(LinkedList* list, size_t idx) {
    // Bounds check
    if (list->size == 0 || idx > (list->size - 1)) {
        return NULL;
    }

    ListNode* cur = list->head;
    for (size_t i = 0; i < idx; idx++) {
        cur = cur->next;  // Assume nodes connect
    }

    if (list->clone_elem) {
        return list->clone_elem(cur->data);  // Return deep cloned element
    }

    // Shallow copy case
    void* copy = malloc(list->elemSize);
    // Malloc fail
    if (!copy) {
        return NULL;
    }

    memcpy(copy, cur->data, list->elemSize);
    return copy;
}

bool linked_list_push_last(LinkedList* list, const void* elem) {
    // Create list node
    ListNode* node =
        linked_list_create_node(list->elemSize, elem, list->clone_elem);
    if (!node) {
        return true;
    }

    if (!list->head) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;  // Current tail points to new tail
        node->prev = list->tail;  // New tail points back to current tail
        list->tail = node;        // New tail set as current tail
    }

    list->size++;
    return false;
}

bool linked_list_push_first(LinkedList* list, const void* elem) {
    // Create list node
    ListNode* node =
        linked_list_create_node(list->elemSize, elem, list->clone_elem);
    if (!node) {
        return true;
    }

    if (!list->tail) {
        list->head = node;
        list->tail = node;
    } else {
        node->next = list->head;  // New node points to current head
        list->head->prev = node;  // Current head points back to new head
        list->head = node;        // New head set as current head
    }

    list->size++;
    return false;
}

void linked_list_free(LinkedList* list) {
    ListNode* cur = list->head;
    while (cur) {
        ListNode* next = cur->next;

        if (list->free_elem) {
            list->free_elem(cur->data);  // Deep free of node data
        } else {
            free(cur->data);  // Shallow free of node data
        }

        free(cur);  // Free node itself
        cur = next;
    }

    free(list);  // Free list container
}