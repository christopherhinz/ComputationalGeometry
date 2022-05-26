#include "p3_lib.h"
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

        sweep_line sl;
        sl.event_queue = std::vector<point>();

        read_dat(filename, sl.event_queue);
        int intersect_count = 0;
        std::vector<point> intersec_list;

        // sortieren nach x Werten, falls x Werte gleich sortieren nach y Werten
        sl.sort_event_queue();
        sl.init_segment_queue();

        while(sl.event_queue.size() != 0){
            point E = sl.event_queue.pop_back();
            if(E.pt == point_type::BEG){
                TreatLeftEndoint(E, sl);
            } else if (E.pt == point_type::END){
                TreatRightEndpoint(E, sl);
            } else {
                Treatintersection(E, sl);
            }
        }




        /*
        int lines_count = 0;//lines_vec.size();
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
                  */
    }



    return 0;
}
