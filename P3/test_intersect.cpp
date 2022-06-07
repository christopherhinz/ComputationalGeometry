
#include "p3_lib.h"


int main(int argc, char* argv[]){

    point p11 = {.x = 1.0, .y = 0.0};
    point p12 = {.x = -1.0, .y = 0.0};
    line l1 = {p11, p12};

    point p21 = {.x = 0.0, .y = 1.0};
    point p22 = {.x = 0.0, .y = -1.0};
    line l2 = {p21, p22};

    auto result1 = line_intersect_check(l1, l2);
    std::cout << l1 << " & " << l2 << std::endl;
    std::cout <<  std::boolalpha << "intersect: " << result1.first << ", point: " << result1.second << std::endl;


    point p31 = {.x = 0.0, .y = 2.0};
    point p32 = {.x = 2.0, .y = 0.0};
    line l3 = {p31, p32};

    point p41 = {.x = 0.5, .y = 0.5};
    point p42 = {.x = 1.5, .y = 1.5};
    line l4 = {p41, p42};

    auto result2 = line_intersect_check(l3, l4);
    std::cout << l3 << " & " << l4 << std::endl;
    std::cout <<  std::boolalpha << "intersect: " << result2.first << ", point: " << result2.second << std::endl;

    return 0;
}