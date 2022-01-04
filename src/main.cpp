#include "utils/cli.h"
#include "../include/matplotlibcpp.h"
#include <iostream>

namespace plt = matplotlibcpp;

int main(int argc, char** argv) {

    Cli cli;
    cli.print_help(argv);
    cli.print_info();
    cli.read_params(argv);

    return 0;
}
