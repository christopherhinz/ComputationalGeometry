
#include "p3_lib.h"
#include <chrono>
#include <iostream>
#include <iomanip>

// clang++ -std=c++14 line_sweep.cpp && ./a.out > output.txt && open output.txt

#define printf_debug 1

int while_count = 0;
void log_messages(sweep_line& sl, point& E){
    (++while_count, std::cout << "\n======  Durchlauf " << while_count << "  ======\n");
    sl.print_event_queue();
    sl.print_segment_queue();
}

typedef long long LLint;
inline bool indizes_in_range(LLint lower_lim, LLint upper_lim, LLint i_lower, LLint i_upper){
    return (i_upper >= lower_lim && i_upper <= upper_lim) && (i_lower >= lower_lim && i_lower <= upper_lim);
}



int main(){

    std::vector<std::string> filenames //{"strecken/problemkinder.dat"};
                                        //{"strecken/s_1000_10_reduced.dat"};
                                        //{"strecken/s_1000_10.dat"};
                                        {"strecken/VL_example.dat"};
                                        //{"strecken/s_1000_1.dat"};
                                        /*"strecken/s_10000_1.dat",
                                        "strecken/s_100000_1.dat"};*/


    for(auto filename : filenames){
        auto start = std::chrono::steady_clock::now();

        sweep_line sl;
        sl.event_queue = std::vector<point>();

        read_dat(filename, sl.event_queue);

        std::vector<line> lines_by_index{sl.event_queue.size()/2};
        for(auto& p: sl.event_queue){
            if(p.pt == BEG) lines_by_index[p.lineID-1].p1 = p;
            else            lines_by_index[p.lineID-1].p2 = p;
        }


        std::size_t intersect_count = 0;
        std::vector<point> intersec_list;

        sl.sort_event_queue();


        while(sl.event_queue.size() != 0){

            point E = sl.event_queue.back();

            #if printf_debug
                log_messages(sl, E);
            #endif
            int current_index = 0;

            // BEGIN OF LINE
            if(E.pt == point_type::BEG){
                #if printf_debug
                    std::cout << "BEG\n";
                #endif
                if(sl.segment_queue.size() == 0){
                    sl.segment_queue.push_back( segment{.lineID = E.lineID, .y_beg = E.y} );
                }
                else{
                    std::size_t size = sl.segment_queue.size();
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
                if( indizes_in_range(0, sl.segment_queue.size()-1, current_index, current_index-1) ){
                    #if printf_debug                                            
                        std::cout << "BEG: above\n";
                    #endif
                    auto above_intersect = line_intersect_check(lines_by_index[sl.segment_queue[current_index  ].lineID-1], 
                                                                lines_by_index[sl.segment_queue[current_index-1].lineID-1]);
                    if(above_intersect.first && !point_in_point_list(above_intersect.second, sl.event_queue)){
                        sl.event_queue.push_back(above_intersect.second);
                        sl.sort_event_queue();
                    }
                }

                // check segment below recently added segment
                if( indizes_in_range(0, sl.segment_queue.size()-1, current_index, current_index+1) ){
                    #if printf_debug
                        std::cout << "BEG: below\n";
                    #endif
                    auto below_intersect = line_intersect_check(lines_by_index[sl.segment_queue[current_index  ].lineID-1], 
                                                                lines_by_index[sl.segment_queue[current_index+1].lineID-1]);
                    if(below_intersect.first && !point_in_point_list(below_intersect.second, sl.event_queue)){
                        sl.event_queue.push_back(below_intersect.second);
                        sl.sort_event_queue();
                    }
                }                  
            } 

            // END OF LINE
            else if (E.pt == point_type::END){
                #if printf_debug
                    std::cout << "END\n";
                #endif    

                for(std::size_t i = 0; i < sl.segment_queue.size(); ++i){
                    if(sl.segment_queue[i].lineID == E.lineID)
                        current_index = i;
                }

                // check segment above and below current segment
                if( indizes_in_range(0, sl.segment_queue.size()-1, current_index-1, current_index+1) ){
                    #if printf_debug                                            
                        std::cout << "END: above\n";
                    #endif
                    auto above_intersect = line_intersect_check(lines_by_index[sl.segment_queue[current_index-1].lineID-1], 
                                                                lines_by_index[sl.segment_queue[current_index+1].lineID-1]);
                    if(above_intersect.first && !point_in_point_list(above_intersect.second, sl.event_queue)){
                        sl.event_queue.push_back(above_intersect.second);
                        sl.sort_event_queue();
                    }
                }
                sl.erase_segment(E.lineID);        
            } 

            // INTERSECTION
            else if (E.pt == point_type::SEC) {
                #if printf_debug
                    std::cout << "SEC\n";
                #endif 
                if(!point_in_point_list(E, intersec_list))
                    intersec_list.push_back(E);
                std::size_t seg_pos1, seg_pos2;
                #if printf_debug
                    std::cout << "\tline1: ID" << E.line1 << ", line2: ID" << E.line2 << std::endl; 
                #endif
                for(std::size_t i = 0; i < sl.segment_queue.size(); ++i){
                    if(sl.segment_queue[i].lineID == E.line1) 
                        seg_pos1 = i;
                    else if(sl.segment_queue[i].lineID == E.line2) 
                        seg_pos2 = i;
                }
                //if(seg_pos1 > seg_pos2)
                //    std::swap<std::size_t>(seg_pos1, seg_pos2);
                #if printf_debug
                    std::cout << "\tSegments to swap: " << seg_pos1 << " " << seg_pos2 << std::endl;
                #endif
                swap_segments(sl.segment_queue[seg_pos1], sl.segment_queue[seg_pos2]);
                // std::swap<std::size_t>(seg_pos1, seg_pos2);

                               
                
                // check segment above recently added segment
                if( indizes_in_range(0, sl.segment_queue.size()-1, seg_pos1, seg_pos1-1) ){
                    #if printf_debug 
                        std::cout << "SEC: above\n";
                        std::cout << "compare lines: " << sl.segment_queue[seg_pos1  ].lineID << " & " 
                                  << sl.segment_queue[seg_pos1-1].lineID << std::endl;
                    #endif
                    auto above_intersect = line_intersect_check(lines_by_index[sl.segment_queue[seg_pos1  ].lineID-1], 
                                                                lines_by_index[sl.segment_queue[seg_pos1-1].lineID-1]);
                    if(above_intersect.first && !point_in_point_list(above_intersect.second, sl.event_queue)){
                        sl.event_queue.push_back(above_intersect.second);
                        sl.sort_event_queue();
                    }
                }

                // check segment below recently added segment
                if( indizes_in_range(0, sl.segment_queue.size()-1, seg_pos2, seg_pos2+1) ){
                    #if printf_debug                                            
                        std::cout << "SEC: below\n";
                        std::cout << "compare lines: " << sl.segment_queue[seg_pos2  ].lineID << " & " 
                                  << sl.segment_queue[seg_pos2+1].lineID << std::endl;
                    #endif
                    auto below_intersect = line_intersect_check(lines_by_index[sl.segment_queue[seg_pos2  ].lineID-1], 
                                                                lines_by_index[sl.segment_queue[seg_pos2+1].lineID-1]);
                    if(below_intersect.first && !point_in_point_list(below_intersect.second, sl.event_queue)){
                        sl.event_queue.push_back(below_intersect.second);
                        sl.sort_event_queue();
                    }
                } 
                
            }

            for(int i = 0; i < sl.event_queue.size(); ++i){
                if(E == sl.event_queue[i])
                    sl.event_queue.erase(sl.event_queue.begin()+i);
            }
            //if(while_count == 10)
            //    break;
        } 

        std::cout << "INTERSECTIONS\nNumber of intersects: " << intersec_list.size() << std::endl;    
        for(auto intersect : intersec_list)
            std::cout << intersect.x << " " << intersect.y << std::endl;
            //std::cout << intersect << std::endl;
    } 
    return 0;
}
