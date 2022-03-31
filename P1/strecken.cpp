


#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>


#define N 1000

struct point{
    float x;
    float y;
};

struct line{
    point p1;
    point p2;
};


void read_dat(std::vector<float>& v){
    std::ifstream file;
    file.open("strecken/s_1000_1.dat");
    float data;
    for(int i = 0; i < N; ++i){
        file >> data;
        v.push_back(data);
    }
    file.close();
}


void pack_koords(std::vector<float>& source, std::vector<line>& target){
    line temp;
    for(unsigned int i = 0; i < source.size()/4; ++i){
        temp.p1.x = source[0+i];
        temp.p1.y = source[1+i];
        temp.p2.x = source[2+i];
        temp.p2.y = source[3+i];
        target.push_back(temp);
    }
}

float ccw(point p, point q, point r){
    float res = (p.x*q.y - p.y*q.x)+ (q.x*r.y - q.y*r.x) + (p.y*r.x  - p.x*r.y);
    return res;
}

bool line_intersect_check(line l1, line l2){
    float ccw_res1 = ccw(l1.p1, l1.p2, l2.p1) * ccw(l1.p1, l1.p1, l2.p2);
    float ccw_res2 = ccw(l2.p1, l2.p2, l1.p1) * ccw(l2.p1, l2.p1, l1.p2);
    return (ccw_res1 <= 0 && ccw_res2 <= 0);
}

int main(){
    auto start = std::chrono::steady_clock::now();


    std::vector<float> vec;
    std::vector<line> lines_vec;
    read_dat(vec);
    pack_koords(vec, lines_vec);


    int intersect_counter = 0;
    for(unsigned int i = 0; i < lines_vec.size(); ++i){
        for(unsigned int j = 0; j < lines_vec.size(); ++j){
            if(i!=j){
                if(line_intersect_check(lines_vec[i], lines_vec[j])){
                    ++intersect_counter;
                }
            }
        }
    }

    std::cout << "Strecken insgesamt: " << vec.size() << "\n" << "Schnitte zweier Strecken: " << intersect_counter << "\n";

    auto end = std::chrono::steady_clock::now();     
    std::cout << "Runtime: " 
    << (float)std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()/1000 
        + std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";

    return 0;
}

