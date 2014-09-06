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
inline int format_optcode(unsigned char *buffer, int pc, char s[], int size);

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

/*
 * This macro/function combination may not be the prettiest, but it makes my
 * life a whole lot easier when defining optcodes #sorrynotsorry
 */
#define OPT_1(a) (bytes = format_optcode(buffer, pc, a, 1))
#define OPT_2(a, b) (bytes = format_optcode(buffer, pc, a, b))
#define GET_OPT(a, b, name, ...) name
#define OPT(...) GET_OPT(__VA_ARGS__, OPT_2, OPT_1)(__VA_ARGS__)
inline int format_optcode(unsigned char *buffer, int pc, char s[], int size) {
    printf(s, (size >= 2) ? (
        (size == 2) ? buffer[pc+1] : buffer[pc+2]
    ) : (unsigned char)"", (size == 3) ? buffer[pc+1] : (unsigned char)"");
    return size;
}

int opcode(unsigned char *buffer, int pc) {
    int bytes = 1;

    switch(buffer[pc]) {
        // How 'bout them optcodes
        case 0x00: OPT("NOP");                      break;
        case 0x01: OPT("LXI B, #$%02x%02x", 3);     break;
        case 0x02: OPT("STAX B");                   break;
        case 0x03: OPT("INX B");                    break;
        case 0x04: OPT("INR B");                    break;
        case 0x05: OPT("DCR B");                    break;
        case 0x06: OPT("MVI B, #$%02x", 2);         break;
        case 0x07: OPT("RLC");                      break;
        case 0x08: OPT("NOP");                      break;
        case 0x09: OPT("DAD B");                    break;
        case 0x0a: OPT("LDAX B");                   break;
        case 0x0b: OPT("DCX B");                    break;
        case 0x0c: OPT("INR C");                    break;
        case 0x0d: OPT("DCR C");                    break;
        case 0x0e: OPT("MVI C, #$%02x%02x", 3);     break;
        case 0x0f: OPT("RRC");                      break;
        case 0x10: OPT("NOP");                      break;
        case 0x11: OPT("LXI D, #$%02x%02x", 3);     break;
        case 0x12: OPT("STAX D");                   break;
        case 0x13: OPT("INX D");                    break;
        case 0x14: OPT("INR D");                    break;
        case 0x15: OPT("DCR D");                    break;
        case 0x16: OPT("MVI D, #$%02x", 2);         break;
        case 0x17: OPT("RAL");                      break;
        case 0x18: OPT("NOP");                      break;
        case 0x19: OPT("DAD D");                    break;
        case 0x1a: OPT("LDAX E");                   break;
        case 0x1b: OPT("DCX D");                    break;
        case 0x1c: OPT("INR E");                    break;
        case 0x1d: OPT("DCR E");                    break;
        case 0x1e: OPT("MVI E, #$%02x%02x", 3);     break;
        case 0x1f: OPT("RAR");                      break;
        case 0x20: OPT("RIM");                      break;
        case 0x21: OPT("LXI H, #$%02x%02x", 3);     break;
        case 0x22: OPT("SHLD #$%02x%02x", 3);       break;
        case 0x23: OPT("INX H");                    break;
        case 0x24: OPT("INR H");                    break;
        case 0x25: OPT("DCR H");                    break;
        case 0x26: OPT("MVI H, #$%02x", 2);         break;
        case 0x27: OPT("DAA");                      break;
        case 0x28: OPT("NOP");                      break;
        case 0x29: OPT("DAD H");                    break;
        case 0x2a: OPT("LHLD #$%02x%02x", 3);       break;
        case 0x2b: OPT("DCX H");                    break;
        case 0x2c: OPT("INR L");                    break;
        case 0x2d: OPT("DCR L");                    break;
        case 0x2e: OPT("LXI SP, #$%02x%02x", 3);    break;
        case 0x2f: OPT("CMA");                      break;
        case 0x30: OPT("SIM");                      break;
        case 0x31: OPT("LXI SP, #$%02x%02x", 3);    break;
        case 0x32: OPT("STA #$%02x%02x", 3);        break;
        case 0x33: OPT("INX SP");                   break;
        case 0x34: OPT("INR M");                    break;
        case 0x35: OPT("DCR M");                    break;
        case 0x36: OPT("MVI M, #$%02x", 2);         break;
        case 0x37: OPT("STC");                      break;
        case 0x38: OPT("NOP");                      break;
        case 0x39: OPT("DAD SP");                   break;
        case 0x3a: OPT("LDA #$%02x%02x", 3);        break;
        case 0x3b: OPT("DCX SP");                   break;
        case 0x3c: OPT("INR A");                    break;
        case 0x3d: OPT("DCR A");                    break;
        case 0x3e: OPT("MVI A, #$%02x", 2);         break;
        case 0x3f: OPT("CMC");                      break;
        case 0x40: OPT("MOV B, B");                 break;
        case 0x41: OPT("MOV B, C");                 break;
        case 0x42: OPT("MOV B, D");                 break;
        case 0x43: OPT("MOV B, E");                 break;
        case 0x44: OPT("MOV B, H");                 break;
        case 0x45: OPT("MOV B, L");                 break;
        case 0x46: OPT("MOV B, M");                 break;
        case 0x47: OPT("MOV B, A");                 break;
        case 0x48: OPT("MOV C, B");                 break;
        case 0x49: OPT("MOV C, C");                 break;
        case 0x4a: OPT("MOV C, D");                 break;
        case 0x4b: OPT("MOV C, E");                 break;
        case 0x4c: OPT("MOV C, H");                 break;
        case 0x4d: OPT("MOV C, L");                 break;
        case 0x4e: OPT("MOV C, M");                 break;
        case 0x4f: OPT("MOV C, A");                 break;
        case 0x50: OPT("MOV D, B");                 break;
        case 0x51: OPT("MOV D, C");                 break;
        case 0x52: OPT("MOV D, D");                 break;
        case 0x53: OPT("MOV D, E");                 break;
        case 0x54: OPT("MOV D, H");                 break;
        case 0x55: OPT("MOV D, L");                 break;
        case 0x56: OPT("MOV D, M");                 break;
        case 0x57: OPT("MOV D, A");                 break;
        case 0x58: OPT("MOV E, B");                 break;
        case 0x59: OPT("MOV E, C");                 break;
        case 0x5a: OPT("MOV E, D");                 break;
        case 0x5b: OPT("MOV E, E");                 break;
        case 0x5c: OPT("MOV E, H");                 break;
        case 0x5d: OPT("MOV E, L");                 break;
        case 0x5e: OPT("MOV E, M");                 break;
        case 0x5f: OPT("MOV E, A");                 break;
        case 0x60: OPT("MOV H, B");                 break;
        case 0x61: OPT("MOV H, C");                 break;
        case 0x62: OPT("MOV H, D");                 break;
        case 0x63: OPT("MOV H, E");                 break;
        case 0x64: OPT("MOV H, H");                 break;
        case 0x65: OPT("MOV H, L");                 break;
        case 0x66: OPT("MOV H, M");                 break;
        case 0x67: OPT("MOV H, A");                 break;
        case 0x68: OPT("MOV L, B");                 break;
        case 0x69: OPT("MOV L, C");                 break;
        case 0x6a: OPT("MOV L, D");                 break;
        case 0x6b: OPT("MOV L, B");                 break;
        case 0x6c: OPT("MOV L, H");                 break;
        case 0x6d: OPT("MOV L, L");                 break;
        case 0x6e: OPT("MOV L, M");                 break;
        case 0x6f: OPT("MOV L, A");                 break;
        case 0x70: OPT("MOV M, B");                 break;
        case 0x71: OPT("MOV M, C");                 break;
        case 0x72: OPT("MOV M, D");                 break;
        case 0x73: OPT("MOV M, E");                 break;
        case 0x74: OPT("MOV M, H");                 break;
        case 0x75: OPT("MOV M, L");                 break;
        case 0x76: OPT("HLT");                      break;
        case 0x77: OPT("MOV M, A");                 break;
        case 0x78: OPT("MOV A, B");                 break;
        case 0x79: OPT("MOV A, C");                 break;
        case 0x7a: OPT("MOV A, D");                 break;
        case 0x7b: OPT("MOV A, E");                 break;
        case 0x7c: OPT("MOV A, H");                 break;
        case 0x7d: OPT("MOV A, L");                 break;
        case 0x7e: OPT("MOV A, M");                 break;
        case 0x7f: OPT("MOV A, A");                 break;
        case 0x80: OPT("ADD B");                    break;
        case 0x81: OPT("ADD C");                    break;
        case 0x82: OPT("ADD D");                    break;
        case 0x83: OPT("ADD E");                    break;
        case 0x84: OPT("ADD H");                    break;
        case 0x85: OPT("ADD L");                    break;
        case 0x86: OPT("ADD M");                    break;
        case 0x87: OPT("ADD A");                    break;
        case 0x88: OPT("ADC B");                    break;
        case 0x89: OPT("ADC C");                    break;
        case 0x8a: OPT("ADC D");                    break;
        case 0x8b: OPT("ADC E");                    break;
        case 0x8c: OPT("ADC H");                    break;
        case 0x8d: OPT("ADC L");                    break;
        case 0x90: OPT("SUB B");                    break;
        case 0x91: OPT("SUB C");                    break;
        case 0x92: OPT("SUB D");                    break;
        case 0x93: OPT("SUB E");                    break;
        case 0x94: OPT("SUB H");                    break;
        case 0x95: OPT("SUB L");                    break;
        case 0x96: OPT("SUB M");                    break;
        case 0x97: OPT("SUB A");                    break;
        case 0x98: OPT("SBB B");                    break;
        case 0x99: OPT("SBB C");                    break;
        case 0x9a: OPT("SBB D");                    break;
        case 0x9b: OPT("SBB E");                    break;
        case 0x9c: OPT("SBB H");                    break;
        case 0x9d: OPT("SBB L");                    break;
        case 0x9e: OPT("SBB M");                    break;
        case 0x9f: OPT("SBB A");                    break;
        case 0xa0: OPT("ANA B");                    break;
        case 0xa1: OPT("ANA C");                    break;
        case 0xa2: OPT("ANA D");                    break;
        case 0xa3: OPT("ANA E");                    break;
        case 0xa4: OPT("ANA H");                    break;
        case 0xa5: OPT("ANA L"); /* topkek */       break;
        case 0xa6: OPT("ANA M");                    break;
        case 0xa7: OPT("ANA A");                    break;
        case 0xa8: OPT("XRA B");                    break;
        case 0xa9: OPT("XRA C");                    break;
        case 0xaa: OPT("XRA D");                    break;
        case 0xab: OPT("XRA E");                    break;
        case 0xac: OPT("XRA H");                    break;
        case 0xad: OPT("XRA L");                    break;
        case 0xae: OPT("XRA M");                    break;
        case 0xaf: OPT("XRA A");                    break;
        case 0xb0: OPT("ORA B");                    break;
        case 0xb1: OPT("ORA C");                    break;
        case 0xb2: OPT("ORA D");                    break;
        case 0xb3: OPT("ORA E");                    break;
        case 0xb4: OPT("ORA H");                    break;
        case 0xb5: OPT("ORA L"); /* topkek */       break;
        case 0xb6: OPT("ORA M");                    break;
        case 0xb7: OPT("ORA A");                    break;
        case 0xb8: OPT("CMP B");                    break;
        case 0xb9: OPT("CMP C");                    break;
        case 0xba: OPT("CMP D");                    break;
        case 0xbb: OPT("CMP E");                    break;
        case 0xbc: OPT("CMP H");                    break;
        case 0xbd: OPT("CMP L");                    break;
        case 0xbe: OPT("CMP M");                    break;
        case 0xbf: OPT("CMP A");                    break;
        case 0xc0: OPT("RNZ");                      break;
        case 0xc1: OPT("POP B");                    break;
        case 0xc2: OPT("JNZ #$%02x%02x", 3);        break;
        case 0xc3: OPT("JMP #$%02x%02x", 3);        break;
        case 0xc4: OPT("CNZ #$%02x%02x", 3);        break;
        case 0xc5: OPT("PUSH B");                   break;
        case 0xc6: OPT("ADI #$%02x", 2);            break;
        case 0xc7: OPT("RST 0");                    break;
        case 0xc8: OPT("RZ");                       break;
        case 0xc9: OPT("RET");                      break;
        case 0xca: OPT("JZ #$%02x%02x", 3);         break;
        case 0xcb: OPT("NOP");                      break;
        case 0xcc: OPT("JZ #$%02x%02x", 3);         break;
        case 0xcd: OPT("CALL #$%02x%02x", 3);       break;
        case 0xce: OPT("ACI #$%02x", 2);            break;
        case 0xcf: OPT("RST 1");                    break;
        case 0xd0: OPT("RNC");                      break;
        case 0xd1: OPT("POP D");                    break;
        case 0xd2: OPT("JNC #$%02x%02x", 3);        break;
        case 0xd3: OPT("OUT #$%02x", 2);            break;
        case 0xd4: OPT("CNC #$%02x%02x", 3);        break;
        case 0xd5: OPT("PUSH D");                   break;
        case 0xd6: OPT("SUI #$%02x", 2);            break;
        case 0xd7: OPT("RST 2");                    break;
        case 0xd8: OPT("RC");                       break;
        case 0xd9: OPT("NOP");                      break;
        case 0xda: OPT("JC #$%02x%02x", 3);         break;
        case 0xdb: OPT("IN #$%02x", 2);             break;
        case 0xdc: OPT("CC #$%02x%02x", 3);         break;
        case 0xdd: OPT("NOP");                      break;
        case 0xde: OPT("SBI #$%02x", 2);            break;
        case 0xdf: OPT("RST 3");                    break;
        case 0xe0: OPT("RPO");                      break;
        case 0xe1: OPT("POP H");                    break;
        case 0xe2: OPT("JPO #$%02x%02x", 3);        break;
        case 0xe3: OPT("XTHL");                     break;
        case 0xe4: OPT("CPO #$%02x%02x", 3);        break;
        case 0xe5: OPT("PUSH H");                   break;
        case 0xe6: OPT("ANI #$%02x", 2);            break;
        case 0xe7: OPT("RST 4");                    break;
        case 0xe8: OPT("RPE");                      break;
        case 0xe9: OPT("PCHL");                     break;
        case 0xea: OPT("JPE #$%02x%02x", 3);        break;
        case 0xeb: OPT("XCHG");                     break;
        case 0xec: OPT("CPE #$%02x%02x", 3);        break;
        case 0xed: OPT("NOP");                      break;
        case 0xee: OPT("XRI #$%02x", 2);            break;
        case 0xef: OPT("RST 5");                    break;
        case 0xf0: OPT("RP");                       break;
        case 0xf1: OPT("POP PSW");                  break;
        case 0xf2: OPT("JP #$%02x%02x", 3);         break;
        case 0xf3: OPT("DI");                       break;
        case 0xf4: OPT("CP #$%02x%02x", 3);         break;
        case 0xf5: OPT("PUSH PSW");                 break;
        case 0xf6: OPT("ORI #$%02x", 2);            break;
        case 0xf7: OPT("RST 6");                    break;
        case 0xf8: OPT("RM");                       break;
        case 0xf9: OPT("SPHL");                     break;
        case 0xfa: OPT("JM #$%02x%02x", 3);         break;
        case 0xfb: OPT("EI");                       break;
        case 0xfc: OPT("CM #$%02x%02x", 3);         break;
        case 0xfd: OPT("NOP");                      break;
        case 0xfe: OPT("CPI #$%02x", 2);            break;
        case 0xff: OPT("RST 7");                    break;
    }

    printf("\n");
    return bytes;
}