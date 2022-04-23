#include <matplot/matplot.h>

using namespace matplot;

int main() {

    std::cout << "Testing Matplot++ library. \n"; 
    plot({1.0, 0.7, 0.4, 0.0, -0.4, -0.7, -1}, "k");
    std::cout << "Matplot++ tested successfully! \n";
    show();
}