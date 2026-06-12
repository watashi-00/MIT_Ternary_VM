#include "common/vm.h"
#include "fs/fs.h"
#include "repl/repl.h"
#include <string.h>

bool debug_mode = false;
char *filename = NULL;

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {

        if (strcmp(argv[i], "-v") == 0) {
            debug_mode = true;
        }
        else if (strcmp(argv[i], "-f") == 0) {

            if (i + 1 < argc) {
                filename = argv[++i];
            }
        }
    }

    VM vm = {0};

    vm.is_running = true;

    Dir *root = mkdir_node("/", NULL);

    vm.root = root;
    vm.cwd = root;

    mkdir_node("home", root);
    mkdir_node("bin", root);
    mkdir_node("tmp", root);

    repl(&vm);

    return 0;
}
