#ifndef LINKED_LIST_H
#define LINKED_LIST_H

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

#endif
