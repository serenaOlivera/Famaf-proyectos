/*First, the libraries that are needed for defining functions*/
#include "array_helpers.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>



unsigned int array_from_file(int array[],
                             unsigned int max_size,
                             const char *filepath) {
    FILE *file;
    unsigned int n=0;
    array=array;

    file = fopen(filepath, "r");
    if (file==NULL){
        fprintf(stdout, "The file %s does not exists\n", filepath);
        exit(EXIT_FAILURE);
    }

    int res = fscanf(file, " %u ", &n);
    if (res !=1){
        fprintf(stdout, "The array format is incorrect\n");
        exit(EXIT_FAILURE);
    }

    if (n==0){
    fprintf(stdout, "The array format is incorrect\n");
    exit(EXIT_FAILURE);
    }

    if (n > max_size){
        fprintf(stdout, "The length exceeds the limit\n");
        exit(EXIT_FAILURE);
    }

    for ( unsigned int i = 0; i < n; i++){
        int check = fscanf(file, " %d ", &(array[i]));
        if (check != 1){
            fprintf(stdout, "There's not enough elements to fit the length of the array\n");
            exit(EXIT_FAILURE);
        }
        
    }

    if (fclose(file) != 0){
        fprintf(stderr, "The file isn't closed\n");
        exit(EXIT_FAILURE);
    }
    
    return n;
}

void array_dump(int a[], unsigned int length){ 

    printf("[");
    for (unsigned int i = 0; i < length-1; i++)
    {
        printf( "%i,", a[i]);
    }
    printf( "%d]", a[length-1]);
    
}