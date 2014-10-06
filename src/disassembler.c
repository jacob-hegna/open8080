/*
 * Shoutout to www.emulator101.com for a solid tutorial on the 8080,
 * you have pretty big domain-handling bugs, but you know your schtuff
 */
#include <stdlib.h>
#include <stdio.h>

/*
 * The prototyping is probably not necessary, but the opcode lookup-table
 * is way too big, so I'm just gonna stick main first
 */
int opcode(unsigned char *buffer, int pc);
inline int format_opcode(unsigned char *buffer, int pc, char s[], int size);

int disassemble(char *filename) {
    FILE *file = fopen(filename, "rb");
    if(file == NULL) {
        printf("Error: cannot open '%s'\n", filename);
        return -1;
    }

    fseek(file, 0L, SEEK_END);
    int fsize = ftell(file);
    fseek(file, 0L, SEEK_SET);

    unsigned char *hexdump = malloc(fsize);
    fread(hexdump, fsize, 1, file);
    fclose(file);

    int pc = 0;
    while(pc < fsize) {
        pc += opcode(hexdump, pc);
    }

    free(hexdump);
    return 0;
}

/*
 * This macro/function combination may not be the prettiest, but it makes my
 * life a whole lot easier when defining opcodes #sorrynotsorry
 */
#define OP_1(a) (bytes = format_opcode(buffer, pc, a, 1))
#define OP_2(a, b) (bytes = format_opcode(buffer, pc, a, b))
#define GET_OP(a, b, name, ...) name
#define OP(...) GET_OP(__VA_ARGS__, OP_2, OP_1)(__VA_ARGS__)
inline int format_opcode(unsigned char *buffer, int pc, char s[], int size) {
    switch(size) {
        case 1:
            printf(" %02x        ", buffer[pc]);
            break;
        case 2:
            printf(" %02x %02x     ", buffer[pc], buffer[pc+1]);
            break;
        case 3:
            printf(" %02x %02x %02x  ", buffer[pc], buffer[pc+1], buffer[pc+2]);
            break;
    }

    printf(s, (size >= 2) ? (
        (size == 2) ? buffer[pc+1] : buffer[pc+2]
    ) : 0, (size == 3) ? buffer[pc+1] : 0);
    return size;
}

int opcode(unsigned char *buffer, int pc) {
    int bytes = 1;

    printf("%04x  ", pc);

    switch(buffer[pc]) {
        // How 'bout them opcodes
        case 0x00: OP("NOP");                      break;
        case 0x01: OP("LXI B, #$%02x%02x", 3);     break;
        case 0x02: OP("STAX B");                   break;
        case 0x03: OP("INX B");                    break;
        case 0x04: OP("INR B");                    break;
        case 0x05: OP("DCR B");                    break;
        case 0x06: OP("MVI B, #$%02x", 2);         break;
        case 0x07: OP("RLC");                      break;
        case 0x08: OP("NOP");                      break;
        case 0x09: OP("DAD B");                    break;
        case 0x0a: OP("LDAX B");                   break;
        case 0x0b: OP("DCX B");                    break;
        case 0x0c: OP("INR C");                    break;
        case 0x0d: OP("DCR C");                    break;
        case 0x0e: OP("MVI C, #$%02x", 2);         break;
        case 0x0f: OP("RRC");                      break;
        case 0x10: OP("NOP");                      break;
        case 0x11: OP("LXI D, #$%02x%02x", 3);     break;
        case 0x12: OP("STAX D");                   break;
        case 0x13: OP("INX D");                    break;
        case 0x14: OP("INR D");                    break;
        case 0x15: OP("DCR D");                    break;
        case 0x16: OP("MVI D, #$%02x", 2);         break;
        case 0x17: OP("RAL");                      break;
        case 0x18: OP("NOP");                      break;
        case 0x19: OP("DAD D");                    break;
        case 0x1a: OP("LDAX E");                   break;
        case 0x1b: OP("DCX D");                    break;
        case 0x1c: OP("INR E");                    break;
        case 0x1d: OP("DCR E");                    break;
        case 0x1e: OP("MVI E, #$%02x", 2);         break;
        case 0x1f: OP("RAR");                      break;
        case 0x20: OP("RIM");                      break;
        case 0x21: OP("LXI H, #$%02x%02x", 3);     break;
        case 0x22: OP("SHLD #$%02x%02x", 3);       break;
        case 0x23: OP("INX H");                    break;
        case 0x24: OP("INR H");                    break;
        case 0x25: OP("DCR H");                    break;
        case 0x26: OP("MVI H, #$%02x", 2);         break;
        case 0x27: OP("DAA");                      break;
        case 0x28: OP("NOP");                      break;
        case 0x29: OP("DAD H");                    break;
        case 0x2a: OP("LHLD #$%02x%02x", 3);       break;
        case 0x2b: OP("DCX H");                    break;
        case 0x2c: OP("INR L");                    break;
        case 0x2d: OP("DCR L");                    break;
        case 0x2e: OP("MVI L, #$%02x%02x", 3);    break;
        case 0x2f: OP("CMA");                      break;
        case 0x30: OP("SIM");                      break;
        case 0x31: OP("LXI SP, #$%02x%02x", 3);    break;
        case 0x32: OP("STA #$%02x%02x", 3);        break;
        case 0x33: OP("INX SP");                   break;
        case 0x34: OP("INR M");                    break;
        case 0x35: OP("DCR M");                    break;
        case 0x36: OP("MVI M, #$%02x", 2);         break;
        case 0x37: OP("STC");                      break;
        case 0x38: OP("NOP");                      break;
        case 0x39: OP("DAD SP");                   break;
        case 0x3a: OP("LDA #$%02x%02x", 3);        break;
        case 0x3b: OP("DCX SP");                   break;
        case 0x3c: OP("INR A");                    break;
        case 0x3d: OP("DCR A");                    break;
        case 0x3e: OP("MVI A, #$%02x", 2);         break;
        case 0x3f: OP("CMC");                      break;
        case 0x40: OP("MOV B, B");                 break;
        case 0x41: OP("MOV B, C");                 break;
        case 0x42: OP("MOV B, D");                 break;
        case 0x43: OP("MOV B, E");                 break;
        case 0x44: OP("MOV B, H");                 break;
        case 0x45: OP("MOV B, L");                 break;
        case 0x46: OP("MOV B, M");                 break;
        case 0x47: OP("MOV B, A");                 break;
        case 0x48: OP("MOV C, B");                 break;
        case 0x49: OP("MOV C, C");                 break;
        case 0x4a: OP("MOV C, D");                 break;
        case 0x4b: OP("MOV C, E");                 break;
        case 0x4c: OP("MOV C, H");                 break;
        case 0x4d: OP("MOV C, L");                 break;
        case 0x4e: OP("MOV C, M");                 break;
        case 0x4f: OP("MOV C, A");                 break;
        case 0x50: OP("MOV D, B");                 break;
        case 0x51: OP("MOV D, C");                 break;
        case 0x52: OP("MOV D, D");                 break;
        case 0x53: OP("MOV D, E");                 break;
        case 0x54: OP("MOV D, H");                 break;
        case 0x55: OP("MOV D, L");                 break;
        case 0x56: OP("MOV D, M");                 break;
        case 0x57: OP("MOV D, A");                 break;
        case 0x58: OP("MOV E, B");                 break;
        case 0x59: OP("MOV E, C");                 break;
        case 0x5a: OP("MOV E, D");                 break;
        case 0x5b: OP("MOV E, E");                 break;
        case 0x5c: OP("MOV E, H");                 break;
        case 0x5d: OP("MOV E, L");                 break;
        case 0x5e: OP("MOV E, M");                 break;
        case 0x5f: OP("MOV E, A");                 break;
        case 0x60: OP("MOV H, B");                 break;
        case 0x61: OP("MOV H, C");                 break;
        case 0x62: OP("MOV H, D");                 break;
        case 0x63: OP("MOV H, E");                 break;
        case 0x64: OP("MOV H, H");                 break;
        case 0x65: OP("MOV H, L");                 break;
        case 0x66: OP("MOV H, M");                 break;
        case 0x67: OP("MOV H, A");                 break;
        case 0x68: OP("MOV L, B");                 break;
        case 0x69: OP("MOV L, C");                 break;
        case 0x6a: OP("MOV L, D");                 break;
        case 0x6b: OP("MOV L, E");                 break;
        case 0x6c: OP("MOV L, H");                 break;
        case 0x6d: OP("MOV L, L");                 break;
        case 0x6e: OP("MOV L, M");                 break;
        case 0x6f: OP("MOV L, A");                 break;
        case 0x70: OP("MOV M, B");                 break;
        case 0x71: OP("MOV M, C");                 break;
        case 0x72: OP("MOV M, D");                 break;
        case 0x73: OP("MOV M, E");                 break;
        case 0x74: OP("MOV M, H");                 break;
        case 0x75: OP("MOV M, L");                 break;
        case 0x76: OP("HLT");                      break;
        case 0x77: OP("MOV M, A");                 break;
        case 0x78: OP("MOV A, B");                 break;
        case 0x79: OP("MOV A, C");                 break;
        case 0x7a: OP("MOV A, D");                 break;
        case 0x7b: OP("MOV A, E");                 break;
        case 0x7c: OP("MOV A, H");                 break;
        case 0x7d: OP("MOV A, L");                 break;
        case 0x7e: OP("MOV A, M");                 break;
        case 0x7f: OP("MOV A, A");                 break;
        case 0x80: OP("ADD B");                    break;
        case 0x81: OP("ADD C");                    break;
        case 0x82: OP("ADD D");                    break;
        case 0x83: OP("ADD E");                    break;
        case 0x84: OP("ADD H");                    break;
        case 0x85: OP("ADD L");                    break;
        case 0x86: OP("ADD M");                    break;
        case 0x87: OP("ADD A");                    break;
        case 0x88: OP("ADC B");                    break;
        case 0x89: OP("ADC C");                    break;
        case 0x8a: OP("ADC D");                    break;
        case 0x8b: OP("ADC E");                    break;
        case 0x8c: OP("ADC H");                    break;
        case 0x8d: OP("ADC L");                    break;
        case 0x90: OP("SUB B");                    break;
        case 0x91: OP("SUB C");                    break;
        case 0x92: OP("SUB D");                    break;
        case 0x93: OP("SUB E");                    break;
        case 0x94: OP("SUB H");                    break;
        case 0x95: OP("SUB L");                    break;
        case 0x96: OP("SUB M");                    break;
        case 0x97: OP("SUB A");                    break;
        case 0x98: OP("SBB B");                    break;
        case 0x99: OP("SBB C");                    break;
        case 0x9a: OP("SBB D");                    break;
        case 0x9b: OP("SBB E");                    break;
        case 0x9c: OP("SBB H");                    break;
        case 0x9d: OP("SBB L");                    break;
        case 0x9e: OP("SBB M");                    break;
        case 0x9f: OP("SBB A");                    break;
        case 0xa0: OP("ANA B");                    break;
        case 0xa1: OP("ANA C");                    break;
        case 0xa2: OP("ANA D");                    break;
        case 0xa3: OP("ANA E");                    break;
        case 0xa4: OP("ANA H");                    break;
        case 0xa5: OP("ANA L"); /* topkek */       break;
        case 0xa6: OP("ANA M");                    break;
        case 0xa7: OP("ANA A");                    break;
        case 0xa8: OP("XRA B");                    break;
        case 0xa9: OP("XRA C");                    break;
        case 0xaa: OP("XRA D");                    break;
        case 0xab: OP("XRA E");                    break;
        case 0xac: OP("XRA H");                    break;
        case 0xad: OP("XRA L");                    break;
        case 0xae: OP("XRA M");                    break;
        case 0xaf: OP("XRA A");                    break;
        case 0xb0: OP("ORA B");                    break;
        case 0xb1: OP("ORA C");                    break;
        case 0xb2: OP("ORA D");                    break;
        case 0xb3: OP("ORA E");                    break;
        case 0xb4: OP("ORA H");                    break;
        case 0xb5: OP("ORA L"); /* topkek */       break;
        case 0xb6: OP("ORA M");                    break;
        case 0xb7: OP("ORA A");                    break;
        case 0xb8: OP("CMP B");                    break;
        case 0xb9: OP("CMP C");                    break;
        case 0xba: OP("CMP D");                    break;
        case 0xbb: OP("CMP E");                    break;
        case 0xbc: OP("CMP H");                    break;
        case 0xbd: OP("CMP L");                    break;
        case 0xbe: OP("CMP M");                    break;
        case 0xbf: OP("CMP A");                    break;
        case 0xc0: OP("RNZ");                      break;
        case 0xc1: OP("POP B");                    break;
        case 0xc2: OP("JNZ #$%02x%02x", 3);        break;
        case 0xc3: OP("JMP #$%02x%02x", 3);        break;
        case 0xc4: OP("CNZ #$%02x%02x", 3);        break;
        case 0xc5: OP("PUSH B");                   break;
        case 0xc6: OP("ADI #$%02x", 2);            break;
        case 0xc7: OP("RST 0");                    break;
        case 0xc8: OP("RZ");                       break;
        case 0xc9: OP("RET");                      break;
        case 0xca: OP("JZ #$%02x%02x", 3);         break;
        case 0xcb: OP("NOP");                      break;
        case 0xcc: OP("CZ #$%02x%02x", 3);         break;
        case 0xcd: OP("CALL #$%02x%02x", 3);       break;
        case 0xce: OP("ACI #$%02x", 2);            break;
        case 0xcf: OP("RST 1");                    break;
        case 0xd0: OP("RNC");                      break;
        case 0xd1: OP("POP D");                    break;
        case 0xd2: OP("JNC #$%02x%02x", 3);        break;
        case 0xd3: OP("OUT #$%02x", 2);            break;
        case 0xd4: OP("CNC #$%02x%02x", 3);        break;
        case 0xd5: OP("PUSH D");                   break;
        case 0xd6: OP("SUI #$%02x", 2);            break;
        case 0xd7: OP("RST 2");                    break;
        case 0xd8: OP("RC");                       break;
        case 0xd9: OP("NOP");                      break;
        case 0xda: OP("JC #$%02x%02x", 3);         break;
        case 0xdb: OP("IN #$%02x", 2);             break;
        case 0xdc: OP("CC #$%02x%02x", 3);         break;
        case 0xdd: OP("NOP");                      break;
        case 0xde: OP("SBI #$%02x", 2);            break;
        case 0xdf: OP("RST 3");                    break;
        case 0xe0: OP("RPO");                      break;
        case 0xe1: OP("POP H");                    break;
        case 0xe2: OP("JPO #$%02x%02x", 3);        break;
        case 0xe3: OP("XTHL");                     break;
        case 0xe4: OP("CPO #$%02x%02x", 3);        break;
        case 0xe5: OP("PUSH H");                   break;
        case 0xe6: OP("ANI #$%02x", 2);            break;
        case 0xe7: OP("RST 4");                    break;
        case 0xe8: OP("RPE");                      break;
        case 0xe9: OP("PCHL");                     break;
        case 0xea: OP("JPE #$%02x%02x", 3);        break;
        case 0xeb: OP("XCHG");                     break;
        case 0xec: OP("CPE #$%02x%02x", 3);        break;
        case 0xed: OP("NOP");                      break;
        case 0xee: OP("XRI #$%02x", 2);            break;
        case 0xef: OP("RST 5");                    break;
        case 0xf0: OP("RP");                       break;
        case 0xf1: OP("POP PSW");                  break;
        case 0xf2: OP("JP #$%02x%02x", 3);         break;
        case 0xf3: OP("DI");                       break;
        case 0xf4: OP("CP #$%02x%02x", 3);         break;
        case 0xf5: OP("PUSH PSW");                 break;
        case 0xf6: OP("ORI #$%02x", 2);            break;
        case 0xf7: OP("RST 6");                    break;
        case 0xf8: OP("RM");                       break;
        case 0xf9: OP("SPHL");                     break;
        case 0xfa: OP("JM #$%02x%02x", 3);         break;
        case 0xfb: OP("EI");                       break;
        case 0xfc: OP("CM #$%02x%02x", 3);         break;
        case 0xfd: OP("NOP");                      break;
        case 0xfe: OP("CPI #$%02x", 2);            break;
        case 0xff: OP("RST 7");                    break;
    }

    printf("\n");
    return bytes;
}