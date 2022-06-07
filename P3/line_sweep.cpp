
#include "p3_lib.h"
#include <chrono>
#include <iostream>
#include <iomanip>


int main(){

    std::vector<std::string> filenames {"strecken/VL_example.dat"};
                                        /*"strecken/s_1000_1.dat",
                                        "strecken/s_10000_1.dat",
                                        "strecken/s_100000_1.dat"};*/


    for(auto filename : filenames){
        auto start = std::chrono::steady_clock::now();

        sweep_line sl;
        sl.event_queue = std::vector<point>();

        read_dat(filename, sl.event_queue);

        // storage with all lines sorted by index for easy access
        std::vector<line> lines_by_index{sl.event_queue.size()/2};
        for(auto& p: sl.event_queue){
            if(p.pt == BEG) lines_by_index[p.lineID-1].p1 = p;
            else            lines_by_index[p.lineID-1].p2 = p;
        }


        int intersect_count = 0;
        std::vector<point> intersec_list;

        // sortieren nach x Werten, falls x Werte gleich sortieren nach y Werten
        sl.sort_event_queue();
        //sl.init_segment_queue();

    
        while(sl.event_queue.size() != 0){
            sl.print_event_queue();
            point E = sl.event_queue.back();
            if(E.pt == point_type::BEG){
                // muss mit y-Wert passend einsortiert werden
                int current_index;
                if(sl.segment_queue.size() == 0){
                    sl.segment_queue.push_back(E);
                }
                else{
                    int size = sl.segment_queue.size();
                    for(current_index = 0; current_index < size+1; ++current_index){
                        if(sl.segment_queue[current_index].y < E.y){
                            sl.segment_queue.insert(sl.segment_queue.begin()+current_index, E);
                            break;
                        }
                        if(current_index == size){
                            sl.segment_queue.push_back(E);
                            break;
                        }
                    }
                }

                // check segment above recently added segment
                if(current_index < sl.segment_queue.size()-1){
                    auto above_intersect = line_intersect_check(lines_by_index[sl.segment_queue[current_index  ].lineID-1], 
                                                                lines_by_index[sl.segment_queue[current_index+1].lineID-1]);
                    if(above_intersect.first){
                        sl.event_queue.push_back(above_intersect.second);
                        sl.sort_event_queue();
                    }
                }

                // check segment below recently added segment
                if(current_index > 0){
                    auto below_intersect = line_intersect_check(lines_by_index[sl.segment_queue[current_index  ].lineID-1], 
                                                                lines_by_index[sl.segment_queue[current_index-1].lineID-1]);
                    if(below_intersect.first){
                        sl.event_queue.push_back(below_intersect.second);
                        sl.sort_event_queue();
                    }
                }                  
            } 
            else if (E.pt == point_type::END){
            } 
            else if (E.pt == point_type::SEC) {
                intersec_list.push_back(E);
            }

            for(int i = 0; i < sl.event_queue.size(); ++i){
                if(E.pt == sl.event_queue[i].pt && E.lineID == sl.event_queue[i].lineID)
                    sl.event_queue.erase(sl.event_queue.begin()+i);
            }
            //sl.event_queue.pop_back();

        } // while()

        std::cout << "\nINTERSECTIONS\nNumber of intersects: " << intersec_list.size() << std::endl;    
        for(auto intersect : intersec_list)
            std::cout << intersect << std::endl;

    } // for(filename in filenames)




    return 0;
}
