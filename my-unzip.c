#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void uncompress(char *pFileName);

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        printf("my-unzip: file1 [file2 ...]\n");
        exit(1);
    }
    for (int i = 1; i < argc; i++) {
        uncompress(argv[i]);
    }
    //printf("\n");
    return 0;
}

void uncompress(char *pFileName) {
    FILE *file;
    char c;
    int count;

    if ((file = fopen(pFileName, "rb")) == NULL) {
        fprintf(stderr, "error: cannot open file '%s'\n", pFileName);
        exit(1);
    }
    
    while (fread(&count, 4, 1, file) && fread(&c, 1, 1, file)) {
        for (int i = 0; i < count; i++) {
            printf("%c", c);
        }
    }

    fclose(file);
    return;
}