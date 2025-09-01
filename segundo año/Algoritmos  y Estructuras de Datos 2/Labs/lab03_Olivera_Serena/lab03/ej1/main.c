#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 1000

static void dump(char a[], unsigned int length) {
    printf("\"");
    for (unsigned int j=0u; j < length; j++) {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n\n");
}

char *parse_filepath(int argc, char *argv[]) {

    char *result = NULL;

    if (argc < 2) {
        fprintf(stderr, "missing filepath\n");
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return result;
}

unsigned int
data_from_file( const char *path, unsigned int indexes[], char letters[], unsigned int max_size)
{
	FILE *file;
	unsigned int count_lett = 0;
	
	file = fopen (path, "r");
	if (file==NULL){
        	fprintf(stdout, "The file %s does not exists\n", path);
        	exit(EXIT_FAILURE);
    	}
    	
	while (!feof(file))
	{
		fscanf(file, " %u -> *%c* \n ", &indexes[count_lett], &letters[count_lett]);    		
		if (indexes[count_lett] >= max_size)
		{
			fprintf(stdout, "The length exceeds the limit");
			exit(EXIT_FAILURE);
		}
		count_lett = count_lett + 1;
	}
	
	fclose(file);
	
	return count_lett;
}

void sort (unsigned int indexes[], char letters[], unsigned int max_size, char ordered[])
{
	unsigned int pos = 0;
	unsigned int changer = 0;
	while (pos < max_size)
	{
		changer = indexes[pos];
		ordered[changer] = letters[pos];
		pos++;
	}
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;

    filepath = parse_filepath(argc, argv);
    
    
    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE];
    unsigned int length = data_from_file (filepath,indexes, letters, MAX_SIZE);
       
    sort(indexes, letters, length, sorted);

    dump(sorted, length);

    return EXIT_SUCCESS;
}

