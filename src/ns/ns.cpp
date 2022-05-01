#include "ns.h"
#include "../utils/plotting.h"
#include "../utils/matrix.h"
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#include <cmath>

void NS::check_grid(int size) {
    if (size > 101){
        std::cout << "One dimension of the grid is bigger than 100. ";
        std::cout << "Select a value equal or less than 100 for both nx and ny.\n";
        throw std::invalid_argument("");
    }
}

void NS::check_size(int nx, int ny) {
    if (nx != ny)
        throw std::invalid_argument("nx and ny have different value! Plsease set the same value.");
}

void NS::solve_ns(std::string system, int nx, int ny, double re, double rho, 
                  double nu) {
    
    NS::check_grid(nx);
    NS::check_grid(ny);
    NS::check_size(nx, ny);

    double dom_length = 1;
    double h_x, h_y, h;
    h_x = dom_length/(nx-1);
    h_y = dom_length/(ny-1);
    h = h_x;
    
    // Internal variables of the loops
    double u_E, u_W, u_N, u_S; 
    double v_E, v_W, v_N, v_S;
    double a_E, a_W, a_N, a_S, a_P;
    double a_e, a_n, A_e, A_n; 

    // Under relaxation factors
    double alpha = 0.8;
    double alpha_p = 0.8;

    Matrix<double> u_final(nx, ny, 0);
    Matrix<double> v_final(nx, ny, 0);
    Matrix<double> p_final(nx, ny, 1);
    // Set the initial condition for u
    for (int j=0; j<ny; j++) {
        u_final.set_val(0, j, 1);
    }

    // Initialization of the staggered matrices
    Matrix<double> u(nx+1, ny, 0);
    Matrix<double> u_star(nx+1, ny, 0);
    Matrix<double> d_e(nx+1, ny, 0);
    Matrix<double> v(nx, ny+1, 0);
    Matrix<double> v_star(nx, ny+1, 0);
    Matrix<double> d_n(nx, ny+1, 0);
    Matrix<double> p(nx+1, ny+1, 0);
    p.set_val(nx, ny, 1);
    Matrix<double> p_c(nx+1, ny+1, 0);
    Matrix<double> b(nx+1, ny+1, 0);

    Matrix<double> u_new(nx+1, ny, 0);
    Matrix<double> v_new(nx, ny+1, 0);
    Matrix<double> p_new(nx+1, ny+1, 0);
    p_new.set_val(nx, ny, 1);
    for (int j=0; j<ny; j++) {
        u.set_val(0, j, 2);
        u_new.set_val(0, j, 2);
    }

    double error = 1;
    unsigned iteration = 0;
    double threshold = 0.0000001;

    while (error > threshold) {

        // u momentum equation
        for (int i=1; i<nx; i++) {
            for (int j=1; j<ny-1; j++) {
                u_E = 0.5*(u(i, j) + u(i, j+1));
                u_W = 0.5*(u(i, j) + u(i, j-1));
                v_N = 0.5*(v(i-1, j) + v(i-1, j+1));
                v_S = 0.5*(v(i, j) + v(i, j+1));
            
                a_E = -0.5*u_E*h + nu;
                a_W = 0.5*u_W*h + nu;
                a_N = -0.5*v_N*h + nu;
                a_S = 0.5*v_S*h + nu;
            
                a_e = 0.5*u_E*h - 0.5*u_W*h + 0.5*v_N*h - 0.5*v_S*h + 4*nu;

                A_e = -h_x;
                d_e.set_val(i, j, A_e/a_e);

                u_star.set_val(i, j, (
                    a_E*u(i, j+1) + a_W*u(i, j-1) + a_N*u(i-1, j) 
                    + a_S*u(i+1, j))/a_e + d_e(i, j)*(p(i, j+1) - p(i, j))
                    );

            }
        }

        // Boundary conditions for u
        for (int j=0; j<ny; j++) {
            u_star.set_val(0, j, 2-u_star(1, j));
            u_star.set_val(nx, j, -u_star(nx, j));
        }
        for (int i=1; i<nx+1; i++) {
            u_star.set_val(i, 0, 0);
            u_star.set_val(i, ny-1, 0);
        }

        // v momentum equation
        for (int i=1; i<nx-1; i++) {
            for (int j=1; j<ny; j++) {
                u_E = 0.5*(u(i, j) + u(i+1, j));
                u_W = 0.5*(u(i, j-1) + u(i+1, j-1));
                v_N = 0.5*(v(i-1, j) + v(i, j));
                v_S = 0.5*(v(i, j) + v(i+1, j));
                
                a_E = -0.5*u_E*h_y + nu;
                a_W = 0.5*u_W*h_y + nu;
                a_N = -0.5*v_N*h_y + nu;
                a_S = 0.5*v_S*h_y + nu;
                
                a_n = 0.5*u_E*h_y - 0.5*u_W*h_y + 0.5*v_N*h_y - 0.5*v_S*h_y + 4*nu;
                
                A_n = -h_y;
                d_n.set_val(i, j, A_n/a_n);
                
                v_star.set_val(i, j, (
                    a_E*v(i, j+1) + a_W*v(i, j-1) + a_N*v(i-1, j) 
                    + a_S*v(i+1, j))/a_n + d_n(i, j)*(p(i, j) - p(i+1, j))
                    );
            }
        }

        // Boundary conditions for v
        for (int i=0; i<nx; i++) {
            v_star.set_val(i, 0, -v_star(i, 1));
            v_star.set_val(i, ny, -v_star(i, ny-1));
        }
        for (int j=1; j<ny+1; j++) {
            v_star.set_val(0, ny-1, 0);
            v_star.set_val(nx-1, j, 0);
        }

        // Zeroing the corrections
        for (int i=0; i<nx+1; i++) {
            for (int j=0; j<ny+1; j++) {
                p_c.set_val(i, j, 0);
            }
        }

        // Continuity equation
        for (int i=1; i<nx; i++) {
            for (int j=1; j<ny; j++) {
                a_E = -d_e(i, j)*h_x;
                a_W = -d_e(i, j-1)*h_x;
                a_N = -d_n(i-1, j)*h_x;
                a_S = -d_n(i, j)*h_x;
                a_P = a_E + a_W + a_N + a_S;
                b.set_val(i, j,
                    -(u_star(i, j) - u_star(i, j-1))*h_x 
                    + (v_star(i, j) - v_star(i-1, j))*h_x
                    );
                p_c.set_val(i, j,
                    (a_E*p_c(i, j+1) + a_W*p_c(i, j-1) + a_N*p_c(i-1, j) 
                    + a_S*p_c(i+1, j) + b(i, j))/a_P
                    );
            }
        }

        // Correction to the pressure field
        for (int i=1; i<nx; i++) {
            for (int j=1; j<ny; j++) {
                p_new.set_val(i, j, p(i, j) + alpha_p*p_c(i, j));
            }
        }

        // Boundary conditions for the pressure
        for (int j=0; j<ny+1; j++) {
            p_new.set_val(0, j, p_new(1, j));
            p_new.set_val(nx, j, p_new(nx-1, j));
        }
        for (int i=0; i<nx+1; i++) {
            p_new.set_val(i, 0, p_new(i, 1));
            p_new.set_val(i, ny, p_new(i, ny-1));
        }

        // Correcting the velocities: u
        for (int i=1; i<nx; i++) {
            for (int j=1; j<ny-1; j++) {
                u_new.set_val(i, j, 
                    u_star(i, j) + alpha*d_e(i, j)*(p_c(i, j+1) - p_c(i, j)));
            }
        }
        // Boundary conditions for u
        for (int j=0; j<ny; j++) {
            u_new.set_val(0, j, 2-u_new(1, j));
            u_new.set_val(nx, j, -u_new(nx-1, j));
        }
        for (int i=1; i<nx+1; i++) {
            u_new.set_val(i, 0, 0);
            u_new.set_val(i, ny-1, 0);
        }

        // Correcting the velocities: v
        for (int i=1; i<nx-1; i++) {
            for (int j=1; j<ny; j++) {
                v_new.set_val(i, j, 
                    v_star(i, j) + alpha*d_n(i, j)*(p_c(i, j) - p_c(i+1, j))
                    );
            }
        }
        // Boundary conditions for v
        for (int i=0; i<nx; i++) {
            v_new.set_val(i, 0, -v_new(i, 1));
            v_new.set_val(i, ny, -v_new(i, ny-1));
        }
        for (int j=1; j<ny+1; j++) {
            v_new.set_val(0, j, 0);
            v_new.set_val(nx-1, j, 0);
        }

        // Residual error
        error = 0;
        for (int i=1; i<nx+1; i++) {
            for (int j=1; j<ny+1; j++) {
                error = error + std::abs(b(i, j));
            }
        }

        // Updating the matrices
        u = u_new;
        v = v_new;
        p = p_new;

        iteration = iteration + 1;

        if (iteration%1000 == 0)
            std::cout << "Error at iteration " << iteration << ": " << error << "\n";
    }

    // Interpolating the collocated variables
    for (int i=0; i<nx; i++) {
        for (int j=0; j<ny; j++) {
            u_final.set_val(i, j, 0.5*(u(i, j) + u(i+1, j)));
            v_final.set_val(i, j, 0.5*(v(i, j) + v(i, j+1)));
            p_final.set_val(i, j, 
                0.25*(p(i, j) + p(i, j+1) + p(i+1, j) + p(i+1, j+1))
                );
        }
    }

    Plotting plot;
    plot.plot_ns(nx, ny, p_final);
}