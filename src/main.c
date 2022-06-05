#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "vector2.h"
#include "node.h"

void generate_sentence(cvector_vector_type(node*) chain, int sent_len){

    if(sent_len > 0){

        srand(time(NULL));  
        int rand_index = rand() % cvector_size(chain);

        int i, j, k, num_state, sum_probb;
        cvector_vector_type(node) state = chain[rand_index];
        
        for(i = 0; i != sent_len; ++i){

            printf("%s ", state->word);

            for(k = 0, sum_probb = 0; k != cvector_size(state->prob); ++k){
                sum_probb += state->prob[k];
            }

            num_state = cvector_size(state->next_state);

            while(!num_state){
                rand_index = rand() % cvector_size(chain);

                state = chain[rand_index];

                num_state = cvector_size(state->next_state);
            }

            // Must be revisited
            for(j = 0; j != num_state; ++j){
                if(sum_probb <= state->prob[j]){
                    state = state->next_state[j];
                    break;
                } 
                else
                    sum_probb -= state->prob[j];
            }

            ///////////////////
            // printf("\n%s -> ", state->word);
            // for(j = 0; j != cvector_size(state->next_state); ++j){
            //     printf("%s -> ", state->next_state[j]->word);
            // }
            // printf("\n|---> ");
            // for(j = 0; j != cvector_size(state->prob); ++j){
            //     printf("%d -> ", state->prob[j]);
            // }
            ///////////////////
        }
    }
}

int main(int argc, char* argv[]){    
    FILE* fd;
    long fSize;
    char* buf;
    size_t res;
    cvector_vector_type(node*) chain = NULL;

    if(argc != 3){
        fputs("Wrong arguments\nUsage: ./exe text.txt #ofWords", stderr);
        exit(1);
    }
    
    fd = fopen(argv[1], "r");
    if(fd == NULL){
        perror("Error while opening the file");
        exit(2);
    }

    // count number of characters in a file; 
    // works, but probably there is a better way
    int c;
    fSize = 0;
    while ((c = fgetc(fd))) {
        if (c == EOF) break;
        ++fSize;
    }

    buf = malloc(sizeof(char) * (fSize + 1));
    if (buf == NULL) {
        perror("Error while malloc'ing");
        exit(3);
    }

    // set file position indicator to the beginning - for 'fread'
    fseek(fd, 0, SEEK_SET);

    res = fread(buf, 1, fSize, fd);
    if (ferror(fd)) {
        fputs("Error while reading from file to buffer", stderr);
        exit(4);
    }
    buf[fSize] = '\0';

    printf("|%s|\n", buf);

    int i;
    char* word;
    char* old_word;
    word = strtok(buf," \n\t");
    while(word != NULL){

        old_word = word;

        node* state_found = NULL;
        for(i = 0; i != cvector_size(chain); ++i){
            if(!strcmp(old_word, chain[i]->word)){
                state_found = chain[i];
                break;
            }
        }

        word = strtok(NULL, " \n\t");

        node* next_state_found = NULL;
        if(word != NULL){
            for(i = 0; i != cvector_size(chain); ++i){
                if(!strcmp(word, chain[i]->word)){
                    next_state_found = chain[i];
                    break;
                }
            }        
        }

        if(state_found != NULL) {
            if(word != NULL) {
                if(next_state_found != NULL){
                    node* tmp = NULL; 
                    for(i = 0; i != cvector_size(state_found->next_state); ++i){
                        if(!strcmp(word, state_found->next_state[i]->word)){
                            tmp = state_found->next_state[i];
                            break;
                        }
                    }
                    if(tmp != NULL){
                        state_found->prob[i] += 1;
                    }
                    else{
                        cvector_push_back(state_found->next_state, next_state_found);
                        cvector_push_back(state_found->prob, 1);
                    }
                }
                else{
                    //goto createState;
                    node* nextState = malloc(sizeof(node));
                    nextState->prob = NULL;
                    nextState->next_state = NULL;
                    strcpy(nextState->word, word);

                    next_state_found = nextState;

                    cvector_push_back(state_found->next_state, next_state_found);
                    cvector_push_back(state_found->prob, 1);

                    cvector_push_back(chain, next_state_found);
                }
            }
        }
        else{
            node* state = malloc(sizeof(node));
            state->prob = NULL;
            state->next_state = NULL;
            strcpy(state->word, old_word);

            if(word != NULL){
                cvector_push_back(chain, state);

                if(next_state_found == NULL){
                //createState:
                    node* nextState = malloc(sizeof(node));
                    nextState->prob = NULL;
                    nextState->next_state = NULL;
                    strcpy(nextState->word, word);

                    next_state_found = nextState;    
                }

                cvector_push_back(state->next_state, next_state_found);
                cvector_push_back(state->prob, 1);

                cvector_push_back(chain, next_state_found);
            }
            else{
                cvector_push_back(chain, state);
            }
        }
    }
    
    // printf("%zd\n", cvector_size(chain));
    // for(i = 0; i != cvector_size(chain); ++i){
    //     printf("\n%s -> ", chain[i]->word);
    //     for(int j = 0; j != cvector_size(chain[i]->next_state); ++j){
    //         printf("%s -> ", chain[i]->next_state[j]->word);
    //     }
    //     printf("\n|---> ");
    //     for(int j = 0; j != cvector_size(chain[i]->prob); ++j){
    //         printf("%d -> ", chain[i]->prob[j]);
    //     }
    // }

    printf("\n");
    generate_sentence(chain, atoi(argv[2]));
    
    for(i = 0; i != cvector_size(chain); ++i){
        free(chain[i]);
    }
    cvector_free(chain);



    





    free(buf);
    fclose(fd);

}