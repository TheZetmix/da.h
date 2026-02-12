#ifndef DA_H
#define DA_H

#include "stdio.h"
#include "stdlib.h"
#include "assert.h"

// variadic arguments are needed so that expressions like (Type){1, 2} can be passed as values
#define da_append(arr, ...) do { \
        if (arr.size + 1 > arr.cap) {                                   \
            if (arr.cap == 0) arr.cap = 256;                            \
            else arr.cap *= 2;                                          \
            arr.items = realloc(arr.items, arr.cap * sizeof(*arr.items)); \
            if (arr.items == NULL) assert(0 && "da: memory allocation failed"); \
        }                                                               \
        arr.items[arr.size++] = __VA_ARGS__;                            \
    } while (0)

#define da_pop(arr) ( \
    (arr.size > 0) ? arr.items[--arr.size] : ( \
        assert(0 && "da: underflow"), \
        (typeof(*arr.items)){0} \
    ) \
)

#define da_insert(arr, index, ...) do { \
    assert(index <= arr.size && "da: insert index out of bounds"); \
    if (arr.size + 1 > arr.cap) { \
        if (arr.cap == 0) arr.cap = 256; \
        else arr.cap *= 2; \
        arr.items = realloc(arr.items, arr.cap * sizeof(*arr.items)); \
        if (arr.items == NULL) assert(0 && "da: memory allocation failed"); \
    } \
    for (size_t i = arr.size; i > index; i--) { \
        arr.items[i] = arr.items[i-1]; \
    } \
    arr.items[index] = __VA_ARGS__; \
    arr.size++; \
} while(0)

#define da_remove(arr, index) do { \
    assert(index < arr.size && "da: remove index out of bounds"); \
    for (size_t i = index; i < arr.size - 1; i++) { \
        arr.items[i] = arr.items[i+1]; \
    } \
    arr.size--; \
} while(0)

#define da_last(arr) ( \
    (arr.size > 0) ? arr.items[arr.size - 1] : ( \
        assert(0 && "da: underflow"), \
        (typeof(*arr.items)){0} \
    ) \
)

#define da_init() {.items = NULL, .size = 0, .cap = 0}
#define da_declare(type) typedef struct {type *items; size_t size; size_t cap;} da_##type
#define da_free(arr) do { free(arr.items); arr.items = NULL; arr.size = 0; arr.cap = 0; } while(0)

#endif // DA_H
