#include <string.h>
#include <stdio.h>
/*
int main(int argc, char *argv[]) {
    if(argc < 3) {
        printf("Usage: %s [assembly file] [8080 binary file]\n", argv[0]);
        exit(1);
    }
    FILE *file = fopen(argv[1], "r");
    if(file == NULL) {
        printf("Error: cannot open '%s'\n", argv[1]);
        exit(1);
    }

    fseek(file, 0L, SEEK_END);
    int fsize = ftell(file);
    fseek(file, 0L, SEEK_SET);

    unsigned char *asmdump = malloc(fsize);
    fread(asmdump, fsize, 1, file);
    fclose(file);

    char *tok = strtok();

    while(tok != NULL);

    fclose(file);
    exit(0);
}
*/