#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "node.h"

inline int isEmptyChar(char c){
    return (c == ' ' || c == '\n' || c == '\t' || c == '\0');
}

int main(int argc, char* argv[]){    
    FILE* fd;
    long fSize;
    char* buf;
    size_t res;
    Init_Vector(vector, )

    if(argc != 3){
        fputs("Wrong arguments\nUsage: ./exe text.txt #ofWords", stderr);
        exit(1);
    }
    
    fd = fopen(argv[1], "r");
    if(fd == NULL){
        perror("Error while opening the file");
        exit(2);
    }
    fseek(fd, 0, SEEK_END);
    fSize = ftell(fd);
    fseek(fd, 0, SEEK_SET);

    buf = malloc(sizeof(char)*(fSize+1));
    if(buf == NULL){
        perror("Error while malloc'ing");
        exit(3);
    }

    res = fread(buf, 1, fSize, fd);
    if(ferror(fd)){
        fputs("Error while reading from file to buffer", stderr);
        exit(4);
    }
    buf[fSize] = '\0';

    printf("%s", buf);

    int i, j, cntWords;
    char tempBuf[64];
    for(i = 0, j = 0; i != fSize - 1; j = 0){
        if(!isEmptyChar(buf[i])){
            while(!isEmptyChar(buf[i + 1])){
                tempBuf[j++] = buf[i++];
            }
            tempBuf[j] = '\0';  // convert to lowercase 

            
        }
    }
    
    



    





    free(buf);
    fclose(fd);

}