#ifndef __DISASSEMBLER_H_
#define __DISASSEMBLER_H_

int disassemble(char *filename);
int opcode(unsigned char *buffer, int pc);

#endif