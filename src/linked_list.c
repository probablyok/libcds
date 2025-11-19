#include "linked_list.h"

#include <stdlib.h>

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