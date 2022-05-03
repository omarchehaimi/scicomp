#include "cli.h"
#include "../lv/lv.h"
#include "../ns/ns.h"
#include <iostream>
#include <string>
#include <stdexcept>

void Cli::print_info() {
    std::cout << "######################### \n";
    std::cout << "#  Welcome to SciComp!  # \n";
    std::cout << "# Author: Omar Chehaimi # \n";
    std::cout << "#     Version v0.1      # \n";
    std::cout << "######################### \n";
    std::cout << "\n";
}

void Cli::print_help(char** argv) {
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
        std::cout << "# Author: Omar Chehaimi # \n";
        std::cout << "#     Version v0.1      # \n";
        std::cout << "######################### \n";
        std::cout << "\n* Use lt to calculate the solution of the ";
        std::cout << "Lotka-Volterra model and specify all the required parameters. \n";
        std::cout << "\n* Use nv to solve the Navier-Stokes equations for the ";
        std::cout << "cavity flow problem in two dimensions. \n";
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

void Cli::read_params(char** argv) {
    /**
    * Read the parameteter from the cli.
    */

   std::string model = argv[1];

   if (model == "lv") {
       std::string ns = Cli::check_param(argv, 2, "n");
       std::string dts = Cli::check_param(argv, 3, "dt");
       std::string x_0s = Cli::check_param(argv, 4, "x_0");
       std::string y_0s = Cli::check_param(argv, 5, "y_0");
       std::string as = Cli::check_param(argv, 6, "a");
       std::string bs = Cli::check_param(argv, 7, "b");
       std::string cs = Cli::check_param(argv, 8, "c");
       std::string ds = Cli::check_param(argv, 9, "d");
       int n = std::stoi(ns);
       double dt = std::stod(dts);
       double x_0 = std::stod(x_0s);
       double y_0 = std::stod(y_0s);
       double a = std::stod(as);
       double b = std::stod(bs);
       double c = std::stod(cs);
       double d = std::stod(ds);
       Cli::call_lv(n, dt, x_0, y_0, a, b, c, d);

   } else if (model == "ns") {
       std::string system = Cli::check_param(argv, 2, "cavity2d");
       std::string nxs = Cli::check_param(argv, 3, "nx");
       std::string nys = Cli::check_param(argv, 4, "ny");
       std::string dts = Cli::check_param(argv, 5, "dt");
       std::string res = Cli::check_param(argv, 6, "re");
       std::string rhos = Cli::check_param(argv, 7, "rho");
       std::string nus = Cli::check_param(argv, 8, "nu");
       int nx = std::stoi(nxs);
       int ny = std::stoi(nys);
       double dt = std::stod(dts);
       double re = std::stod(res);
       double rho = std::stod(rhos);
       double nu = std::stod(nus);
       Cli::call_ns(system, nx, ny, dt, re, rho, nu);

   } else {
       std::cout << model << " is not an available option. Choose beteween lv or ns \n";
   }
}

void Cli::call_lv(int n, double dt, double x_0, double y_0, double a, double b, 
                  double c, double d) {
    /**
    * Call the Lotka-Volterra solver.
    * The parameters are:
    *     - n: number of steps to solve the system
    *     - dt: time step
    *     - x_0: initial value of pray
    *     - y_0: initial value of predator
    *     - a: grow parameter of the pray
    *     - b: death parameter of the pray
    *     - c: grow parameter of the predator
    *     - d: death parameter of the predator
    */ 
    std::cout << "\n*******************************************************************\n";
    std::cout << "Solving the Lotka-Volterra equations with the following "; 
    std::cout << "parameters: \n";
    std::cout << "    * n   = " << n << "\n";
    std::cout << "    * dt  = " << dt << "\n";
    std::cout << "    * x_0 = " << x_0 << "\n";
    std::cout << "    * y_0 = " << y_0 << "\n";
    std::cout << "    * a   = " << a << "\n";
    std::cout << "    * b   = " << b << "\n";
    std::cout << "    * c   = " << c << "\n";
    std::cout << "    * d   = " << d << "\n";
    std::cout << "The total time for the calculation is n*dt= " << n*dt-dt << "\n";
    
    // Calling the solver
    LV lv_solver;
    lv_solver.solve_lv(n, dt, x_0, y_0, a, b, c, d);

}

void Cli::call_ns(std::string system, int nx, int ny, double dt, double re, 
                  double rho, double nu) {
    /**
     * Call the Navier-Stokes equations solver for the two dimensional case for
     * the cavity flow system.
     * The parameters are:
     *     - system: name of the system. So far only the cavity flow is available
     *     - nx: size of the box along the x direction
     *     - ny: size of the box along the y direction
     *     - dt: time step
     *     - re: Reynolds number
     *     - rho: density
     *     - nu: kinematic viscosity
     */
    std::cout << "\n****************************************************************";
    std::cout << "************************************************\n";
    std::cout << "Solving the Navier-Stokes equations for the cavity flow problem"; 
    std::cout << " in two dimensions with the following parameters: " << "\n";
    std::cout << "    * nx  = " << nx << "\n";
    std::cout << "    * ny  = " << ny << "\n";
    std::cout << "    * dt  = " << dt << "\n";
    std::cout << "    * re  = " << re << "\n";
    std::cout << "    * rho  = " << rho << "\n";
    std::cout << "    * nu  = " << nu << "\n";

    // Calling the solver
    NS nv_solver;
    nv_solver.solve_ns(system, nx, ny, dt, re, rho, nu);
}