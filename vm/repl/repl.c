#include "repl.h"
#include "../fs/fs.h"
#include "../interpreter/interpreter.h"
#include <stdio.h>
#include <string.h>

void repl(VM *vm)
{
    char line[256];

    while (true) {

        print_prompt(vm);

        if (!fgets(line, sizeof(line), stdin)) {
            break;
        }

        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0)
            continue;

        if (strcmp(line, "exit") == 0)
            break;

        if (strcmp(line, "ls") == 0) {
            ls(vm);
            continue;
        }

        if (strcmp(line, "pwd") == 0) {
            pwd(vm);
            continue;
        }

        if (strcmp(line, "run") == 0) {
            exec(*vm);
            continue;
        }

        if (strncmp(line, "cd ", 3) == 0) {
            cd(vm, line + 3);
            continue;
        }

        if (strncmp(line, "mkdir ", 6) == 0) {
            mkdir_node(line + 6, vm->cwd);
            continue;
        }

        printf("unknown command: %s\n", line);
    }
}
