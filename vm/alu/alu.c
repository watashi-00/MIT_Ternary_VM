#include "alu.h"

t_word alu_add(t_word dest, t_word src1, t_word src2)
{
    return dest + src1 + src2;
}

t_word alu_sub(t_word dest, t_word src1, t_word src2)
{
    return dest - src1 - src2;
}
