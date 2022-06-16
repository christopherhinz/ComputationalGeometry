

#include "p3_lib.h"


int main(){


    std::string filename = "strecken/s_100000_1.dat"; 
    std::vector<point> points;
    std::vector<line> lines; 
    std::vector<point> intersects;
    std::vector<line> reduced_lines; 

    point invalid_point{.x = -1.0, .y = -1.0};
    
    read_dat(filename, points, lines);

    bool is_valid = true;
    for(std::size_t i = 0; i < lines.size(); ++i){
        is_valid = true;
        if(lines[i].p_beg.x == lines[i].p_end.x && lines[i].p_beg.y == lines[i].p_end.y){
            //std::cout << "1. Sonderfall (Länge null): \n\t" <<  lines[i] << std::endl;
            is_valid = false;
        }
        if(lines[i].p_beg.x == lines[i].p_end.x){
            //std::cout << "2. Sonderfall (parallel y-Achse): \n\t" <<  lines[i] << std::endl;;
            is_valid = false;
        }

        for(std::size_t j = i+1; j < lines.size(); ++j){
            auto result = line_intersect_check(lines[i], lines[j]);
            if(result.first == false && same_koords(result.second, invalid_point)){
                //std::cout << "3. Sonderfall (Überlappung): \n\t" << lines[i] << " & " << lines[j] << "\n";
                is_valid = false;
                break;
            }
            if(result.first == true){
                if( same_koords(result.second, lines[i].p_beg) || same_koords(result.second, lines[i].p_end) || 
                    same_koords(result.second, lines[j].p_beg) || same_koords(result.second, lines[j].p_end) ){
                    //std::cout << "4. Sonderfall (unechter Schnitt): \n\t" << lines[i] << " & " << lines[j] << "\n";
                    is_valid = false;
                    break;
                }
                if(point_in_point_list(result.second, intersects)){
                    //std::cout << "4. Sonderfall (Mehrfachschnitt): \n\t" << lines[i] << " & " << lines[j] << "\n";
                    is_valid = false;
                    break;
                }
                intersects.push_back(result.second);
            }
        
        }

        // store legal line in container
        if(is_valid)
            reduced_lines.push_back(lines[i]);
    }

    for(auto l: reduced_lines){
        std::cout << l.p_beg.x << " " << l.p_beg.y << " " << l.p_end.x << " " << l.p_end.y << std::endl;
    }

    return 0;
}

/*
clang++ -std=c++14 reduce_dat_files.cpp && ./a.out > strecken/s_100000_1_reduced.dat
*/