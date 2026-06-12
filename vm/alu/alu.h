#ifndef ALU_H
#define ALU_H

#include "../isa/isa.h"

t_word alu_add(t_word dest, t_word src1, t_word src2);
t_word alu_sub(t_word dest, t_word src1, t_word src2);

#endif // ALU_H
