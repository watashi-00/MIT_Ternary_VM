#ifndef VM_H
#define VM_H

#include <stdbool.h>
#include <stdio.h>

#include "../isa/isa.h"

extern bool debug_mode;
extern char *filename;

#define DEBUG_PRINT(...) do { if (debug_mode) printf(__VA_ARGS__); } while (0)

typedef struct Dir {
    char name[32];

    struct Dir *parent;
    struct Dir *children[32];

    int child_count;
} Dir;

typedef struct {
    t_word regs[4];
    t_word pc;
    bool is_running;

    Dir *root;
    Dir *cwd;
} VM;

#endif // VM_H
