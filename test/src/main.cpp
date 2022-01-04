#include "../../include/matplotlibcpp.h"

namespace plt = matplotlibcpp;

int main() {

    std::cout << "Testing matplotlib library. \n"; 
    plt::plot({1,3,2,4});
    std::cout << "matplotlib tested successfully! \n";
    plt::show();
}