/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


/* Maximum allowed length of the array */
#define MAX_SIZE 100000

void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Loads an array given in a file in disk and prints it on the screen."
           "\n\n"
           "The input file must have the following format:\n"
           " * The first line must contain only a positive integer,"
           " which is the length of the array.\n"
           " * The second line must contain the members of the array"
           " separated by one or more spaces. Each member must be an integer."
           "\n\n"
           "In other words, the file format is:\n"
           "<amount of array elements>\n"
           "<array elem 1> <array elem 2> ... <array elem N>\n\n",
           program_name);
}



unsigned int array_from_stdin(int array[],
                             unsigned int max_size) {                            
    unsigned int n = 0;
    array = array;

    if (stdin==NULL){
        fprintf(stdout, "There's nothing to be analized\n");
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "What's the size of your array?\n");
    int res = fscanf(stdin, "%u", &n);
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
        fprintf(stdout,"Enter the element on the %u position:\n",i);
        int check = fscanf(stdin, "%d", &(array[i]));
        if (check != 1){
            fprintf(stdout, "There's not enough elements to fit the length of the array\n");
            exit(EXIT_FAILURE);
        }
        
    }
    
    return n;
}

void array_dump(int a[], unsigned int length) {

    printf("[");
    for ( unsigned int i = 0; i < length-1; i++)
    {
        printf( "%i,", a[i]);
    }
    printf( "%d]\n", a[length-1]);
    
}


int main() {

    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];
    
    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_stdin(array, MAX_SIZE);
    
    /*dumping the array*/
    array_dump(array, length);
    
    return EXIT_SUCCESS;
}
