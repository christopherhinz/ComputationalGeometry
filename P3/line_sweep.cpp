
#include "p3_lib.h"
#include <chrono>
#include <iostream>
#include <iomanip>

// clang++ -std=c++14 line_sweep.cpp && ./a.out > output.txt && open output.txt

#define printf_debug 0

int while_count = 0;
void log_messages(sweep_line& sl, point& E){
    (++while_count, std::cout << "\n======  Durchlauf " << while_count << "  ======\n");
    sl.print_event_queue();
    //sl.print_segment_queue();
}

inline bool indizes_in_range(long long lower_lim, long long upper_lim, long long i_lower, long long i_upper){
    return (i_upper >= lower_lim && i_upper <= upper_lim) && (i_lower >= lower_lim && i_lower <= upper_lim);
}



int main(){

    std::vector<std::string> filenames //{"strecken/s_1000_10.dat"};
                                        //{"strecken/problemkinder.dat"};
                                        //{"strecken/s_1000_10_reduced.dat"};
                                        //{"strecken/VL_example.dat"};
                                        //{"strecken/s_1000_1.dat"};
                                        //{"strecken/s_10000_1.dat"};
                                        {"strecken/s_100000_1.dat"};


    for(auto filename : filenames){
        auto start = std::chrono::steady_clock::now();

        sweep_line sl;
        sl.event_queue = std::vector<point>();
        std::vector<line> lines_by_index{sl.event_queue.size()/2};
        std::size_t intersect_count = 0;
        std::vector<point> intersec_list;

        read_dat(filename, sl.event_queue, lines_by_index);

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
                    sl.segment_queue.push_back( lines_by_index[E.lineID] );
                }
                else{
                    std::size_t size = sl.segment_queue.size();
                    while(current_index < size+1){
                        //if(sl.segment_queue[current_index].p_beg.y < E.y){
                        if(calc_y_value(E.x, sl.segment_queue[current_index]) < E.y){
                            sl.segment_queue.insert( sl.segment_queue.begin()+current_index,  lines_by_index[E.lineID] );
                            break;
                        }
                        if(current_index == size){
                            sl.segment_queue.push_back( lines_by_index[E.lineID] );
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
                    auto above_intersect = line_intersect_check(sl.segment_queue[current_index  ], 
                                                                sl.segment_queue[current_index-1]);
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
                    auto below_intersect = line_intersect_check(sl.segment_queue[current_index  ], 
                                                                sl.segment_queue[current_index+1]);
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
                    if(sl.segment_queue[i].p_beg.lineID == E.lineID)
                        current_index = i;
                }

                // check segment above and below current segment
                if( indizes_in_range(0, sl.segment_queue.size()-1, current_index-1, current_index+1) ){
                    #if printf_debug                                            
                        std::cout << "END: above\n";
                    #endif
                    auto above_intersect = line_intersect_check(sl.segment_queue[current_index-1], 
                                                                sl.segment_queue[current_index+1]);
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
                    if(sl.segment_queue[i].p_beg.lineID == E.line1) 
                        seg_pos1 = i;
                    else if(sl.segment_queue[i].p_beg.lineID == E.line2) 
                        seg_pos2 = i;
                }
                if(seg_pos1 > seg_pos2)
                    std::swap<std::size_t>(seg_pos1, seg_pos2);
                
                #if printf_debug
                    std::cout << "\tSegments to swap: index1=" << seg_pos1 << " & index2=" << seg_pos2 << std::endl;
                #endif

                #if printf_debug
                std::cout << "segment_queue before swap" << std::endl;
                    sl.print_segment_queue();
                #endif

                swap_lines(sl.segment_queue[seg_pos1], sl.segment_queue[seg_pos2]);
                // std::swap<std::size_t>(seg_pos1, seg_pos2);

                #if printf_debug
                std::cout << "segment_queue after swap" << std::endl;
                    sl.print_segment_queue();
                #endif         
                
                // check segment above recently added segment
                if( indizes_in_range(0, sl.segment_queue.size()-1, seg_pos1, seg_pos1-1) ){
                    #if printf_debug 
                        std::cout << "SEC: above\n";
                        std::cout << "compare lines: lineID=" << sl.segment_queue[seg_pos1  ].p_beg.lineID << " & lineID=" 
                                  << sl.segment_queue[seg_pos1-1].p_beg.lineID << std::endl;
                    #endif
                    auto above_intersect = line_intersect_check(sl.segment_queue[seg_pos1  ], 
                                                                sl.segment_queue[seg_pos1-1]);
                    if(above_intersect.first && !point_in_point_list(above_intersect.second, sl.event_queue) && !point_in_point_list(above_intersect.second, intersec_list)){
                        sl.event_queue.push_back(above_intersect.second);
                        sl.sort_event_queue();
                    }
                }

                // check segment below recently added segment
                if( indizes_in_range(0, sl.segment_queue.size()-1, seg_pos2, seg_pos2+1) ){
                    #if printf_debug                                            
                        std::cout << "SEC: below\n";
                        std::cout << "compare lines: lineID=" << sl.segment_queue[seg_pos2  ].p_beg.lineID << " & lineID=" 
                                  << sl.segment_queue[seg_pos2+1].p_beg.lineID << std::endl;
                    #endif
                    auto below_intersect = line_intersect_check(sl.segment_queue[seg_pos2  ], 
                                                                sl.segment_queue[seg_pos2+1]);
                    if(below_intersect.first && !point_in_point_list(below_intersect.second, sl.event_queue) && !point_in_point_list(below_intersect.second, intersec_list)){
                        sl.event_queue.push_back(below_intersect.second);
                        sl.sort_event_queue();
                    }
                } 
                
            }
            #if printf_debug
            std::cout << std::endl;
                sl.print_segment_queue();
            #endif

            for(int i = 0; i < sl.event_queue.size(); ++i){
                if(E == sl.event_queue[i])
                    sl.event_queue.erase(sl.event_queue.begin()+i);
            }
            if(while_count == 12)
                break;
        } 

        auto end = std::chrono::steady_clock::now();
        double runtime = (double)std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()/
            1000 + std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << runtime << " ms\n\n";

        std::cout << "INTERSECTIONS\nNumber of intersects: " << intersec_list.size() << std::endl;    
        //for(auto intersect : intersec_list)
        //    std::cout << intersect.x << " " << intersect.y << std::endl;
    } 
    return 0;
}
