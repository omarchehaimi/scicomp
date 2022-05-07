#include "plotting.h"
#include "matrix.h"
#include <matplot/matplot.h>
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>

using namespace matplot;

void Plotting::check_folder(std::string& path) {
    if (std::filesystem::exists(path) == 0) {
        std::cout << "Creating the path." << "\n";
        std::filesystem::create_directory(path);
    }

}

void Plotting::plot_lv(std::vector<double>& t, std::vector<double>& x, 
                       std::vector<double>& y, std::string x_leg, 
                       std::string y_leg, std::string tlt, 
                       std::string fn, std::string path /* The default is "" */) {   
    std::string cur_dir;
    if (!path.empty()) {
        cur_dir = path;
    } else {
        cur_dir = std::filesystem::current_path();
        cur_dir = cur_dir + "/../plots";
    }
    Plotting::check_folder(cur_dir);

    auto h = figure(true);
    h->position({0, 0, 600, 600});
    h->size(1000, 800);
    h->font_size(12);
    h->title(tlt);

    auto p1 = plot(t, x);
    p1->display_name("Prey");
    hold(on);
    auto p2 = plot(t, y);
    p2->display_name("Predator");
    hold(off);

    legend();

    xlabel(x_leg);
    ylabel(y_leg);

    std::string file_name = cur_dir + "/" + fn + ".pdf";
    save(file_name, "pdf");

    show();
}