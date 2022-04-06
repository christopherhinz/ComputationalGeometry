

#include "p1_lib.h"
#include <chrono>

void print_line(line l1){
    std::cout << "strecke: (" << l1.p1.x << " " << l1.p1.y << "), " <<  "( " << l1.p2.x << " " << l1.p2.y << ")";
} 

int main(){
    auto start = std::chrono::steady_clock::now();


    std::vector<float> vec;
    std::vector<line> lines_vec;
    read_dat((char*)"../strecken/s_1000_1.dat", 1000, vec);
    pack_koords(vec, lines_vec);


    int intersect_counter = 0;
    for(unsigned int i = 0; i < lines_vec.size(); ++i){
        for(unsigned int j = 0; j < lines_vec.size(); ++j){
            if(i!=j){
                if(line_intersect_check(lines_vec[i], lines_vec[j])){
                    ++intersect_counter;
                    if(intersect_counter >= 4400){
                        print_line(lines_vec[i]);
                        std::cout << " -> ";
                        print_line(lines_vec[j]);
                        std::cout << "\n";
                    }
                }
            }
        }
    }
    std::cout << "Strecken insgesamt: " << vec.size() << "\n" << "Schnitte zweier Strecken: " << intersect_counter << "\n";

    auto end = std::chrono::steady_clock::now();     
    std::cout << "Runtime: " 
    << (float)std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()/1000 
        + std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";

    return 0;
}

