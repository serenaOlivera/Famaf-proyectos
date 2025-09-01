/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "abb.h" /* TAD abb */


void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

unsigned int indice (){
    unsigned int n = 0;
    printf("\t Elige la opcion que quieres: \n"
            "\t 1. Mostrar el arbol por pantalla \n"
            "\t 2. Agregar un elemento \n"
            "\t 3. Eliminar un elemento \n"
            "\t 4. Chequear existencia de un elemento \n"
            "\t 5. Mostrar la longitud del arbol \n"
            "\t 6. Mostrar raiz, maximo y minimo del arbol \n"
            "\t 7. Salir del programa \n"
            );
    fscanf(stdin, "%u", &n);
    return n;
}


void printeo(abb tree){
    unsigned int n = 0;

    while (n != 7){
        n = indice(n);
        if(n > 7 || n == 0){
            printf("Instruccion no valida\n");
        }else if (n == 1){
            abb_dump(tree, ABB_PRE_ORDER);
            printf("\n");
        }else if (n == 2){
            abb_elem add = 0;
            printf("Ingresa el numero que quieres agregar \n");
            fscanf(stdin,"%d", &add);
            abb_add(tree,add);
        }else if (n == 3){
            abb_elem bye = 0;
            printf("Ingresa el numero que quieres eliminar \n");
            fscanf(stdin,"%d", &bye);
            abb_remove(tree,bye);
        }else if (n == 4){
            bool boleano = false;
            abb_elem ver = 0;
            printf("Ingresa el numero que quieras verificar \n");
            fscanf(stdin, "%d", &ver);
            boleano = abb_exists(tree,ver);
            if (boleano == true){
                printf("El numero si existe en el arbol\n");
            }else{
                printf("El numero no  existe en el arbol\n");
            }
        }else if (n == 5){
            printf("La longitud del arbol es: %u \n", abb_length(tree));
        }else if (n == 6){
            if (!abb_is_empty(tree)) {
                printf("\n");
                printf("raiz: %d\n minimo: %d\n maximo: %d\n", abb_root(tree),
                                                            abb_min(tree),
                                                            abb_max(tree));
            } else {
                printf("\nÁrbol vacío\n");
            }
        }

    }
    abb_destroy(tree);
    exit(EXIT_SUCCESS);
}

abb abb_from_file(const char *filepath) {
    FILE *file = NULL;
    abb read_tree;

    read_tree = abb_empty();
    file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int i = 0u;
    unsigned int size = 0u;
    int res = 0;
    res = fscanf( file, " %u ", &size);
    if (res != 1) {
        fprintf(stderr, "Invalid format.\n");
        exit(EXIT_FAILURE);
    }
    while (i < size) {
        abb_elem elem;
        res = fscanf(file," %d ", &(elem));
        if (res != 1) {
            fprintf(stderr, "Invalid array.\n");
            exit(EXIT_FAILURE);
        }
        read_tree = abb_add(read_tree, elem);

       ++i;
    }
    fclose(file);
    return read_tree;
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* parse the file to obtain an abb with the elements */
    abb tree = abb_from_file(filepath);


    printeo(tree);

    tree = abb_destroy(tree);
    /*
     * Modificar e implementar con un ciclo una interfaz que permita al usuario
     * realizar una de las siguientes operaciones en cada iteración:
     *
     * 1 ........ Mostrar árbol por pantalla
     * 2 ........ Agregar un elemento
     * 3 ........ Eliminar un elemento
     * 4 ........ Chequear existencia de elemento
     * 5 ........ Mostrar longitud del árbol
     * 6 ........ Mostrar raiz, máximo y mínimo del árbol
     * 7 ........ Salir
     *
     * Se debe solicitar un número de entrada para realizar una de las acciones.
     *
     * Para las opciones 2, 3 y 4 se le deberá pedir al usuario que ingrese el
     * elemento a agregar, eliminar o chequear respectivamente.
     *
     * Al salir debe liberarse toda la memoria utilizada.
     *
     */
    return (EXIT_SUCCESS);
}
