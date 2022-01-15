#ifndef PLOTTING_H
#define PLOTTING_H

#include "../../include/matplotlibcpp.h"
#include <vector>
#include <string>

/**
 * @class Plotting
 * @brief Class with plotting functions.
 */

class Plotting 
{
    private:
        /** Width and height of the figure for the plot */
        int w;
        int h;

        /** Check if the folder exists and if not create it */
        void check_folder(std::string& path);
    
    public:
        /** Constructor and destructor */
        Plotting() {};
        Plotting(int w, int h);

        /** Plot and save */
        void plot_lv(std::vector<double>& t, std::vector<double>& x, 
                     std::vector<double>& y, std::string x_leg, 
                     std::string y_leg, std::string title, 
                     std::string fn, std::string path="");

};

#endif