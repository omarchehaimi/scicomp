#include "utils/cli.h"
#include <iostream>

int main(int argc, char** argv) {

    Cli cli;
    cli.print_help(argv);
    cli.print_info();
    cli.read_params(argv);

    return 0;
}
