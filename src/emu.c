#include <stdlib.h>
#include <stdio.h>

#include "disassembler.h"
#include "opcodes_emu.h"
#include "state.h"

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


void unimplemented_opcode(State *state) {
    printf("ERROR: unimplemented instruction: ");
    opcode(state->memory, state->pc);
}

#define OPT_EMU(opt, reg) opt(state, &state->reg)
void emulate_opcode(State *state) {
    unsigned char *opcode = &state->memory[state->pc];
    switch(*opcode) {
        case 0x00: break;
        case 0x01: // LXI B, word
            state->c = opcode[1];
            state->b = opcode[2];
            state->pc += 2;
            break;

        case 0x05: // DCR B
            dcr_emu(state, &state->b);
            break;
        case 0x0d: // DCR C
            dcr_emu(state, &state->c);
            break;
        case 0x15: // DCR D
            dcr_emu(state, &state->d);
            break;
        case 0x1d: // DCR E
            dcr_emu(state, &state->e);
            break;
        case 0x25: // DCR H
            dcr_emu(state, &state->h);
            break;
        case 0x2d: // DCR L
            dcr_emu(state, &state->l);
            break;
        case 0x3d: // DCR A
            dcr_emu(state, &state->a);
            break;

        case 0x04: // INR B
            inr_emu(state, &state->b);
            break;
        case 0x0c: // INR C
            inr_emu(state, &state->c);
            break;
        case 0x14: // INR D
            inr_emu(state, &state->d);
            break;
        case 0x1c: // INR E
            inr_emu(state, &state->e);
            break;
        case 0x24: // INR H
            inr_emu(state, &state->h);
            break;
        case 0x2c: // INR L
            inr_emu(state, &state->l);
            break;
        case 0x3c: // INR A
            inr_emu(state, &state->a);
            break;

        case 0x80: // ADD B
            add_emu(state, &state->b);
            break;
        case 0x81: // ADD C
            add_emu(state, &state->c);
            break;
        case 0x82: // ADD D
            add_emu(state, &state->d);
            break;
        case 0x83: // ADD E
            add_emu(state, &state->e);
            break;
        case 0x84: // ADD H
            add_emu(state, &state->h);
            break;
        case 0x85: // ADD L
            add_emu(state, &state->l);
            break;
        case 0x87: // ADD A
            add_emu(state, &state->a);
            break;

        case 0x90: // SUB B
            sub_emu(state, &state->b);
            break;
        case 0x91: // SUB C
            sub_emu(state, &state->c);
            break;
        case 0x92: // SUB D
            sub_emu(state, &state->d);
            break;
        case 0x93: // SUB E
            sub_emu(state, &state->e);
            break;
        case 0x94: // SUB H
            sub_emu(state, &state->h);
            break;
        case 0x95: // SUB L
            sub_emu(state, &state->l);
            break;
        case 0x97: // SUB A
            sub_emu(state, &state->a);
            break;

        case 0xa0: // ANA B
            ana_emu(state, &state->b);
            break;
        case 0xa1: // ANA C
            ana_emu(state, &state->c);
            break;
        case 0xa2: // ANA D
            ana_emu(state, &state->d);
            break;
        case 0xa3: // ANA E
            ana_emu(state, &state->e);
            break;
        case 0xa4: // ANA H
            ana_emu(state, &state->h);
            break;
        case 0xa5: // ANA L
            ana_emu(state, &state->l);
            break;
        case 0xa7: // ANA A
            ana_emu(state, &state->a);

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