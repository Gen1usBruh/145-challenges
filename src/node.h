#include "map.h"

typedef struct Node{
    char* word;
    map_int_t map;
} node;

void incrProb(node* curState, const char* nextState);

