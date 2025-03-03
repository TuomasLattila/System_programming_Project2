#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compress(int listCount, char *pFileNames[]);

int main(int argc, char *argv[]) {
    
    if (argc < 2) {// check if no files are given
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }
    compress(argc, argv); //compress given files
    return 0;
}

void compress(int listCount, char *pFileNames[]) {
    FILE *file;
    int count;
    char prev = '\0';
    char c;

    for (int i = 1; i < listCount; i++) {
      if ((file = fopen(pFileNames[i], "r")) == NULL) {
        fprintf(stdout, "error: cannot open file '%s'\n", pFileNames[i]);
        exit(1);
      }

      while(fread(&c, sizeof(char), 1, file)) { //loop through file char by char
	if (prev == '\0') {
	    prev = c;
	    count = 0;
	}
	else if (c != prev) { // if current char different from previous char, craete one entry (count+char)
            fwrite(&count, 4, 1, stdout); //count in binary
            fwrite(&prev, 1, 1, stdout); //char
            prev = c;
            count = 0;
        }
        count++;
      }
      fclose(file);
    }
    fwrite(&count, 4, 1, stdout); //writes the last entry
    fwrite(&prev, 1, 1, stdout);
    return;
}