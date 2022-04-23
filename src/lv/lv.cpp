#include "lv.h"
#include "../utils/plotting.h"
#include <iostream>
#include <string>
#include <vector>

double LV::prey(double x, double y, double a, double b)
{
    return a*x - b*x*y;
}

double LV::predator(double x, double y, double c, double d)
{
    return d*x*y - c*y;
}

void LV::solve_lv(int n, double dt, double x_0, double y_0, double a, double b, 
                  double c, double d, std::string path /* The default is "" */)
{

    std::vector<double> t (n, 0);
    std::vector<double> x (n, 0);
    std::vector<double> y (n, 0);

    // Set initial conditions and solve the equation with the classic 
    // Runge-Kutta method (RK4)
    double kx1, kx2, kx3, kx4;
    double ky1, ky2, ky3, ky4;

    x[0] = x_0;
    y[0] = y_0;
    for(int i = 1; i < t.size(); i++) {

        kx1 = LV::prey(x[i-1], y[i-1], a, b);
        ky1 = LV::predator(x[i-1], y[i-1], c, d);
        kx2 = LV::prey(x[i-1]+dt*kx1/2, y[i-1]+dt*ky1/2, a, b);
        ky2 = LV::predator(x[i-1]+dt*kx1/2, y[i-1]+dt*ky1/2, a, b);
        kx3 = LV::prey(x[i-1]+dt*kx2/2, y[i-1]+dt*ky2/2, a, b);
        ky3 = LV::predator(x[i-1]+dt*kx2/2, y[i-1]+dt*ky2/2, a, b);
        kx4 = LV::prey(x[i-1]+dt*kx3, y[i-1]+dt*ky3, a, b);
        ky4 = LV::predator(x[i-1]+dt*kx3, y[i-1]+dt*ky3, a, b);

        x[i] = x[i-1] + (dt*(kx1 + 2*kx2 + 2*kx3 + kx4))/6;
        y[i] = y[i-1] + (dt*(ky1 + 2*ky2 + 2*ky3 + ky4))/6;

        t[i] = t[i-1] + dt;

    }
    
    Plotting plot;
    std::string fn = std::to_string(x_0) + "_" + std::to_string(y_0);
    fn = fn + "_" + std::to_string(a);
    fn = fn + "_" + std::to_string(b) + "_" + std::to_string(c);
    fn = fn + "_" + std::to_string(d);
    fn = fn + "_" +std::to_string(dt);
    plot.plot_lv(t, x, y, "Time", "Population", "Lotka-Volterra Model", fn);
}