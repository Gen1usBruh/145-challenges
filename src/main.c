#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "vector2.h"
#include "node.h"

inline int isEmptyChar(char c){
    return (c == ' ' || c == '\n' || c == '\t' || c == '\0');
}

inline void strlower(char* str){
    for( ; *str; ++str) *str = tolower(*str);
}
/*
void replace_char(char* str, char ch_replace){
    char replace_by[4];
    replace_by[0] = replace_by[2] = ' '; replace_by[1] = ch_replace;
    char* char_pos;
    char_pos = strchr(str, ch_replace);
    while(char_pos != NULL){
        strncpy(char_pos, replace_by, 3);
        char_pos = strchr(char_pos + 1, ch_replace);
    }
}
void* split(char* str, int len){
    char* word;
    int cnt = 0;
    word = strtok(str," \n\t");
    while(word != NULL){
        ++cnt;
        printf("%s %zd\n", word, strlen(word));
        word = strtok(NULL, " \n\t");
    }

    printf("%d\n\n\n", cnt);

    char** list_of_words = malloc(cnt * sizeof(char*));
    word = strtok(str," \n\t");
    int i = 0;
    while(word != NULL && i != cnt){
        printf("%s %zd\n", word, strlen(word));
        list_of_words[i] = malloc(sizeof(char)*strlen(word) + 1);
        printf("heyyyyyyyyyyyy\n");
        strcpy(list_of_words[i], word);
        printf("heyyyyyyyyyyyy\n");
        word = strtok(NULL, " \n\t");
        ++i;
    }
    return list_of_words;
}
*/

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
                // printf("Found old_word: %s\n", chain[i]->word);
                state_found = chain[i];
                break;
            }
        }

        word = strtok(NULL, " \n\t");

        node* next_state_found = NULL;
        if(word != NULL){
            for(i = 0; i != cvector_size(chain); ++i){
                if(!strcmp(word, chain[i]->word)){
                    // printf("Found word: %s\n", chain[i]->word);
                    next_state_found = chain[i];
                    break;
                }
            }        
        }

        if(state_found != NULL/*&& state_found != cvector_end(chain)*/) {
            if(word != NULL) {
                if(next_state_found != NULL){
                    node* tmp = NULL; 
                    for(i = 0; i != cvector_size(state_found->next_state); ++i){
                        if(!strcmp(word, state_found->next_state[i]->word)){
                            // printf("Found state_found->next_state: %s\n", state_found->next_state[i]->word);
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
        //
        //printf("%s\n", word);
    }
    //cvector_pop_back(chain);
    printf("%zd\n", cvector_size(chain));
    for(i = 0; i != cvector_size(chain); ++i){
        printf("\n%s -> ", chain[i]->word);
        for(int j = 0; j != cvector_size(chain[i]->next_state); ++j){
            printf("%s -> ", chain[i]->next_state[j]->word);
        }
        printf("\n|---> ");
        for(int j = 0; j != cvector_size(chain[i]->prob); ++j){
            printf("%d -> ", chain[i]->prob[j]);
        }
    }
    
    for(i = 0; i != cvector_size(chain); ++i){
        free(chain[i]);
    }
    cvector_free(chain);



    





    free(buf);
    fclose(fd);

}