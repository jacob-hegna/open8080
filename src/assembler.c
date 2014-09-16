#include <string.h>
#include <stdio.h>

void assemble_line(FILE *file, char *line);

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

    for(int i = 0; i < line_amt; ++i)
        assemble_line(output, lines[i]);

    free(lines);
    fclose(output);
    return 0;
}

void mvi(char *reg, char *word, FILE *file) {
    unsigned char buffer[] = {0, 0};
    if(strcmp(reg, "A") == 0) buffer[0] = 0x3e;
    else if(strcmp(reg, "B") == 0) buffer[0] = 0x06;
    else if(strcmp(reg, "C") == 0) buffer[0] = 0x0e;
    else if(strcmp(reg, "D") == 0) buffer[0] = 0x16;
    else if(strcmp(reg, "E") == 0) buffer[0] = 0x1e;
    else if(strcmp(reg, "H") == 0) buffer[0] = 0x26;
    else if(strcmp(reg, "L") == 0) buffer[0] = 0x2e;
    else if(strcmp(reg, "M") == 0) buffer[0] = 0x36;
    sscanf(word, "%02x", &buffer[1]);
    fwrite(buffer, sizeof(buffer), 1, file);
}

void add(char *reg, FILE *file) {
    unsigned char buffer[] = {0};
    if(strcmp(reg, "B") == 0) buffer[0] = 0x80;
    else if(strcmp(reg, "C") == 0) buffer[0] = 0x81;
    else if(strcmp(reg, "D") == 0) buffer[0] = 0x82;
    else if(strcmp(reg, "E") == 0) buffer[0] = 0x83;
    else if(strcmp(reg, "H") == 0) buffer[0] = 0x84;
    else if(strcmp(reg, "L") == 0) buffer[0] = 0x85;
    else if(strcmp(reg, "M") == 0) buffer[0] = 0x86;
    else if(strcmp(reg, "A") == 0) buffer[0] = 0x87;
    fwrite(buffer, sizeof(buffer), 1, file);
}

void sub(char *reg, FILE *file) {
    unsigned char buffer[] = {0};
    if(strcmp(reg, "B") == 0) buffer[0] = 0x90;
    else if(strcmp(reg, "C") == 0) buffer[0] = 0x91;
    else if(strcmp(reg, "D") == 0) buffer[0] = 0x92;
    else if(strcmp(reg, "E") == 0) buffer[0] = 0x93;
    else if(strcmp(reg, "H") == 0) buffer[0] = 0x94;
    else if(strcmp(reg, "L") == 0) buffer[0] = 0x95;
    else if(strcmp(reg, "M") == 0) buffer[0] = 0x96;
    else if(strcmp(reg, "A") == 0) buffer[0] = 0x97;
    fwrite(buffer, sizeof(buffer), 1, file);
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
        mvi(inst[1], inst[2], file);
    } else if(strcmp(inst[0], "ADD") == 0) {
        add(inst[1], file);
    } else {
        sub(inst[1], file);
    }
    free(buffer);
}