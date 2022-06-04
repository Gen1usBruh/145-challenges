#include "vector2.h"

typedef struct Node{
    char word[64];
    cvector_vector_type(int) prob;
    cvector_vector_type(struct Node*) next_state;
} node;