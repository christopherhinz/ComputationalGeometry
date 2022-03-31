

#include "p1_lib.h"


/*
Hier sollen alle möglichen Streckenanordnungen getestet werden zur Validierung der Funktionen


*/


int main(){


    // Strecken mit senkrechntem Schnitt
    // l1 von  p1 = (0,1) nach p2 = (0,-1)
    // l2 von  p1 = (1,0) nach p2 = (-1,0)
    line l1 = {.p1.x = 0, .p1.y = 1, .p2.x = 0, .p2.y = -1};
    line l2 = {.p1.x = 1, .p1.y = 0, .p2.x = -1, .p2.y = 0};
    std::cout << std::boolalpha << line_intersect_check(l1, l2) << "\n";

    



    return 0;
}

