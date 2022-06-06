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

struct line{
    point p1;
    point p2;
};

struct sweep_line{
    point current_event;
    std::vector<std::size_t> segment_queue;
    std::vector<point> event_queue;
    void sort_event_queue(){
        std::sort(event_queue.begin(), event_queue.end(), [](point& p1, point& p2){return p1.x == p2.x ? p1.y > p2.y : p1.x > p2.x;});
    }
    void init_segment_queue(){
        segment_queue.push_back(event_queue.back().lineID);
    }
};

void read_dat(std::string filename, std::vector<point>& target){
    point pb, pe;
    std::size_t countID = 0;
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
    return retval;
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
