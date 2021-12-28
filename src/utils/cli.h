#ifndef CLI_H
#define CLI_H

#include <string>

class Cli
{
    private:
        int argc;
	    char** argv;
    public:
        void print_info(); 
	    void print_help(char** argv);
        void read_params(char** argv);
        std::string check_param(char** p, int el, std::string name_p);
        void call_lv(int n, float x_0, float y_0, float a, float b, float c, float d);
        void call_fem();
};

#endif