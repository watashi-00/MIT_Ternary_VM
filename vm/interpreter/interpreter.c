#include "interpreter.h"
#include "../alu/alu.h"
#include <stdio.h>

void exec(VM vm)
{
    t_word program[] = {
        LOAD, RAX, 10,
        LOAD, RBX, 5,
        LOAD, RCX, 15,
        ADD, RAX, RBX, RCX,
        PRINT, RAX,
        SUB, RAX, RBX, RCX,
        PRINT, RAX,
        HALT
    };

    bool is_running = true;

    while (is_running) {

        t_word instruction = program[vm.pc++];

        DEBUG_PRINT("PC %d\n", vm.pc);

        switch (instruction) {

            case HALT:
                DEBUG_PRINT("exiting vm\n");
                is_running = false;
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
                t_word reg_src1 = program[vm.pc++];
                t_word reg_src2 = program[vm.pc++];

                vm.regs[reg_dest] = alu_add(
                    vm.regs[reg_dest],
                    vm.regs[reg_src1],
                    vm.regs[reg_src2]
                );

                DEBUG_PRINT(
                    "R[%d] + R[%d] + R[%d] -> [%d]\n",
                    reg_dest,
                    reg_src1,
                    reg_src2,
                    reg_dest
                );

                break;
            }

            case SUB: {
                t_word reg_dest = program[vm.pc++];
                t_word reg_src1 = program[vm.pc++];
                t_word reg_src2 = program[vm.pc++];

                vm.regs[reg_dest] = alu_sub(
                    vm.regs[reg_dest],
                    vm.regs[reg_src1],
                    vm.regs[reg_src2]
                );

                DEBUG_PRINT(
                    "R[%d] - R[%d] - R[%d] -> [%d]\n",
                    reg_dest,
                    reg_src1,
                    reg_src2,
                    reg_dest
                );

                break;
            }

            case PRINT: {
                t_word reg_print = program[vm.pc++];

                printf("R[%d]: %d\n",
                       reg_print,
                       vm.regs[reg_print]);

                break;
            }

            default:
                printf(
                    "error: unknown instruction %d on %d\n",
                    instruction,
                    vm.pc - 1
                );

                is_running = false;
                break;
        }
    }
}
