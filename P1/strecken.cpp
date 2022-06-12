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
    std::vector<std::string> filenames {"strecken/s_1000_1.dat",
                                        "strecken/s_10000_1.dat",
                                        "strecken/s_100000_1.dat"};

    std::cout << std::left << std::setw(16) << "Datei" << std::setw(1) << "|"
              << std::setw(10) << " Strecken" << std::setw(1) << "|"
              << std::setw(10) << " Schnitte" << std::setw(1) << "|"
              << std::setw(10) << " Laufzeit" << std::endl;

    for(auto filename : filenames){
        auto start = std::chrono::steady_clock::now();

        std::vector<line> lines_vec;
        read_dat(filename, lines_vec);
        int lines_count = lines_vec.size();
        int intersect_count = 0;

        for(unsigned int i = 0; i < lines_vec.size(); ++i){
            for(unsigned int j = i; j < lines_vec.size(); ++j){
                if(i!=j){
                    if(line_intersect_check(lines_vec[i], lines_vec[j])){
                        ++intersect_count;
                    }
                }
            }
        }

        auto end = std::chrono::steady_clock::now();
        double runtime = (double)std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()/
            1000 + std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        std::cout << std::left << std::setw(16) << filename << std::setw(1) << "|"
                  << " " << std::setw(9) << lines_count     << std::setw(1) << "|"
                  << " " << std::setw(9) << intersect_count << std::setw(1) << "|"
                  << " " << std::setw(10) << std::setprecision(2) << std::right << std::fixed
                  << runtime << " ms" << std::endl;
    }

    return 0;
}
