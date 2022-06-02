#include "vector.h"

typedef struct Node{
    char* word;
    vector numOfConn;
    vector nextState;
} node;

void incrProb(node* curState, const char* nextState);

