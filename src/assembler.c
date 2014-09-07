#include <string.h>
#include <stdio.h>

void assemble_line(FILE *file, char *line);

int assemble(char *filename) {
    FILE *file = fopen(filename, "r");
    if(file == NULL) {
        printf("Error: cannot open '%s'\n", filename);
        exit(1);
    }

    FILE *output = fopen("test.bin", "wb");

    fseek(file, 0L, SEEK_END);
    int fsize = ftell(file);
    fseek(file, 0L, SEEK_SET);

    char *chardump = malloc(fsize);
    fread(chardump, fsize, 1, file);
    fclose(file);

    int line_amt = 1;
    for(int i = 0; i < fsize; ++i) {
        if(chardump[i] == '\n') ++line_amt;
    }

    char **lines = malloc(sizeof(char*) * line_amt);

    char *tok = strtok(chardump, "\n");
    for(int i = 0; i < line_amt; ++i) {
        lines[i] = tok;
        tok = strtok(NULL, "\n");
    }
    free(chardump);

    for(int i = 0; i < line_amt; ++i)
        assemble_line(output, lines[i]);

    free(lines);
    fclose(output);
    return 0;
}

void assemble_line(FILE *file, char *line) {
    char *buffer = strtok(line, ", ");
    char *inst[3] = {NULL, NULL, NULL};
    int i = 0;
    while(buffer != NULL) {
        inst[i++] = buffer;
        buffer = strtok(NULL, ", ");
    }
    if(strcmp(inst[0], "MVI") == 0) {
        unsigned char buffer[] = {0, 0};
        if(strcmp(inst[1], "A") == 0) {
            buffer[0] = 0x3e;
            sscanf(inst[2], "%02x", &buffer[1]);
        } else if(strcmp(inst[1], "B") == 0) {
            buffer[0] = 0x06;
            sscanf(inst[2], "%02x", &buffer[1]);
        }
        fwrite(buffer, sizeof(buffer), 1, file);
    } else if(strcmp(inst[0], "ADD") == 0) {
        unsigned char buffer[] = {0};
        if(strcmp(inst[1], "B") == 0) {
            buffer[0] = 0x80;
        }
        fwrite(buffer, sizeof(buffer), 1, file);
    }
}