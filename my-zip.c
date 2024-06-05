#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compress(char *pFileName);

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        printf("my-zip: file1 [file2 ...]\n");
        exit(1);
    }
    for (int i = 1; i < argc; i++) {
        compress(argv[i]);
    }
    //printf("\n");
    return 0;
}

void compress(char *pFileName) {
    FILE *file;
    int count;
    char prev;
    char c;

    if ((file = fopen(pFileName, "r")) == NULL) {
        fprintf(stderr, "error: cannot open file '%s'\n", pFileName);
        exit(1);
    }

    fread(&prev, sizeof(char), 1, file);
    count = 1;

    while(fread(&c, sizeof(char), 1, file)) {
        if (c != prev) {
            fwrite(&count, 4, 1, stdout);
            fwrite(&prev, 1, 1, stdout);
            prev = c;
            count = 0;
        }
        count++;
    }
    fwrite(&count, 4, 1, stdout);
    fwrite(&prev, 1, 1, stdout);
    fclose(file);
    return;
}