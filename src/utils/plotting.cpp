#include "plotting.h"
#include <vector>
#include <string>
#include <filesystem>

namespace plt = matplotlibcpp;

// Plotting::Plotting(int w, int h)
// {
//     this->w = w;
//     this->h = h;
// }

void Plotting::check_folder(std::string& path)
{
    if (std::filesystem::exists(path) == 0) {
        std::cout << "Creating the path." << "\n";
        std::filesystem::create_directory(path);
    }

}

void Plotting::plot_lv(std::vector<double>& t, std::vector<double>& x, 
                       std::vector<double>& y, std::string x_leg, 
                       std::string y_leg, std::string title, 
                       std::string fn, std::string path /* The default is "" */)
{   
    std::string cur_dir;
    if (!path.empty()) {
        cur_dir = path;
    } else {
        cur_dir = std::filesystem::current_path();
        cur_dir = cur_dir + "/../plots";
    }
    Plotting::check_folder(cur_dir);

    plt::figure();
    plt::plot(t, x, {{"label", "Predator"}});
    plt::plot(t, y, {{"label", "Prey"}});
    plt::xlabel(x_leg);
    plt::ylabel(y_leg);
    plt::title(title);
    plt::legend();

    plt::save(cur_dir+"/"+fn);

    plt::show();
}