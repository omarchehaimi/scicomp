#include <iostream>
#include <string>
#include <stdexcept>
#include "cli.h"

void Cli::print_info()
{
    std::cout << "######################### \n";
    std::cout << "#  Welcome to SciComp!  # \n";
    std::cout << "#     Version v0.1      # \n";
    std::cout << "######################### \n";
}

void Cli::print_help(char** argv)
{
    /**
     * Prints the help message if --help flag is passed as first parameter of 
     * the cli.
    */

    std::string help;
    if (argv[1] != NULL) {
        help = argv[1];
    } else {
        help = "";
    }

    if (help == "--help") {
        std::cout << "######################### \n";
        std::cout << "#  Welcome to SciComp!  # \n";
        std::cout << "#     Version v0.1      # \n";
        std::cout << "######################### \n";
        std::cout << "\n* Use lt to calculate the solution of the ";
        std::cout << "Lotka-Volterra model and specify all the required parameters. \n";
        std::cout << "\n* Use fem to calculate a the solutions of a simple problem ";
        std::cout << "by using the finite element method. \n";
        exit(0);
    } else if (help.empty()) {
        std::cout << "No parameters have been passed! Run ./scicomp --help to print the help. \n";
        exit(1);
    }
}

std::string Cli::check_param(char** p, int el, std::string name_p) {
    /**
     * Checks if the param p has been initialized and return it as a string.
     * Parameters:
     *     - p: array of char to be checked
     *     - el: element of the array
     *     - name_p: name of the parameter
     */  
    
    if (p[el] == NULL) {
        std::cout << name_p << " has not been passed! \n";
        exit(1);
    }

    std::string pr = p[el];
    pr = pr.substr(pr.find("=") + 1);
    return pr;
}

void Cli::read_params(char** argv)
{
    /**
    * Reads the parameteter from the cli.
    */

   std::string model = argv[1];

   if (model == "lv") {
       std::string ns = Cli::check_param(argv, 2, "n");
       std::string x_0s = Cli::check_param(argv, 3, "x_0");
       std::string y_0s = Cli::check_param(argv, 4, "y_0");
       std::string as = Cli::check_param(argv, 5, "a");
       std::string bs = Cli::check_param(argv, 6, "b");
       std::string cs = Cli::check_param(argv, 7, "c");
       std::string ds = Cli::check_param(argv, 8, "d");
       int n = std::stoi(ns);
       float x_0 = std::stof(x_0s);
       float y_0 = std::stof(y_0s);
       float a = std::stof(as);
       float b = std::stof(bs);
       float c = std::stof(cs);
       float d = std::stof(ds);
       Cli::call_lv(n, x_0, y_0, a, b, c, d);

   } else if (model=="fem") {
       Cli::call_fem();

   } else {
       std::cout << model << " is not an available option. Choose beteween lv or fem \n";
   }
}

void Cli::call_lv(int n, float x_0, float y_0, float a, float b, float c, float d)
{
    /**
    * Calls the Lotka-Volterra solver.
    * The parameters are:
    *     - t: number of steps to solve the system
    *     - x_0: initial value of pray
    *     - y_0: initial value of predator
    *     - a: grow parameter of the pray
    *     - b: death parameter of the pray
    *     - c: grow parameter of the predator
    *     - d: death parameter of the predator
    */ 
    std::cout << "\n****************************************************************\n";
    std::cout << "Solving the Lotka-Volterra model with the following "; 
    std::cout << "parameters: \n";
    std::cout << "    * n=" << n << "\n";
    std::cout << "    * x_0=" << x_0 << "\n";
    std::cout << "    * y_0=" << y_0 << "\n";
    std::cout << "    * a=" << a << "\n";
    std::cout << "    * b=" << b << "\n";
    std::cout << "    * c=" << c << "\n";
    std::cout << "    * d=" << d << "\n";
}

void Cli::call_fem()
{
    std::cout << "\n********************************************************\n";
    std::cout << "Message inside fem just to print something for testing. \n";
}