#include "linked_list.h"

#include <stdlib.h>
#include <string.h>

LinkedList* linked_list_create(size_t elemSize) {
    LinkedList* list = malloc(sizeof(LinkedList));
    // Malloc failed
    if (!list) {
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    list->elemSize = elemSize;
    list->size = 0;

    return list;
}

/**
 * Helper function for adding nodes to a given list. It initializes a list node
 * which stores data of size `elemSize` (in bytes) and contents `elem`.
 * @param elemSize The size (in bytes) of the data list node holds
 * @param elem A void pointer representing to data that is copied into node.
 * @return NULL if system calls fail and the node could not be created, a
 * pointer to the list node on the heap, otherwise.
 */
static ListNode* linked_list_create_node(size_t elemSize, const void* elem) {
    ListNode* node = malloc(sizeof(ListNode));
    // Malloc failed
    if (!node) {
        return NULL;
    }

    node->data = malloc(elemSize);
    // Malloc failed
    if (!node->data) {
        free(node);
        return NULL;
    }

    memcpy(node->data, elem, elemSize);
    node->next = NULL;
    node->prev = NULL;

    return node;
}

bool linked_list_push_last(LinkedList* list, const void* elem) {
    // Create list node
    ListNode* node = linked_list_create_node(list->elemSize, elem);
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
    ListNode* node = linked_list_create_node(list->elemSize, elem);
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
        free(cur->data);  // Free data in node
        free(cur);        // Free node itself
        cur = next;
    }

    free(list);  // Free list container
}

void linked_list_free_with(LinkedList* list, void (*free_nested)(void*)) {
    ListNode* cur = list->head;
    while (cur) {
        ListNode* next = cur->next;
        free_elem(cur->data);  // Free nested data in node
        free(cur->data);       // Free data in node
        free(cur);             // Free node itself
        cur = next;
    }

    free(list);  // Free list container
}