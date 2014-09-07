#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "disassembler.h"
#include "assembler.h"
#include "emu.h"

extern int opterr;
extern char* optarg;

int main(int argc, char *argv[]) {
    char usage[] = "Usage: %s -ade <filename> | -h\n";
    if(argc < 2) {
        printf(usage, argv[0]);
        exit(1);
    }

    opterr = 0;
    int c;
    while((c = getopt(argc, argv, "a:d:e:h")) != -1) {
        switch(c) {
            case 'a':
                break;
            case 'd':
                disassemble(optarg);
                break;
            case 'e':
                emulate(optarg);
                break;
            case 'h':
                printf(usage, argv[0]);
                printf(" -a   assemble 8080 assembly\n");
                printf(" -d   disassmble 8080 assembly\n");
                printf(" -e   emulate an 8080 processer with a given binary file\n");
                printf(" -h   print this message\n");
                break;
            default:
                break;
        }
    }
    exit(0);
}