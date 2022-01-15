#include "lv.h"
#include "../utils/plotting.h"
#include <iostream>
#include <string>
#include <vector>

void LV::solve_lv(int n, double dt, double x_0, double y_0, double a, double b, 
                  double c, double d, std::string path /* The default is "" */)
{

    std::vector<double> t (n, 0);
    std::vector<double> x (n, 0);
    std::vector<double> y (n, 0);

    // Set initial conditions
    x[0] = x_0;
    y[0] = y_0;
    for(int i = 1; i < t.size(); i++) {
        t[i] = t[i-1] + dt;
        x[i] = x[i-1] + (a*x[i-1] - b*x[i-1]*y[i-1])*dt;
        y[i] = y[i-1] + (c*x[i-1]*y[i-1] - d*y[i-1])*dt;
    }
    
    Plotting plot;
    std::string fn = std::to_string(x_0) + "_" + std::to_string(y_0);
    fn = fn + "_" + std::to_string(a);
    fn = fn + "_" + std::to_string(b) + "_" + std::to_string(c);
    fn = fn + "_" + std::to_string(d) + ".pdf";
    plot.plot_lv(t, x, y, "Time", "Population", "Lotka-Volterra Model", fn);
}