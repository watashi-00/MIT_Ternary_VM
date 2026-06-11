#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef int t_word;

bool debug_mode = false;

#define DEBUG_PRINT(...) do { if (debug_mode) printf(__VA_ARGS__); } while (0)

typedef enum{
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

typedef struct {
    t_word regs[4];
    t_word pc;
    bool is_running;
} VM;

int main(int argc, char *argv[]) {
    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-v") == 0) {
            debug_mode = true;
        }
    }

    VM vm = {.pc = 0, .is_running = 1};
    for(int i=0; i<4;i++) vm.regs[i] = 0;

    t_word program[] = {
        LOAD, RAX, 10,
        LOAD, RBX, 5,
        ADD, RAX, RBX,
        PRINT, RAX,
        HALT
    };

    while(vm.is_running) {
        t_word instruction = program[vm.pc];
        vm.pc++;
        DEBUG_PRINT("PC %d\n", vm.pc);
        switch (instruction) {
            case HALT:
                DEBUG_PRINT("exiting vm\n");
                vm.is_running = 0;
                break;
            case LOAD: {
                t_word reg = program[vm.pc++];
                t_word value = program[vm.pc++];
                vm.regs[reg] = value;
                DEBUG_PRINT("LOAD: R[%d] = %d\n", reg, value);
                break;
            }
            case ADD: {
                t_word reg_dest = program[vm.pc++];
                t_word reg_src  = program[vm.pc++];
                vm.regs[reg_dest] = vm.regs[reg_dest] + vm.regs[reg_src];
                DEBUG_PRINT("R[%d] + R[%d] -> [%d] \n", reg_dest, reg_src, reg_dest);
                break;
            }
            case PRINT: {
                t_word reg_print = program[vm.pc++];
                printf("R[%d]:%d\n", reg_print, vm.regs[reg_print]);
                break;
            }
            default: {
                printf("error: unkown instruction %d on %d \n", instruction, vm.pc-1);
                vm.is_running=0;
                break;
            }
        }
    }

    return 0;
}