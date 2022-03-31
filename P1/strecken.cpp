

#include "p1_lib.h"
#include <chrono>


int main(){
    auto start = std::chrono::steady_clock::now();


    std::vector<float> vec;
    std::vector<line> lines_vec;
    read_dat(vec);
    pack_koords(vec, lines_vec);


    int intersect_counter = 0;
    for(unsigned int i = 0; i < lines_vec.size(); ++i){
        for(unsigned int j = 0; j < lines_vec.size(); ++j){
            if(i!=j){
                if(line_intersect_check(lines_vec[i], lines_vec[j])){
                    ++intersect_counter;
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

