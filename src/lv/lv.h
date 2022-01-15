#ifndef LV_H
#define LV_H

#include <string>

class LV 
{
    public:
        void solve_lv(int n, double dt, double x_0, double y_0, double a, 
                      double b, double c, double d, std::string path="");
};

#endif