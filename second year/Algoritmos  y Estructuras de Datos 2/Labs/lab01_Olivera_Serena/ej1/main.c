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

void array_dump(int a[], unsigned int length) {

    printf("[");
    for ( unsigned int i = 0; i < length-1; i++)
    {
        printf( "%i,", a[i]);
    }
    printf( "%d]", a[length-1]);
    
}


int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];
    
    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_file(array, MAX_SIZE, filepath);
    
    /*dumping the array*/
    array_dump(array, length);
    
    return EXIT_SUCCESS;
}
