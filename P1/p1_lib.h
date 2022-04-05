#include <fstream>
#include <iostream>
#include <string>
#include <vector>


struct point{
    float x;
    float y;
};

struct line{
    point p1;
    point p2;
};


void read_dat(char* filename, unsigned int N, std::vector<float>& v){
    std::ifstream file;
    file.open(filename);
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
    bool retval = false;
    float ccw_res1 = ccw(l1.p1, l1.p2, l2.p1) * ccw(l1.p1, l1.p2, l2.p2);
    float ccw_res2 = ccw(l2.p1, l2.p2, l1.p1) * ccw(l2.p1, l2.p2, l1.p2);
    if(ccw_res1 <= 0.0f && ccw_res2 <= 0.0f){
        retval = true;
        if(ccw_res1 == 0.0f && ccw_res2 == 0.0f){
            float lambda1 = (l1.p1.x-l2.p1.x)/(l2.p2.x-l2.p1.x);
            float lambda2 = (l1.p2.x-l2.p1.x)/(l2.p2.x-l2.p1.x);
            if ((lambda1 < 0 || lambda1 > 1) && (lambda2 < 0 || lambda2 > 1)) retval = false;
        }
    }
    return retval;
}
