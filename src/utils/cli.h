#ifndef CLI_H
#define CLI_H

#include <string>

/**
 * @class Cli
 * @brief Class for a minimal cli.
 */

class Cli
{
    private:
        /** Input parameters */
        int argc;
	    char** argv;

    public:
        /** Helper functions */
        void print_info(); 
	    void print_help(char** argv);

        /** Read the parameters from the user and check them */
        void read_params(char** argv);
        std::string check_param(char** p, int el, std::string name_p);

        /** Call of the Lotka-Volterra model */
        void call_lv(int n, double dt, double x_0, double y_0, double a, 
                     double b, double c, double d);

        /** Call of the Navier-Stokes solver */
        void call_ns(std::string system, int nx, int ny, double re, double rho, 
                     double nu);
};

#endif