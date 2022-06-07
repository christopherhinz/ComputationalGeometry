#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

enum point_type { BEG = 0, END, SEC};

struct point{
    double x;
    double y;
    point_type pt;
    std::size_t lineID;
};
std::ostream& operator<<(std::ostream& os, point& p){
    os << "(" << p.x << "," << p.y << ")";
    return os;
}

struct line{
    point p1;
    point p2;
};
std::ostream& operator<<(std::ostream& os, line& l){
    os << l.p1 << " <-> " << l.p2;
    return os;
}

struct sweep_line{
    point current_event;
    std::vector<point> segment_queue;
    std::vector<point> event_queue;
    void sort_event_queue(){
        std::sort(event_queue.begin(), event_queue.end(), [](point& p1, point& p2){return p1.x == p2.x ? p1.y > p2.y : p1.x > p2.x;});
    }
    void init_segment_queue(){
        segment_queue.push_back(event_queue.back());
    }
    void print_event_queue(){
        std::cout << "Event queue:\n";
        for(auto& elem : event_queue)
            std::cout << "\t lineID " << elem.lineID << ": "<< elem << "\n";
        std::cout << "\n";
    }
};

void read_dat(std::string filename, std::vector<point>& target){
    point pb, pe;
    std::size_t countID = 1;
    std::ifstream file;
    file.open(filename.c_str());
    double k1, k2, k3, k4;
    if(!file.is_open()){
        std::cout << "Could not open file\n";
    }
    while(file >> k1 >> k2 >> k3 >> k4){
        if(k1 < k3){
            pb = { k1, k2, BEG, countID};
            pe = { k3, k4, END, countID};
        }
        else{
            pb = { k1, k2, END, countID};
            pe = { k3, k4, BEG, countID};
        }
        ++countID;
        target.push_back(pb);
        target.push_back(pe);
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
    return intersect_point;
}

std::pair<bool, point> line_intersect_check(line l1, line l2){
    bool retval = false;
    point p_intersect = {.x = 0.0, .y = 0.0};
    double ccw_res1 = ccw(l1.p1, l1.p2, l2.p1) * ccw(l1.p1, l1.p2, l2.p2);
    double ccw_res2 = ccw(l2.p1, l2.p2, l1.p1) * ccw(l2.p1, l2.p2, l1.p2);
    double lambda1, lambda2;
    if(ccw_res1 <= 0.0 && ccw_res2 <= 0.0){
        retval = true;
        if(ccw_res1 == 0.0 && ccw_res2 == 0.0){
            lambda1 = (l2.p1.x-l1.p1.x)/(l1.p2.x-l1.p1.x);
            lambda2 = (l2.p2.x-l1.p1.x)/(l1.p2.x-l1.p1.x);
            if ((lambda1 < 0.0 || lambda1 > 1.0) && (lambda2 < 0.0 || lambda2 > 1.0))
                retval = false;
        }
    }
    if(retval){
        p_intersect = calc_intersect_point(l1, l2);
    }
    return std::pair<bool, point>(retval, p_intersect);
}

/*
void TreatLeftEndpoint(point& E, sweep_line& sl){
    std::size_t segE = E.lineID;
    sl.segment_queue.push_back(segE);

    std::size_t segA ;
}

void TreatRightEndpoint(point& E, sweep_line& sw){
    return;
}

void TreatIntersection(point& E, sweep_line& sw){
    return;
}


void sort_xvals(){
    return;
}*/
