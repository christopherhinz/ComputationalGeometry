
#include "p3_lib.h"
#include <chrono>
#include <iostream>
#include <iomanip>

int while_count = 0;
void log_messages(sweep_line& sl, point& E){
    (++while_count, std::cout << "======  Durchlauf " << while_count << "  ======\n");
    //std::cout << "Current Event: " << (E.pt == 0 ? "BEG " : E.pt == 1 ? "END " : "SEC ") << E.lineID << "\n";
    sl.print_event_queue();
    sl.print_segment_queue();
}

typedef unsigned long long uintLL;

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


        uintLL intersect_count = 0;
        std::vector<point> intersec_list;

        // sortieren nach x Werten, falls x Werte gleich sortieren nach y Werten
        sl.sort_event_queue();

        while(sl.event_queue.size() != 0){

            point E = sl.event_queue.back();

            log_messages(sl, E);
            int current_index = 0;

            // BEGIN OF LINE
            if(E.pt == point_type::BEG){
                // muss mit y-Wert passend einsortiert werden
                if(sl.segment_queue.size() == 0){
                    sl.segment_queue.push_back( segment{.lineID = E.lineID, .y_beg = E.y} );
                }
                else{
                    uintLL size = sl.segment_queue.size();
                    while(current_index < size+1){
                        if(sl.segment_queue[current_index].y_beg < E.y){
                            sl.segment_queue.insert( sl.segment_queue.begin()+current_index, segment{.lineID = E.lineID, .y_beg = E.y} );
                            break;
                        }
                        if(current_index == size){
                            sl.segment_queue.push_back( segment{.lineID = E.lineID, .y_beg = E.y} );
                            break;
                        }
                        ++current_index;
                    }
                }

                // check segment above recently added segment
                if(current_index < sl.segment_queue.size()-1){
                    auto above_intersect = line_intersect_check(lines_by_index[sl.segment_queue[current_index  ].lineID-1], 
                                                                lines_by_index[sl.segment_queue[current_index+1].lineID-1]);
                    if(above_intersect.first && !point_in_event_queue(above_intersect.second, sl.event_queue)){
                        sl.event_queue.push_back(above_intersect.second);
                        sl.sort_event_queue();
                    }
                }

                // check segment below recently added segment
                if(current_index > 0){
                    auto below_intersect = line_intersect_check(lines_by_index[sl.segment_queue[current_index  ].lineID-1], 
                                                                lines_by_index[sl.segment_queue[current_index-1].lineID-1]);
                    if(below_intersect.first && !point_in_event_queue(below_intersect.second, sl.event_queue)){
                        sl.event_queue.push_back(below_intersect.second);
                        sl.sort_event_queue();
                    }
                }                  
            } 

            // END OF LINE
            else if (E.pt == point_type::END){

                for(uintLL i = 0; i < sl.segment_queue.size(); ++i){
                    if(sl.segment_queue[i].lineID == E.lineID)
                        current_index = i;
                }

                // check segment above and below current segment
                if(current_index > 0 && current_index < sl.segment_queue.size()-1){
                    auto above_intersect = line_intersect_check(lines_by_index[sl.segment_queue[current_index-1].lineID-1], 
                                                                lines_by_index[sl.segment_queue[current_index+1].lineID-1]);
                    if(above_intersect.first && !point_in_event_queue(above_intersect.second, sl.event_queue)){
                        sl.event_queue.push_back(above_intersect.second);
                        sl.sort_event_queue();
                    }
                }
                //sl.event_queue.erase(sl.event_queue.begin()+current_index);        
                sl.erase_segment(E.lineID);        
            } 

            // INTERSECTION
            else if (E.pt == point_type::SEC) {
                intersec_list.push_back(E);
                uintLL i_line1, i_line2;
                for(uintLL i = 0; i < sl.segment_queue.size(); ++i){
                    if(sl.segment_queue[i].lineID == lines_by_index[E.line1].p1.lineID) 
                        i_line1 = i;
                    else if(sl.segment_queue[i].lineID == lines_by_index[E.line2].p1.lineID) 
                        i_line2 = i;
                }
                std::cout << "Segments to swap: " << i_line1 << " " << i_line2 << std::endl;
                swap_segments(sl.segment_queue[i_line1], sl.segment_queue[i_line2]);

                               
                
                // check segment above recently added segment
                if(i_line1 < sl.segment_queue.size()-1){
                    auto above_intersect = line_intersect_check(lines_by_index[sl.segment_queue[i_line1  ].lineID-1], 
                                                                lines_by_index[sl.segment_queue[i_line1+1].lineID-1]);
                    if(above_intersect.first && !point_in_event_queue(above_intersect.second, sl.event_queue)){
                        std::cout << "added1: " << above_intersect.second << "\n";
                        sl.event_queue.push_back(above_intersect.second);
                        sl.sort_event_queue();
                    }
                }

                // check segment below recently added segment
                if(i_line2 > 0 && sl.segment_queue.size() >= 2){
                    auto below_intersect = line_intersect_check(lines_by_index[sl.segment_queue[i_line2  ].lineID-1], 
                                                                lines_by_index[sl.segment_queue[i_line2-1].lineID-1]);
                    if(below_intersect.first && !point_in_event_queue(below_intersect.second, sl.event_queue)){
                        std::cout << "added2: " << below_intersect.second << "\n";
                        sl.event_queue.push_back(below_intersect.second);
                        sl.sort_event_queue();
                    }
                } 
                
            }

            for(int i = 0; i < sl.event_queue.size(); ++i){
                if(E.pt == sl.event_queue[i].pt && E.lineID == sl.event_queue[i].lineID){
                    std::cout << "removed from event_queue: " << E << std::endl;
                    sl.event_queue.erase(sl.event_queue.begin()+i);
                }
            }

            //if(while_count == 7)
            //    break;

        } // while()

        std::cout << "\nINTERSECTIONS\nNumber of intersects: " << intersec_list.size() << std::endl;    
        for(auto intersect : intersec_list)
            std::cout << intersect << std::endl;

    } // for(filename in filenames)




    return 0;
}
