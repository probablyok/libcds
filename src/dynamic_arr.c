#include "dynamic_arr.h"

#include <stdlib.h>

DynamicArr* dynamic_arr_create(size_t elemSize,
                               void* (*clone_elem)(const void*),
                               void (*free_elem)(void*)) {
    DynamicArr* arr = malloc(sizeof(DynamicArr));
    // Malloc failed
    if (!arr) {
        return NULL;
    }

    // Store metadata
    arr->head = 0;
    arr->tail = 0;
    arr->elemSize = elemSize;
    arr->size = 0;
    arr->capacity = DYNAMIC_ARR_INIT_CAPACITY;
    arr->clone_elem = clone_elem;
    arr->free_elem = free_elem;

    // Create array
    arr->data = malloc(DYNAMIC_ARR_INIT_CAPACITY * elemSize);

    return arr;
}

void dynamic_array_free(DynamicArr* arr) {
    // TODO: Iterate from head to tail and deep/shallow free element

    // Free dynamically allocated array
    free(arr->data);
    // Free structure itself
    free(arr);
}