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
 * @param clone_elem A callback function that should be provided if you intend
 * to store elements that contain heap-allocated data. This function should,
 * when passed the data of a given node, copy all memory a return a pointer
 * to a heap-allocated copy of the data that can persist without referencing the
 * list. Set to `NULL` if a deep clone is not needed.
 * @param free_elem A callback function that should be provided if you intend
 * to free elements that contain heap-allocated data. This function should,
 * when passed that data of a given node, free all memory contained within it,
 * and the node's `data` as well. Set to `NULL` if a deep free is not needed.
 */
typedef struct {
    ListNode* head;
    ListNode* tail;
    size_t elemSize;
    size_t size;
    void* (*clone_elem)(const void*);  // Deep copy callback
    void (*free_elem)(void*);          // Deep free callback
} LinkedList;

/**
 * Creates a returns an empty, heap-allocated `LinkedList` with elements set to
 * be of `elemSize` bytes. Linked lists must be freed by the programmer when
 * no longer needed. If storing elements that hold there own heap-allocated
 * pointers, also specify deep clone and free functions, otherwise specify
 * `NULL`.
 * @param elemSize The number of bytes for data each node in list node holds.
 * @param clone_elem A pointer to a function that copies bytes at a void pointer
 * to a new void pointer and returns it.
 * @param free_elem A pointer to a function that frees all heap-allocated
 * pointers in an element as a void pointer.
 * @return Pointer to an empty, heap-allocated linked list.
 */
LinkedList* linked_list_create(size_t elemSize,
                               void* (*clone_elem)(const void*),
                               void (*free_elem)(void*));

/**
 * Returns a void pointer to the data held at index `idx` in given linked list.
 * This function returns a copy to the data, meaning the returned value get
 * persist after list lifetime and must be manually freed.
 * @param list A reference to the list being indexed.
 * @param idx The index whose data is being retrieved.
 * @return `NULL` if the index provided was not within min and max bounds of
 * list, or if the list is empty.
 */
void* linked_list_get_index(LinkedList* list, size_t idx);

/**
 * Adds a node to the end of the list with contents copied from `elem`.
 * @param list A reference to the linked list being added to.
 * @param elem A reference to the void pointer representing data that is being
 * copied to the list.
 * @return `true` if there was an error adding the element, `false` otherwise.
 */
bool linked_list_push_last(LinkedList* list, const void* elem);

/**
 * Adds a node to the start of the list with contents copied from `elem`.
 * @param list A reference to the linked list being added to.
 * @param elem A reference to the void pointer representing data that is being
 * copied to the list.
 * @return `true` if there was an error adding the element, `false` otherwise.
 */
bool linked_list_push_first(LinkedList* list, const void* elem);

/**
 * Adds a node after a given index with contents copied from `elem`. The
 * index must be within bounds of the list's min and max indices.
 * @param list A reference to the linked list being added to.
 * @param elem A reference to the void pointer representing data that is being
 * copied to the list.
 * @return `true` if there was an error adding the element, `false` otherwise.
 */
bool linked_list_push_at(LinkedList* list, const void* elem, size_t idx);

/**
 * Frees memory pertaining to a linked list. It frees: each node's `data`
 * (either deeply if `free_elem` is not NULL, shallow otherwise), the node
 * itself, and finally the list itself. Lists freed with this function should
 * never be used afterwards. Freeing a list does not deallocate any values
 * retrieved from the list during its lifetime.
 * @param list The linked list container whose contents (and itself) are being
 * freed.
 */
void linked_list_free(LinkedList* list);

#endif
