#include "p1_lib.h"
#include <chrono>
#include <iostream>
#include <iomanip>

void print_line(line l1){
    std::cout << "strecke: (" << l1.p1.x << " " << l1.p1.y << "), " <<  "(" << l1.p2.x << " " << l1.p2.y << ")";
}

void print_content(std::vector<line>& vec, int limit){
    int counter = 0;
    for(auto x : vec){
        if(counter < limit){
            print_line(x);
            std::cout << "\n";
            ++counter;
        }
    }
}

int main(){
    output_values output_array[NOF_DATAFILES];

    std::vector<std::string> file_paths{"s_1000_1.dat",
                                        "s_10000_1.dat",
                                        "s_100000_1.dat"};

    for(auto file_path : file_paths){
        auto start = std::chrono::steady_clock::now();

        std::vector<line> lines_vec;
        read_dat(file_path, lines_vec);
        int intersect_counter = 0;

        for(unsigned int i = 0; i < lines_vec.size(); ++i){
            for(unsigned int j = i; j < lines_vec.size(); ++j){
                if(i!=j){
                    if(line_intersect_check(lines_vec[i], lines_vec[j])){
                        ++intersect_counter;
                    }
                }
            }
        }


        std::cout << "Datei: " << file_path << std::endl;
        std::cout << "Strecken insgesamt: " << lines_vec.size() << std::endl;
        std::cout << "Anzahl der Schnitte: " << intersect_counter << std::endl;

        auto end = std::chrono::steady_clock::now();
        std::cout << "Laufzeit: "
        << (double)std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()/1000
            + std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
    }

    return 0;
}
