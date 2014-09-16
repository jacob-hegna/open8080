#ifndef __STATE_H_
#define __STATE_H_

#include <stdlib.h>

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
void dump_state(State *state);

#endif