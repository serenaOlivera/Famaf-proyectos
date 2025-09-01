/* First, the standard lib includes, alphabetically ordered */
#include "array_helpers.h"
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

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;
    // Program takes exactly two arguments
    // (the program's name itself and the input-filepath)
    bool valid_args_count = (argc == 2);

    if (!valid_args_count) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return result;
}

int array_invert (int a[], unsigned int length){
    unsigned int pos = 0;

    while (pos<length/2){               /* I just need to check half of the array*/
        array_swap(a,pos,length-pos-1);
        pos++;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;
    bool res;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];
    
    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_file(array, MAX_SIZE, filepath);

    /* inverts the array*/
    array_invert(array,length);
    
    /* dumping the array*/
    array_dump(array, length);

    /*checks if the array is sorted and prints a message*/
    res=array_is_sorted(array,length);
    if (res==true){
        fprintf(stdout, "El arreglo esta ordenado\n");
    }else if (res==false){
        fprintf(stdout, "El arreglo no esta ordenado\n");
    }

    return EXIT_SUCCESS;
}
