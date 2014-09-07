#include <stdlib.h>
#include <stdio.h>

typedef struct {
    uint8_t z   : 1;
    uint8_t s   : 1;
    uint8_t p   : 1;
    uint8_t cy  : 1;
    uint8_t ac  : 1;
    uint8_t pad : 3;
} ConditionCodes;

typedef struct {
    uint8_t  a;
    uint8_t  b;
    uint8_t  c;
    uint8_t  d;
    uint8_t  e;
    uint8_t  h;
    uint8_t  l;
    uint16_t sp;
    uint16_t pc;
    uint8_t *memory;
    ConditionCodes cc;
    uint8_t int_enable;
} State;

void emulate_opcode(State *state);

int emulate(char *filename) {
    State state;

    FILE *file = fopen(filename, "rb");
    if(file == NULL) {
        printf("Error: cannot open '%s'\n", filename);
        return -1;
    }

    fseek(file, 0L, SEEK_END);
    int fsize = ftell(file);
    fseek(file, 0L, SEEK_SET);

    state.memory = malloc(fsize);
    fread(state.memory, fsize, 1, file);
    fclose(file);

    while(state.pc < fsize) {
        emulate_opcode(&state);
    }

    free(state.memory);

    return 0;
}

void emulate_opcode(State *state) {
    unsigned char *opcode = &state->memory[state->pc];
    switch(*opcode) {
        case 0x00: break;
        case 0x01:
            state->c = opcode[1];
            state->b = opcode[2];
            state->pc += 2;
            break;
    }
    ++state->pc;
}