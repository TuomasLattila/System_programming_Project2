#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readFromInput(char *searchTerm);
void readFromFile(char *searchTerm, char *fileName);

int main(int argc, char *argv[]) {

    if (argc < 2) { //check if no arguments given
        fprintf(stderr, "my-grep: searchterm [file ...]\n");
        exit(1);
    }

    switch (argc)
    {
    case 2: //only search term given. Reads from stdin
        readFromInput(argv[1]);
        break;
    
    default: //searchterm and file/files given.
        for (int i = 2; i < argc; i++) { // lopps through the files
            readFromFile(argv[1], argv[i]);
            printf("\n\n");
        };
        break;
    }

    return 0;
};

void readFromInput(char *pSearchTerm) {
    char *pRow = NULL;
    size_t len = 0;
    size_t bufferSize = 10;
    __ssize_t read = -1;
    char *pPrint = NULL;

    if ((pPrint = (char *) malloc(bufferSize)) == NULL) { //initial allocation
        fprintf(stderr, "malloc failed\n");
        exit(1);
    };
    strcpy(pPrint, "\0");//preventing issues with the strcat() with this code.

    printf("Write multiple lines (end: ctrl+D):\n\n");
    while ((read = getline(&pRow, &len, stdin)) != -1) {
        if (strstr(pRow, pSearchTerm) != NULL) {
            bufferSize = bufferSize + read; //add rows size for realloc
            if ((pPrint = (char *) realloc(pPrint, bufferSize)) == NULL) {// re-allocates the variable to fit new row
                fprintf(stderr, "realloc failed\n");
                exit(1);
            };
            strcat(pPrint, pRow); // append row containing the search term
        };
    };
    if (feof(stdin)) { //if writing ended, prints the rows containing the search term
        printf("\nWriting ended.\n\nLines where the term is included:\n\n");
        printf("%s",pPrint);
    } else if (ferror(stdin)) {
        fprintf(stderr, "Reading from stdin failed");
        free(pRow);
        free(pPrint);
        exit(1);
    }
    free(pRow); // free allocated memories
    free(pPrint);
    return;
};

void readFromFile(char *pSearchTerm, char *pFileName) {
    FILE *file;
    char *pRow = NULL;
    size_t len = 0;
    __ssize_t read = -1;

    if ((file = fopen(pFileName, "r")) == NULL) {
        fprintf(stderr, "my-grep: cannot open file\n");
        exit(1);
    };
    while ((read = getline(&pRow, &len, file)) != -1) { //read row by row and print if search term is found
        if (strstr(pRow, pSearchTerm) != NULL) {
            printf("%s", pRow);
        };    
    };
    fclose(file);
    free(pRow);
    return;
};