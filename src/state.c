#include "state.h"

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
