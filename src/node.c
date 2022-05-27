#include "node.h"

void incrProb(node* curState, const char* nextState){
    int* probb = map_get(&(curState->map), nextState);
    if(probb){
        map_set(&(curState->map), nextState, (*probb) + 1);
    }
}