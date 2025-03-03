#include <stdio.h>
#include <stdlib.h>
#define MAX 1200

int main(int argc, char *argv[]) {
    FILE *file;
    char buffer[MAX];

    if (argc < 2) { //checks if no arguments given
        exit(0);
    }

    for (int i = 1; i < argc; i++)  { //loops throug the given files
        if ((file = fopen(argv[i], "r")) == NULL) {
            fprintf(stdout, "wcat: cannot open file\n");
            exit(1);
        };
        while (fgets(buffer, MAX, file) != NULL) {//reads and prints the contents
            printf("%s",buffer);
        }
        fclose(file);
    };
    
    return 0;
};