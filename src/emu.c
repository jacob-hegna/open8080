#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "disassembler.h"
#include "opcodes_emu.h"
#include "state.h"
#include "opcodes.h"

void emulate_opcode(State *state);

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

void emulate_opcode(State *state) {
    unsigned char *opcode = &state->memory[state->pc];
    switch(*opcode) {
        case NOP: break;
        case LXI_B:
            state->c = opcode[1];
            state->b = opcode[2];
            state->pc += 2;
            break;

        case DCR_B:
            dcr_emu(state, &state->b);
            break;
        case DCR_C:
            dcr_emu(state, &state->c);
            break;
        case DCR_D:
            dcr_emu(state, &state->d);
            break;
        case DCR_E:
            dcr_emu(state, &state->e);
            break;
        case DCR_H:
            dcr_emu(state, &state->h);
            break;
        case DCR_L:
            dcr_emu(state, &state->l);
            break;
        case DCR_A:
            dcr_emu(state, &state->a);
            break;

        case INR_B:
            inr_emu(state, &state->b);
            break;
        case INR_C:
            inr_emu(state, &state->c);
            break;
        case INR_D:
            inr_emu(state, &state->d);
            break;
        case INR_E:
            inr_emu(state, &state->e);
            break;
        case INR_H:
            inr_emu(state, &state->h);
            break;
        case INR_L:
            inr_emu(state, &state->l);
            break;
        case INR_A:
            inr_emu(state, &state->a);
            break;

        case ADD_B:
            add_emu(state, &state->b);
            break;
        case ADD_C:
            add_emu(state, &state->c);
            break;
        case ADD_D:
            add_emu(state, &state->d);
            break;
        case ADD_E:
            add_emu(state, &state->e);
            break;
        case ADD_H:
            add_emu(state, &state->h);
            break;
        case ADD_L:
            add_emu(state, &state->l);
            break;
        case ADD_A:
            add_emu(state, &state->a);
            break;

        case SUB_B:
            sub_emu(state, &state->b);
            break;
        case SUB_C:
            sub_emu(state, &state->c);
            break;
        case SUB_D:
            sub_emu(state, &state->d);
            break;
        case SUB_E:
            sub_emu(state, &state->e);
            break;
        case SUB_H:
            sub_emu(state, &state->h);
            break;
        case SUB_L:
            sub_emu(state, &state->l);
            break;
        case SUB_A:
            sub_emu(state, &state->a);
            break;

        case ANA_B:
            ana_emu(state, &state->b);
            break;
        case ANA_C:
            ana_emu(state, &state->c);
            break;
        case ANA_D:
            ana_emu(state, &state->d);
            break;
        case ANA_E:
            ana_emu(state, &state->e);
            break;
        case ANA_H:
            ana_emu(state, &state->h);
            break;
        case ANA_L:
            ana_emu(state, &state->l);
            break;
        case ANA_A:
            ana_emu(state, &state->a);

        case MVI_A:
            state->a = opcode[1];
            ++state->pc;
            break;
        case MVI_B:
            state->b = opcode[1];
            ++state->pc;
            break;
        case MVI_C:
            state->c = opcode[1];
            ++state->pc;
            break;
        case MVI_D:
            state->d = opcode[1];
            ++state->pc;
            break;
        case MVI_E:
            state->e = opcode[1];
            ++state->pc;
            break;
        case MVI_H:
            state->h = opcode[1];
            ++state->pc;
            break;
        case MVI_L:
            state->l = opcode[1];
            ++state->pc;
            break;

        default:
            unimplemented_opcode(state);
            break;
    }
    ++state->pc;
}