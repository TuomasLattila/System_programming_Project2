#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compress(char *pFileName);

int main(int argc, char *argv[]) {
    
    if (argc < 2) {// check if no files are given
        printf("my-zip: file1 [file2 ...]\n");
        exit(1);
    }
    for (int i = 1; i < argc; i++) { //loop through the files and compress them
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

    fread(&prev, sizeof(char), 1, file); //read first character
    count = 1;

    while(fread(&c, sizeof(char), 1, file)) { //loop through file char by char
        if (c != prev) { // if current char different from previous char, craete one entry (count+char)
            fwrite(&count, 4, 1, stdout); //count in binary
            fwrite(&prev, 1, 1, stdout); //char
            prev = c;
            count = 0;
        }
        count++;
    }
    fwrite(&count, 4, 1, stdout); //writes the last entry
    fwrite(&prev, 1, 1, stdout);
    printf("\n");
    fclose(file);
    return;
}