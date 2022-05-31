#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#define Init_Vector(typename, type) \
    typedef struct { \
        unsigned int _size, _capacity; \
        type* _ptr_array; \
    } typename; \
    \
    typedef struct { \
        bool error; \
        type* node; \
    } typename##Result; \  
 \
    typename typename##_new() { \
        unsigned int capacity = 1; \
        type* ptr_node = malloc(capacity * sizeof(type)); \
        if (!ptr_node) { \
            fprintf(stderr, "Error in %s", typename##_new); \
            exit(1); \
        } \
        typename vector = { ._size = 0, ._capacity = capacity, ._ptr_array = ptr_node }; \
        return vector; \
    } \
 \
    typename* typename##_deinit(typename* vector) { \
        free(vector->_ptr_array); \
        vector->_size = 0; \
        vector->_capacity = 0; \
    } \
 \
    unsigned int typename##_size(typename* vector) { \
        return vector->_size; \
    } \
 \
    unsigned int typename##_capacity(typename* vector) { \
        return vector->_capacity; \
    } \
 \
    typename##Result typename##_begin(typename* vector) { \
        if(vector->_size != 0){ \
            typename##Result ok = {.error = false, .node = vector->_ptr_array}; \
            return ok; \
        } \
        typename##Result not_ok = {.error = true}; \
        return not_ok; \
    } \
 \
    typename##Result typename##_end(typename* vector) { \
        if(vector->_size != 0){ \
            typename##Result ok = {.error = false, .node = vector->_ptr_array + typename##_size(vector)}; \
            return ok; \
        } \
        typename##Result not_ok = {.error = true}; \
        return not_ok; \
    } \
 \
    typename##Result typename##_at(typename* vector, unsigned int index) { \
        if(vector->_size != 0 && index >= 0 && index < vector->_size){ \
            typename##Result ok = {.error = false, .node = vector->_ptr_array[index]}; \
            return ok; \
        } \
        typename##Result not_ok = {.error = true}; \
        return not_ok; \
    } \
 \
    void typename##_push_back(typename* vector, type* node) { \
        if(vector->_size >= vector->_capacity) \
            reserve(2 * vector->_capacity); \
        vector->_ptr_array[vector->_size++] = node; \
    } \
 \
    void typename##_reserve(typename* vector, unsigned int capacity){ \
        type* new_array = realloc(vector->_ptr_array, capacity * sizeof(type)); \
        
        vector->_ptr_array = new_array; \
        vector->_capacity = capacity; \
    } \
 \