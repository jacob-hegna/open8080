#include <stdlib.h>
#include <stdio.h>

#include "disassembler.h"

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

void init_state(State *state);
void emulate_opcode(State *state);
uint8_t parity(uint16_t p);
void dump_state(State *state);

int emulate(char *filename) {
    State state;
    init_state(&state);

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

    dump_state(&state);

    free(state.memory);

    return 0;
}

void init_state(State *state) {
    state->a = 0;
    state->b = 0;
    state->c = 0;
    state->d = 0;
    state->e = 0;
    state->h = 0;
    state->l = 0;
    state->sp = 0;
    state->pc = 0;
    state->memory = NULL;
    state->cc.z = 0;
    state->cc.s = 0;
    state->cc.p = 0;
    state->cc.cy = 0;
    state->cc.ac = 0;
    state->cc.pad = 0;
}

uint8_t parity(uint16_t p) {
    uint8_t amt = 0;
    uint16_t o = 1;
    for(int i = 0; i < 16; ++i) {
        if(p & (o << i)) ++amt;
    }
    return (amt % 2 == 1);
}

void dump_state(State *state) {
    printf(" -- Printout of 8080 state -- \n");
    printf("registers:\n  a: %02x\n  b: %02x\n  c: %02x\n  d: %02x\n  e: %02x\n",
                          state->a,  state->b,  state->c,  state->d,  state->e);
    printf("  h: %02x\n  l: %02x\n", state->h, state->l);
    printf("sp: %04x\n", state->sp);
    printf("pc: %04x\n", state->pc);
    printf("flags:\n");
    printf("  s: %i\n  z: %i\n  p: %i\n  cy: %i\n  ac: %i\n",
        state->cc.s, state->cc.z, state->cc.p, state->cc.cy, state->cc.ac);
}

void unimplemented_opcode(State *state) {
    printf("ERROR: unimplemented instruction: ");
    opcode(state->memory, state->pc);
}

void emulate_opcode(State *state) {
    unsigned char *opcode = &state->memory[state->pc];
    uint16_t answer = 0;
    switch(*opcode) {
        case 0x00: break;
        case 0x01: // LXI B, word
            state->c = opcode[1];
            state->b = opcode[2];
            state->pc += 2;
            break;

        case 0x80: // ADD B
            answer = (uint16_t) state->a + (uint16_t) state->b;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = (answer & 0x80);
            state->cc.cy = (answer > 0xff);
            state->cc.p = parity(answer & 0xff);
            state->a = answer & 0xff;
            break;
        case 0x81: // ADD C
            answer = (uint16_t) state->a + (uint16_t) state->c;
            state->cc.z = ((answer & 0xff) == 0);
            state->cc.s = (answer & 0x80);
            state->cc.cy = (answer > 0xff);
            state->cc.p = parity(answer & 0xff);
            state->a = answer & 0xff;
            break;

        case 0x3e: // MVI A, d8
            state->a = opcode[1];
            ++state->pc;
            break;
        case 0x06: // MVI B, d8
            state->b = opcode[1];
            ++state->pc;
            break;
        case 0x0e: // MVI C, d8
            state->c = opcode[1];
            ++state->pc;
            break;
        case 0x16: // MVI D, d8
            state->d = opcode[1];
            ++state->pc;
            break;
        case 0x1e: // MVI E, d8
            state->e = opcode[1];
            ++state->pc;
            break;
        case 0x26: // MVI H, d8
            state->h = opcode[1];
            ++state->pc;
            break;
        case 0x2e: // MVI L, d8
            state->l = opcode[1];
            ++state->pc;
            break;

        default:
            unimplemented_opcode(state);
            break;
    }
    ++state->pc;
}