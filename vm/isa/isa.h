#ifndef ISA_H
#define ISA_H

typedef int t_word;

typedef enum {
    HALT = 0,
    LOAD,
    ADD,
    SUB,
    PRINT
} Opcode;

typedef enum {
    RAX = 0,
    RBX = 1,
    RCX = 2,
    RDX = 3
} Reg;

#endif // ISA_H
