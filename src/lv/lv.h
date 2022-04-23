#ifndef LV_H
#define LV_H

#include <string>

class LV 
{
    public:
        double prey(double x, double y, double a, double b);
        double predator(double x, double y, double c, double d);
        void solve_lv(int n, double dt, double x_0, double y_0, double a, 
                      double b, double c, double d, std::string path="");
};

#endif