
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

    std::vector<std::string> filenames {"strecken/s_1000_1.dat"};/*,
                                        "strecken/s_10000_1.dat",
                                        "strecken/s_100000_1.dat"};*/

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

        std::cout << "Number of events: " << sl.event_queue.size() << std::endl;
    
        while(sl.event_queue.size() != 0){
            point E = sl.event_queue.back();
            if(E.pt == point_type::BEG){
                // add new segment to sl
                //TreatLeftEndpoint(E, sl);
            } 
            else if (E.pt == point_type::END){
                // remove segment from sl
                //TreatRightEndpoint(E, sl);
            } 
            else {
                // swap intersecting segments in sl
                //TreatIntersection(E, sl);
            }
            sl.event_queue.pop_back();
        }

        std::cout << "Number of intersects: " << intersec_list.size() << std::endl;    

    }



    return 0;
}
