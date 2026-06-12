#ifndef FS_H
#define FS_H

#include "../common/vm.h"

Dir *mkdir_node(const char *name, Dir *parent);
void ls(VM *vm);
void cd(VM *vm, const char *target);
void pwd_recursive(Dir *dir);
void pwd(VM *vm);
void print_prompt(VM *vm);

#endif // FS_H
