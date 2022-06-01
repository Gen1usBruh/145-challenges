#include "vector.h" 
#include <assert.h>

typedef struct Node{
    int age;
    int pp;
} node;


int main(){
    Init_Vector(vector, node)
    vector vec = vector_new(); 
    printf("Size: %u Capacity: %u\n", vector_size(&vec), vector_capacity(&vec));
    node n = {20, 20};
    vector_push_back(&vec, n);
    printf("Size: %u Capacity: %u\n", vector_size(&vec), vector_capacity(&vec));
    node m = {17, 17};
    vector_push_back(&vec, m);
    printf("Size: %u Capacity: %u\n", vector_size(&vec), vector_capacity(&vec));
    vectorResult a = vector_at(&vec, 0);
    printf("Data: %d\n",((node*)a.node)->pp);
    assert(!a.error);
    a = vector_at(&vec, 1);
    printf("Data: %d\n",((node*)a.node)->pp);
    assert(!a.error);
    //a = vector_at(&vec, 2);
    //assert(!a.error);
    a = vector_begin(&vec);
    printf("Data: %d\n",((node*)a.node)->pp);
    a = vector_end(&vec);
    printf("Data: %d\n",((node*)a.node - 1)->pp);
    vector_deinit(&vec);
    printf("Size: %u Capacity: %u\n", vector_size(&vec), vector_capacity(&vec));
}