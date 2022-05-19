#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct point{
    double x;
    double y;
};

struct line{
    point p1;
    point p2;
};

<<<<<<< HEAD
void read_dat(std::string filename, std::vector<line>& target){
    line temp;
    std::ifstream file;
    file.open(filename.c_str());
    double k1, k2, k3, k4;
    if(!file.is_open()){
        std::cout << "Could not open file\n";
    }
=======
void read_dat(char* filename, std::vector<line>& target){
    line temp;
    std::ifstream file;
    file.open(filename);
    double k1, k2, k3, k4;
>>>>>>> 6da1d0c981bc1ff2e84f838b23f6d3a6efccb28a
    while(file >> k1 >> k2 >> k3 >> k4){
        temp.p1.x = k1;
        temp.p1.y = k2;
        temp.p2.x = k3;
        temp.p2.y = k4;
        target.push_back(temp);
    }
    file.close();
}

double ccw(point p, point q, point r){
    double res = (p.x*q.y - p.y*q.x)+ (q.x*r.y - q.y*r.x) + (p.y*r.x  - p.x*r.y);
    return res;
}

bool line_intersect_check(line l1, line l2){
    bool retval = false;
    double ccw_res1 = ccw(l1.p1, l1.p2, l2.p1) * ccw(l1.p1, l1.p2, l2.p2);
    double ccw_res2 = ccw(l2.p1, l2.p2, l1.p1) * ccw(l2.p1, l2.p2, l1.p2);
<<<<<<< HEAD
    if(ccw_res1 <= 0.0 && ccw_res2 <= 0.0){
        retval = true;
        if(ccw_res1 == 0.0 && ccw_res2 == 0.0){
            double lambda1 = (l2.p1.x-l1.p1.x)/(l1.p2.x-l1.p1.x);
            double lambda2 = (l2.p2.x-l1.p1.x)/(l1.p2.x-l1.p1.x);
            if ((lambda1 < 0.0 || lambda1 > 1.0) && (lambda2 < 0.0 || lambda2 > 1.0))
=======
    if(ccw_res1 <= 0.0f && ccw_res2 <= 0.0f){
        retval = true;
        if(ccw_res1 == 0.0f && ccw_res2 == 0.0f){
            double lambda1 = (l1.p1.x-l2.p1.x)/(l2.p2.x-l2.p1.x);
            double lambda2 = (l1.p2.x-l2.p1.x)/(l2.p2.x-l2.p1.x);
            if ((lambda1 < 0 || lambda1 > 1) && (lambda2 < 0 || lambda2 > 1)) 
>>>>>>> 6da1d0c981bc1ff2e84f838b23f6d3a6efccb28a
                retval = false;
        }
    }
    return retval;
}
