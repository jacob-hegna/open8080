#ifndef __OPCODES_ASM_H_
#define __OPCODES_ASM_H_

#include <string.h>

inline void mvi_asm(char *reg, char *word, FILE *file) {
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

inline void add_asm(char *reg, FILE *file) {
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

inline void sub_asm(char *reg, FILE *file) {
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

inline void dcr_asm(char *reg, FILE *file) {
    unsigned char buffer[] = {0};
    if(strcmp(reg, "B") == 0) buffer[0] = 0x05;
    else if(strcmp(reg, "C") == 0) buffer[0] = 0x0d;
    else if(strcmp(reg, "D") == 0) buffer[0] = 0x15;
    else if(strcmp(reg, "E") == 0) buffer[0] = 0x1d;
    else if(strcmp(reg, "H") == 0) buffer[0] = 0x25;
    else if(strcmp(reg, "L") == 0) buffer[0] = 0x2d;
    else if(strcmp(reg, "M") == 0) buffer[0] = 0x35;
    else if(strcmp(reg, "A") == 0) buffer[0] = 0x3d;
    fwrite(buffer, sizeof(buffer), 1, file);
}

inline void inr_asm(char *reg, FILE *file) {
    unsigned char buffer[] = {0};
    if(strcmp(reg, "B") == 0) buffer[0] = 0x04;
    else if(strcmp(reg, "C") == 0) buffer[0] = 0x0c;
    else if(strcmp(reg, "D") == 0) buffer[0] = 0x14;
    else if(strcmp(reg, "E") == 0) buffer[0] = 0x1c;
    else if(strcmp(reg, "H") == 0) buffer[0] = 0x24;
    else if(strcmp(reg, "L") == 0) buffer[0] = 0x2e;
    else if(strcmp(reg, "M") == 0) buffer[0] = 0x34;
    else if(strcmp(reg, "A") == 0) buffer[0] = 0x3c;
    fwrite(buffer, sizeof(buffer), 1, file);
}

inline void ana_asm(char *reg, FILE *file) {
    unsigned char buffer[] = {0};
    if(strcmp(reg, "B") == 0) buffer[0] = 0xa0;
    else if(strcmp(reg, "C") == 0) buffer[0] = 0xa1;
    else if(strcmp(reg, "D") == 0) buffer[0] = 0xa2;
    else if(strcmp(reg, "E") == 0) buffer[0] = 0xa3;
    else if(strcmp(reg, "H") == 0) buffer[0] = 0xa4;
    else if(strcmp(reg, "L") == 0) buffer[0] = 0xa5;
    else if(strcmp(reg, "M") == 0) buffer[0] = 0xa6;
    else if(strcmp(reg, "A") == 0) buffer[0] = 0xa7;
    fwrite(buffer, sizeof(buffer), 1, file);
}

#endif