#include "fs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Dir *mkdir_node(const char *name, Dir *parent)
{
    Dir *dir = malloc(sizeof(Dir));

    if (!dir) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }

    strncpy(dir->name, name, sizeof(dir->name) - 1);
    dir->name[sizeof(dir->name) - 1] = '\0';

    dir->parent = parent;
    dir->child_count = 0;

    for (int i = 0; i < 32; i++) {
        dir->children[i] = NULL;
    }

    if (parent != NULL) {
        if (parent->child_count >= 32) {
            printf("directory full\n");
            free(dir);
            return NULL;
        }

        parent->children[parent->child_count++] = dir;
    }

    return dir;
}

void ls(VM *vm)
{
    for (int i = 0; i < vm->cwd->child_count; i++) {
        printf("%s\n", vm->cwd->children[i]->name);
    }
}

void cd(VM *vm, const char *target)
{
    if (strcmp(target, "..") == 0) {

        if (vm->cwd->parent != NULL) {
            vm->cwd = vm->cwd->parent;
        }

        return;
    }

    for (int i = 0; i < vm->cwd->child_count; i++) {

        Dir *child = vm->cwd->children[i];

        if (strcmp(child->name, target) == 0) {
            vm->cwd = child;
            return;
        }
    }

    printf("directory not found: %s\n", target);
}

void pwd_recursive(Dir *dir)
{
    if (dir == NULL)
        return;

    if (dir->parent != NULL) {
        pwd_recursive(dir->parent);

        if (strcmp(dir->name, "/") != 0) {
            printf("/%s", dir->name);
        }
    } else {
        printf("/");
    }
}

void pwd(VM *vm)
{
    pwd_recursive(vm->cwd);
    printf("\n");
}

void print_prompt(VM *vm)
{
    printf("vm> ");
    pwd_recursive(vm->cwd);
    printf(" $ ");
}
