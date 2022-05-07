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

void NS::save_res(Matrix<double>& u, Matrix<double>& v, Matrix<double>& p, 
                  int nx, int ny) {
    // OUTPUT DATA
	FILE *u_out, *v_out, *p_out;

    std::string cur_dir;
    std::string u_path, v_path, p_path;
    cur_dir = std::filesystem::current_path();
    cur_dir = cur_dir + "/../ns_res";

    u_path = cur_dir + "/u_out.txt";
    v_path = cur_dir + "/v_out.txt";
    p_path = cur_dir + "/p_out.txt";

    Plotting check;
    check.check_folder(cur_dir);

	u_out = std::fopen(u_path.c_str(), "w+t");
    v_out = std::fopen(v_path.c_str(), "w+t");
    p_out = std::fopen(p_path.c_str(), "w+t");

	if (u_out == nullptr || v_out == nullptr || p_out == nullptr) {
        std::cout << "One of the output file has failed to be opened!\n";
        std::fclose(u_out);
        std::fclose(v_out);
        std::fclose(p_out);
	} else {
        for (int i=0 ; i<nx; i++) {
            for (int j=0; j<ny; j++) {
                fprintf(u_out, "%5.8lf\t", u(i, j));
                fprintf(v_out, "%5.8lf\t", v(i, j));
                fprintf(p_out, "%5.8lf\t", p(i, j));
            }
            fprintf(u_out, "\n");
            fprintf(v_out, "\n");
            fprintf(p_out, "\n");
        }
	}
}

void NS::solve_ns(std::string system, int nx, int ny, double dt, double re, 
                  double rho, double nu) {
    
    NS::check_grid(nx);
    NS::check_grid(ny);
    NS::check_size(nx, ny);

    double dx, dy, delta;
    double error = 1;
    int step = 1;
    dx = 1.0/(nx-1);
    dy = 1.0/(ny-1);
    delta = 4.5;

    // Initialization
    // u
    Matrix<double> u(nx, ny+1, 0);
    Matrix<double> un(nx, ny+1, 0);
    Matrix<double> uc(nx, ny, 0);
    // v
    Matrix<double> v(nx+1, ny, 0);
    Matrix<double> vn(nx+1, ny, 0);
    Matrix<double> vc(nx, ny, 0);
    // p
    Matrix<double> p(nx+1, ny+1, 1);
    Matrix<double> pn(nx+1, ny+1, 0);
    Matrix<double> pc(nx, ny, 0);
    // m
    Matrix<double> m(nx+1, ny+1, 0);

    for (int i=0; i<nx; i++) {
        u.set_val(i, ny, 1);
        u.set_val(i, ny-1, 1);
    }

    while (error > 0.00000001) {

        // Solve u equation
        for (int i=1; i<nx-1; i++) {
            for (int j=1; j<nx; j++) {
                un.set_val(i, j, 
                    u(i, j) - dt*(
                        (u(i+1, j)*u(i+1, j)-u(i-1, j)*u(i-1, j))/2.0/dx 
					+ 0.25*(
                        (u(i, j)+u(i, j+1))*(v(i, j)+v(i+1, j))
                        -(u(i, j)+u(i, j-1))*(v(i+1, j-1)+v(i, j-1)))/dy)
					- dt/dx*(p(i+1, j)-p(i, j)) 
					+ dt*1.0/re*(
                        (u(i+1, j)-2.0*u(i, j)+u(i-1, j))/dx/dx 
                        + (u(i, j+1)-2.0*u(i, j)+u(i, j-1))/dy/dy)
                    );
            }
        }

        // Boundary conditions
        for (int j=1; j<ny; j++) {
            un.set_val(0, j, 0);
            un.set_val(nx-1, j, 0);
        }
        for (int i=0; i<nx; i++) {
            un.set_val(i, 0, -un(i, 1));
            un.set_val(i, ny, 2-un(i, ny-1));
        }
        
        // Solve v equation
        for (int i=1; i<nx; i++) {
            for (int j=1; j<ny-1; j++) {
                vn.set_val(i, j, 
                    v(i, j) - dt* (0.25*(
                        (u(i, j)+u(i, j+1))*(v(i, j)+v(i+1, j))
                        -(u(i-1, j)+u(i-1, j+1))*(v(i, j)+v(i-1, j)))/dx 
					+ (v(i, j+1)*v(i, j+1)-v(i, j-1)*v(i, j-1))/2.0/dy) 
					- dt/dy*(p(i, j+1)-p(i, j)) 
					+ dt*1.0/re*(
                        (v(i+1, j)-2.0*v(i, j)+v(i-1, j))/dx/dx
                        +(v(i, j+1)-2.0*v(i, j)+v(i, j-1))/dy/dy)
                    );
            }
        }

        // Boundary conditions
        for (int j=1; j<ny-1; j++) {
            vn.set_val(0, j, -vn(1, j));
            vn.set_val(nx, j, -vn(nx-1, j));
        }

        for (int i=0; i<nx; i++) {
            vn.set_val(i, 0, 0);
            vn.set_val(i, ny-1, 0);
        }

        // Solve continuity equation
        for (int i=1; i<nx; i++) {
            for (int j=1; j<ny; j++) {
                pn.set_val(i, j, 
                    p(i, j) - dt*delta*(
                        (un(i, j)-un(i-1, j))/dx 
                        + ( vn(i, j)-vn(i, j-1))/dy)
                    );
            }
        }

        // Boundary contitions
        for (int i=1; i<nx; i++) {
            pn.set_val(i, 0, pn(i, 1));
            pn.set_val(i, ny, pn(i, ny-1));
        }

        for (int j=0; j<ny+1; j++) {
            pn.set_val(0, j, pn(1, j));
            pn.set_val(nx, j, pn(nx-1, j));
        }

        // Error calculation
        error = 0.0;
        
        for (int i=1; i<nx; i++) {
            for (int j=1; j<ny; j++) {
                m.set_val(i, j, 
                    (un(i, j)-un(i-1, j))/dx 
                    + (vn(i, j)-vn(i, j-1))/dy
                    );
                error = error + std::fabs(m(i, j));
            }

        }

        if (step%1000 == 0)
            std::cout << "The error for the step " << step << " is: " 
                      << error << "\n";

        // Updating the matrices
        u = un;
        v = vn;
        p = pn;

        step = step + 1; 
    }

    // Interpolation
    for (int i=0; i<nx; i++) {
		for (int j=0; j<ny; j++) {
            uc.set_val(i, j, 0.5*(u(i, j)+u(i, j+1)));
            vc.set_val(i, j, 0.5*(v(i, j)+v(i+1, j)));
            pc.set_val(i, j, 0.25*(p(i, j)+p(i+1, j)+p(i, j+1)+p(i+1, j+1)));
		}
	}

    std::cout << "Calculation completed\nSaving the results \n";
    NS::save_res(uc, vc, pc, nx, ny);

}