#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#include <stddef.h>

/**
 * Single node in a linked list. Holds data and points to the next and previous
 * child in the list.
 * @param data The data held by the node. Should not be dereferenced as it is
 * a void pointer.
 * @param next A pointer to the next node in the linked list. `NULL` represents
 * that there is no next node, and that this node is the list tail.
 * @param prev A pointer to the previous node in the linked list. `NULL`
 * represents that there is no previous node, and that this node is the list
 * head.
 */
typedef struct ListNode {
    void* data;
    struct ListNode* next;
    struct ListNode* prev;
} ListNode;

/**
 * Holds pointers to the start (head) and end (tail) of a linked list, and
 * holds metadata about the list (size, element size). It is assumed that each
 * `next` from the head node forms a chain of pointers to the tail node, and
 * vice versa from the tail to head with `prev`.
 * @param head A pointer to the head/start of the linked list.
 * @param tail A pointer to the tail/end of the linked list.
 * @param elemSize The size, in bytes, of the `data` entry in each node.
 * @param size The total number of nodes currently being stored in this
 * particular list.
 */
typedef struct {
    ListNode* head;
    ListNode* tail;
    size_t elemSize;
    size_t size;
} LinkedList;

/**
 * Creates a returns an empty, heap-allocated `LinkedList` with elements set to
 * be of `elemSize` bytes. Linked lists must be freed by the programmer when
 * no longer needed.
 * @param elemSize The number of bytes for data each node in list node holds.
 * @return Pointer to an empty, heap-allocated linked list.
 */
LinkedList* linked_list_create(size_t elemSize);

/**
 * Adds a node to the end of the list with contents copied from `elem`.
 * @param list A reference to the linked list being added to.
 * @param elem A reference to the void pointer representing data that is being
 * copied to the list.
 */
bool linked_list_push_last(LinkedList* list, const void* elem);

/**
 * Adds a node to the start of the list with contents copied from `elem`.
 * @param list A reference to the linked list being added to.
 * @param elem A reference to the void pointer representing data that is being
 * copied to the list.
 */
bool linked_list_push_first(LinkedList* list, const void* elem);

/**
 * Frees memory pertaining to a linked list. It frees: each node's `data`, the
 * node itself, and finally the list itself. Lists freed with this function
 * should never be used afterwards.
 * @param list The linked list container whose contents (and itself) are being
 * freed.
 */
void linked_list_free(LinkedList* list);

/**
 * Frees memory pertaining to a linked list in cases where data held by each
 * node is nested and must be freed (i.e. each node holds an array of heap
 * allocated pointers). Works like `linked_list_free()` but also frees nested
 * node data with `free_nested()`. Lists freed with this function should never
 * be used afterwards.
 * @param list The linked lis container whose contents (and itself) are being
 * freed.
 * @param free_nested A function pointer which takes in one void pointer
 * (representing data held by node) and performs operations needed to free
 * nested data.
 */
void linked_list_free_with(LinkedList* list, void (*free_nested)(void*));

#endif
