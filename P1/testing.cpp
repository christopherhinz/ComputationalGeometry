

#include "p1_lib.h"


/*
Hier sollen alle möglichen Streckenanordnungen getestet werden zur Validierung der Funktionen
*/

void print_result(line l1, line l2){
    std::cout << std::boolalpha << "Soll: true, Ist: " << line_intersect_check(l1, l2) << "\n";
}


int main(){

    // Verschiedene Schnitte

    // Strecken mit senkrechtem Schnitt (symmetrisch)
    // p1 = (0,1) nach p2 = (0,-1)
    // p1 = (1,0) nach p2 = (-1,0
    print_result(line{.p1.x = 0, .p1.y = 1, .p2.x = 0, .p2.y = -1}, line{.p1.x = 1, .p1.y = 0, .p2.x = -1, .p2.y = 0});

    // Strecken mit senkrechtem Schnitt (unsymmetrisch)
    // p1 = (0,2) nach p2 = (0,0)
    // p1 = (1,0) nach p2 = (-1,0)
    print_result(line{.p1.x = 0, .p1.y = 2, .p2.x = 0, .p2.y = 0}, line{.p1.x = 1, .p1.y = 0, .p2.x = -1, .p2.y = 0});
    
    // Strecken auf gleicher Gerade mit Schnitt in einem Punkt
    // p1 = (1,0) nach p2 = (2,0)
    // p1 = (1,0) nach p2 = (-1,0)
    print_result(line{.p1.x = 1, .p1.y = 0, .p2.x = 2, .p2.y = 0}, line{.p1.x = 1, .p1.y = 0, .p2.x = -1, .p2.y = 0});

    // Strecken auf gleicher Gerade mit Schnitt in einer Strecke
    // p1 = (0,0) nach p2 = (2,0)
    // p1 = (1,0) nach p2 = (-1,0)
    print_result(line{.p1.x = 0, .p1.y = 0, .p2.x = 2, .p2.y = 0}, line{.p1.x = 1, .p1.y = 0, .p2.x = -1, .p2.y = 0});

    // Strecken auf gleicher Gerade mit Schnitt in einer Strecke
    // p1 = (0,0) nach p2 = (2,0)
    // p1 = (1,0) nach p2 = (-1,0)
    print_result(line{.p1.x = 1, .p1.y = 0, .p2.x = -1, .p2.y = 1}, line{.p1.x = 1, .p1.y = 0, .p2.x = -1, .p2.y = 0});


    // Verschiedene ohne Schnitt

    // Strecken ohne Schnitt auf Gerade
    // p1 = (-2,0) nach p2 = (0,0)
    // p1 = (1,0) nach p2 = (3,0)
    line l11 = {.p1.x = -2, .p1.y = 0, .p2.x = 0, .p2.y = 0};
    line l12 = {.p1.x = 1, .p1.y = 0, .p2.x = 3, .p2.y = 0};
    std::cout << std::boolalpha << "Soll: false, Ist: " << line_intersect_check(l11, l12) << "\n";

    // Strecken ohne Schnitt parallel
    // p1 = (-2,0) nach p2 = (0,0)
    // p1 = (-2,1) nach p2 = (0,2)
    print_result(line{.p1.x = -2, .p1.y = 0, .p2.x = 0, .p2.y = 0}, line{.p1.x = -2, .p1.y = 1, .p2.x = 0, .p2.y = 2});

    // Strecken ohne Schnitt schräg
    // p1 = (-2,0) nach p2 = (0,0)
    // p1 = (0,1) nach p2 = (2,0)
    print_result(line{.p1.x = -2, .p1.y = 0, .p2.x = 0, .p2.y = 0}, line{.p1.x = 0, .p1.y = 1, .p2.x = 2, .p2.y = 0});

    return 0;
}

