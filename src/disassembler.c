#include <stdlib.h>
#include <stdio.h>

/*
 * The prototyping is probably not necessary, but the opcode lookup-table
 * is way too big, so I'm just gonna stick main first
 */
int opcode(unsigned char *buffer, int pc);

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("Usage: %s [binary file]\n", argv[0]);
        exit(1);
    }
    FILE *file = fopen(argv[1], "rb");
    if(file == NULL) {
        printf("Error: cannot open '%s'\n", argv[1]);
        exit(1);
    }

    fseek(file, 0L, SEEK_END);
    int fsize = ftell(file);
    fseek(file, 0L, SEEK_SET);

    unsigned char *hexdump = malloc(fsize);
    fread(hexdump, fsize, 1, file);

    int pc = 0;
    while(pc < fsize) {
        pc += opcode(hexdump, pc);
    }

    free(hexdump);
    fclose(file);
    exit(0);
}

int opcode(unsigned char *buffer, int pc) {
    int bytes = 1;

    switch(buffer[pc]) {
        case 0x00: printf("NOP"); break;
        case 0x01: printf("LXI B, #$%02x%02x",buffer[pc+2],buffer[pc+1]); bytes=3; break;
        case 0x02: printf("STAX B"); break;
        case 0x03: printf("INX B"); break;
        case 0x04: printf("INR B"); break;
        case 0x05: printf("DCR B"); break;
        case 0x06: printf("MVI B, #$%02x",buffer[pc+1]); bytes=2; break;
        case 0x07: printf("RLC"); break;
        case 0x08: break;
        case 0x09: printf("DAD B"); break;
        case 0x0a: printf("LDAX B"); break;
        case 0x0b: printf("DCX B"); break;
        case 0x0c: printf("INR C"); break;
        case 0x0d: printf("DCR C"); break;
        case 0x0e: printf("MVI C, #$%02x%02x",buffer[pc+2],buffer[pc+1]); bytes=2; break;
        case 0x0f: printf("RRC"); break;
        case 0x10: break;
        case 0x11: printf("LXI D, #$%02x%02x",buffer[pc+2],buffer[pc+1]); bytes=3; break;
        case 0x12: printf("STAX D"); break;
        case 0x13: printf("INX D"); break;
        case 0x14: printf("INR D"); break;
        case 0x15: printf("DCR D"); break;
        case 0x16: printf("MVI D, #$%02x", buffer[pc+2]), bytes=2; break;
        case 0x17: printf("RAL"); break;
        case 0x18: break;
        case 0x19: printf("DAD D"); break;
        case 0x1a: printf("LDAX E"); break;
        case 0x1b: printf("DCX D"); break;
        case 0x1c: printf("INR E"); break;
        case 0x1d: printf("DCR E"); break;
        case 0x1e: printf("MVI E, #$%02x%02x",buffer[pc+2],buffer[pc+1]); bytes=3; break;
        case 0x1f: printf("RAR"); break;
        case 0x20: printf("RIM"); break;
        case 0x21: printf("LXI H, #$%02x%02x",buffer[pc+2],buffer[pc+1]); bytes=3; break;
        case 0x22: printf("SHLD #$%02x%02x",buffer[pc+2],buffer[pc+1]); bytes=3; break;
        case 0x23: printf("INX H"); break;
        case 0x24: printf("INR H"); break;
        case 0x25: printf("DCR H"); break;
        case 0x26: printf("MVI H, #$%02x",buffer[pc+1]); bytes=2; break;
        case 0x27: printf("DAA"); break;
        case 0x28: break;
        case 0x29: printf("DAD H"); break;
        case 0x2a: printf("LHLD #$%02x%02x",buffer[pc+2],buffer[pc+1]); bytes=3; break;
        case 0x2b: printf("DCX H"); break;
        case 0x2c: printf("INR L"); break;
        case 0x2d: printf("DCR L"); break;
        case 0x2e: printf("LXI SP, #$%02x%02x",buffer[pc+2],buffer[pc+1]); bytes=3; break;
        case 0x2f: printf("CMA"); break;
        case 0x30: printf("SIM"); break;
        case 0x31: printf("LXI SP, #$%02x%02x",buffer[pc+2],buffer[pc+1]); bytes=3; break;
        case 0x32: printf("STA #$%02x%02x",buffer[pc+2],buffer[pc+1]); bytes=3; break;
        case 0x33: printf("INX SP"); break;
        case 0x34: printf("INR M"); break;
        case 0x35: printf("DCR M"); break;
        case 0x36: printf("MVI M, #$%02x",buffer[pc+1]); bytes=2; break;
        case 0x37: printf("STC"); break;
        case 0x38: break;
        case 0x39: printf("DAD SP"); break;
        case 0x3a: printf("LDA #$%02x%02x",buffer[pc+2],buffer[pc+1]); bytes=3; break;
    }

    printf("\n");
    return bytes;
}