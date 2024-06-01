#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        printf("my-zip: file1 [file2 ...]\n");
        exit(1);
    }
    
    
    return 0;
}

void compress(char *pFileName) {
    FILE *file;
    char entry[5];

    if ((file = fopen(pFileName, "r")) == NULL) {
        fprintf(stderr, "error: cannot open file '%s'\n", pFileName);
        exit(1);
    }
    

    fclose(file);
    return;
}