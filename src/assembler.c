#include <string.h>
#include <stdio.h>

#include "opcodes_asm.h"

void assemble_line(FILE *file, char *line);

char* cstrlwr(char *s) {
    for(;s;++s)
        *s = tolower(*s);
    return s;
}

int assemble(char *filename) {
    FILE *file = fopen(filename, "r");
    if(file == NULL) {
        printf("Error: cannot open '%s'\n", filename);
        exit(1);
    }

    FILE *output = fopen("a.out", "wb");

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

    for(int i = 0; i < line_amt; ++i) {
        assemble_line(output, cstrlwr(lines[i]));
    }

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
    if(strcmp(inst[0], "mvi") == 0) {
        mvi_asm(inst[1], inst[2], file);
    } else if(strcmp(inst[0], "add") == 0) {
        add_asm(inst[1], file);
    } else if(strcmp(inst[0], "sub") == 0) {
        sub_asm(inst[1], file);
    } else if(strcmp(inst[0], "dcr") == 0) {
        dcr_asm(inst[1], file);
    } else if(strcmp(inst[0], "inr") == 0) {
        inr_asm(inst[1], file);
    } else if(strcmp(inst[0], "ana") == 0) {
        ana_asm(inst[1], file);
    } else {
        // should never happen
        // lol
    }
    free(buffer);
}