
#include "p3_lib.h"


int main(){

    line l_test = { point{.x = 1.0, .y = 4.0}, point{.x = 7.0, .y = 2.0}};
    double y_current = calc_y_value(4.0 ,l_test);
    std::cout << "Test\n";
    std::cout << y_current << std::endl;

    l_test = { point{.x = 0.0, .y = 0.0}, point{.x = 6.0, .y = 6.0}};
    y_current = calc_y_value(4.0 ,l_test);
    std::cout << "Test\n";
    std::cout << y_current << std::endl;

    l_test = { point{.x = 2.0, .y = 5.0}, point{.x = 6.0, .y = 5.0}};
    y_current = calc_y_value(4.0 ,l_test);
    std::cout << "Test\n";
    std::cout << y_current << std::endl;

    return 0;
}