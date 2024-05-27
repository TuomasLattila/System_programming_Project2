#include <stdio.h>
#include <stdlib.h>
#define MAX 1200

int main(int argc, char *argv[]) {
    FILE *file;
    char buffer[MAX];

    if (argc < 2) {
        exit(0);
    }

    for (int i = 1; i < argc; i++)  {
        if ((file = fopen(argv[i], "r")) == NULL) {
            fprintf(stderr, "my-cat: cannot open file\n");
            exit(1);
        };
        while (fgets(buffer, MAX, file) != NULL) {
            printf("%s",buffer);
        }
        printf("\n\n");
        fclose(file);
    };
    
    return 0;
};