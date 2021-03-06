#include "../p1_lib.h"
#include <chrono>

struct line_pair{
    line l1;
    line l2;
};

void write_csv(char* filename, std::vector<line_pair>& intersects){
    std::ofstream file;
    file.open ("intersections.csv");
    if(!file.is_open()){
        std::cout << "Could not open file\n";
    }
    for(auto i = 0; i < intersects.size(); ++i){
        file << intersects[i].l1.p1.x << ";" << intersects[i].l1.p1.y << ";" << intersects[i].l1.p2.x << ";" << intersects[i].l1.p2.y << "\n";
        file << intersects[i].l2.p1.x << ";" << intersects[i].l2.p1.y << ";" << intersects[i].l2.p2.x << ";" << intersects[i].l2.p2.y << "\n\n";
    }
    file.close();
}


int main(){
    std::vector<line> lines_vec;
    std::vector<line_pair> result_vec;
    line_pair lp;
    read_dat((char*)"../strecken/s_10000_1.dat", lines_vec);


    int intersect_counter = 0;
    for(unsigned int i = 0; i < lines_vec.size(); ++i){
        for(unsigned int j = i; j < lines_vec.size(); ++j){
            if(i!=j){
                if(line_intersect_check(lines_vec[i], lines_vec[j])){
                    ++intersect_counter;
                    lp.l1 = lines_vec[i];
                    lp.l2 = lines_vec[j];
                    result_vec.push_back(lp);
                }
            }
        }
    }
    write_csv((char*)"result.csv", result_vec);
    std::cout << "Strecken insgesamt: " << lines_vec.size() << "\n" << "Schnitte zweier Strecken: " << intersect_counter << "\n";

    return 0;
}