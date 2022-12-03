#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    printf("%s\n",argv[1]);

    if(strcmp(argv[1], "hola") == 0){
        printf("mundo\n");
    }

}