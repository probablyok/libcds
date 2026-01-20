#ifndef DYNAMIC_ARR_H
#define DYNAMIC_ARR_H

#include <stddef.h>

/**
 * Dynamic array structure that holds metadata about size, capacity, head and
 * tail, as well as a reference to the current static array representing
 * structure. The dynamic array is implemented to be cyclic for O(1) prepend
 * operations, and is always contingous from the head to tail index logical
 * order taking wrapping into account. The array resizes by doubling when full,
 * and the array "unwraps" during this.
 * @param size The total number of used indices in the data array.
 * @param capacity The total number of indices (used/unused) in the data array.
 * @param head The index of the first logical element in the data array.
 * @param tail The index of the last logical element in the data array.
 * @param arr A reference to a dynamically allocated data array.
 * @param clone_elem A callback function that should be provided if you intend
 * to store elements that contain heap-allocated data. This function should,
 * when passed the data of a given node, copy all memory and return a pointer
 * to a heap-allocated copy of the data that can persist without referencing the
 * list. Set to `NULL` if a deep clone is not needed.
 * @param free_elem A callback function that should be provided if you intend
 * to free elements that contain heap-allocated data. This function should,
 * when passed the data of a given node, free all memory contained within it,
 * and the node's `data` as well. Set to `NULL` if a deep free is not needed.
 */
typedef struct {
    size_t size;
    size_t capacity;
    size_t head;
    size_t tail;
    void** arr;
    void* (*clone_elem)(const void*); // Deep copy callback
    void* (*free_elem)(void*);        // Deep free callback
} DynamicArr;

#endif