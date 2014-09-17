#ifndef __OPCODES_EMU_H_
#define __OPCODES_EMU_H_

#include <stdint.h>
#include <stdlib.h>

#include "state.h"

inline uint8_t parity(uint16_t p) {
    uint8_t amt = 0;
    uint16_t o = 1;
    for(int i = 0; i < 16; ++i) {
        if(p & (o << i)) ++amt;
    }
    return (amt % 2 == 1);
}

inline void add_emu(State *state, uint8_t *x) {
    uint16_t answer = (uint16_t) state->a + (uint16_t) *x;
    state->cc.z = ((answer & 0xff) == 0);
    state->cc.s = (answer & 0x80);
    state->cc.cy = (answer > 0xff);
    state->cc.p = parity(answer & 0xff);
    state->a = answer & 0xff;
}

inline void sub_emu(State *state, uint8_t *x) {
    uint16_t answer = (uint16_t) state->a - (uint16_t) *x;
    state->cc.z = ((answer & 0xff) == 0);
    state->cc.s = (answer & 0x80);
    state->cc.cy = (answer > 0xff);
    state->cc.p = parity(answer & 0xff);
    state->a = answer & 0xff;
}

inline void dcr_emu(State *state, uint8_t *x) {
    --(*x);
    state->cc.z = ((*x & 0xff) == 0);
    state->cc.s = (*x & 0x80);
    state->cc.p = parity(*x & 0xff);
}

inline void inr_emu(State *state, uint8_t *x) {
    ++(*x);
    state->cc.z = ((*x & 0xff) == 0);
    state->cc.s = (*x & 0x80);
    state->cc.p = parity(*x & 0xff);
}

inline void ana_emu(State *state, uint8_t *x) {
    state->a = (uint16_t) state->a & (uint16_t) *x;
    state->cc.z = ((state->a & 0xff) == 0);
    state->cc.s = (state->a & 0x80);
    state->cc.cy = (state->a > 0xff);
    state->cc.p = parity(state->a & 0xff);
}

#endif