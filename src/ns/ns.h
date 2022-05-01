#ifndef NS_H
#define NS_H

#include "../utils/matrix.h"
#include <string>
#include <vector>

class NS
{
    private:
        void check_grid(int size);
        void check_size(int nx, int ny);

    public: 
        void solve_ns(std::string system, int nx, int ny, double re, 
                      double rho, double nu);
        void save_res(Matrix<double>& u, Matrix<double>& v, Matrix<double>& p,
                      int nx, int ny);
};

#endif