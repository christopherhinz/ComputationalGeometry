#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct point{
    double x;
    double y;
};
inline std::ostream& operator<<(std::ostream& os, point& p){
    os << "koords=(" << p.x << "," << p.y << ")";
    return os;
}

struct line{
    point p1;
    point p2;
};
inline std::ostream& operator<<(std::ostream& os, line& l){
    os << l.p1 << " <-> " << l.p2;
    return os;
}

void read_dat(std::string filename, std::vector<line>& target){
    line temp;
    std::ifstream file;
    file.open(filename.c_str());
    double k1, k2, k3, k4;
    if(!file.is_open()){
        std::cout << "Could not open file\n";
    }
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

point calc_intersect_point(line _l1, line _l2){
    line l1, l2;
    l1.p1 = _l1.p1;
    l1.p2 = {.x = _l1.p2.x - _l1.p1.x, .y = _l1.p2.y - _l1.p1.y};
    l2.p1 = _l2.p1;
    l2.p2 = {.x = _l2.p2.x - _l2.p1.x, .y = _l2.p2.y - _l2.p1.y};
    double lambda2 = (l1.p1.y + l2.p1.x*l1.p2.y/l1.p2.x - l2.p1.y - l1.p1.x*l1.p2.y/l1.p2.x)/(l2.p2.y - l2.p2.x*l1.p2.y/l1.p2.x);
    point intersect_point = {.x = l2.p1.x + lambda2 * l2.p2.x, .y = l2.p1.y + lambda2 * l2.p2.y};
    //std::cout << intersect_point.x << " " << intersect_point.y << " lines: l1=" << _l1 << " & l2=" << _l2 << std::endl;
    return intersect_point;
}

bool line_intersect_check(line l1, line l2){
    bool retval = false;
    double ccw_res1 = ccw(l1.p1, l1.p2, l2.p1) * ccw(l1.p1, l1.p2, l2.p2);
    double ccw_res2 = ccw(l2.p1, l2.p2, l1.p1) * ccw(l2.p1, l2.p2, l1.p2);
    if(ccw_res1 <= 0.0 && ccw_res2 <= 0.0){
        retval = true;
        if(ccw_res1 == 0.0 && ccw_res2 == 0.0){
            double lambda1 = (l2.p1.x-l1.p1.x)/(l1.p2.x-l1.p1.x);
            double lambda2 = (l2.p2.x-l1.p1.x)/(l1.p2.x-l1.p1.x);
            if ((lambda1 < 0.0 || lambda1 > 1.0) && (lambda2 < 0.0 || lambda2 > 1.0))
                retval = false;
        }
    }
    if(retval){
        calc_intersect_point(l1, l2);
    }
    return retval;
}
