#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

enum point_type { BEG = 0, END = 1, SEC = 2};


struct point{
    double x;
    double y;
    point_type pt;
    std::size_t lineID = 0;
    std::size_t line1 = 0;
    std::size_t line2 = 0;
};
bool operator==(point& p1, point& p2){
    return p1.x == p2.x && p1.y == p2.y && p1.pt == p2.pt && p1.lineID == p2.lineID;
}
bool operator!=(point& p1, point& p2){
    return !(p1==p2);
}
std::ostream& operator<<(std::ostream& os, point& p){
    os << "pt=" << p.pt << ", lineID=" << p.lineID << ", koords=(" << p.x << "," << p.y << ")";
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

struct segment{
    std::size_t lineID;
    double y_beg;
};
void swap_segments(segment& s1, segment& s2){
    segment s_tmp = {.lineID = s1.lineID, .y_beg = s1.y_beg};
    s1 = {.lineID = s2.lineID, .y_beg = s2.y_beg};
    s2 = {.lineID = s_tmp.lineID, .y_beg = s_tmp.y_beg};
}

struct sweep_line{
    point current_event;
    std::vector<segment> segment_queue;
    std::vector<point> event_queue;
    void sort_event_queue(){
        std::sort(event_queue.begin(), event_queue.end(), [](point& p1, point& p2){return p1.x == p2.x ? p1.y > p2.y : p1.x > p2.x;});
    }
    void print_event_queue(){
        std::cout << "Event queue:\n";
        for(auto& elem : event_queue){
            if(elem.pt == BEG || elem.pt == END)
                std::cout << "\t" << (elem.pt == 0 ? "BEG" : "END") << elem.lineID << ": "<< elem << "\n";
            else
                std::cout << "\tSEC " << elem.line1 << "," << elem.line2 << ": " << elem << "\n";
        }
        std::cout << "\n";
    }
    void print_segment_queue(){
        std::cout << "Segment queue:\n";
        for(auto& elem : segment_queue)
            std::cout   << "\tlineID" << elem.lineID << "\n";
        std::cout << "\n";
    }
    void erase_segment(std::size_t lineID){
        for(std::size_t i = 0; i < segment_queue.size(); ++i){
            if(segment_queue[i].lineID == lineID){
                segment_queue.erase(segment_queue.begin()+i);
                break;
            }
        }
    }
};

void read_dat(std::string filename, std::vector<point>& target){
    point p_beg, p_end;
    std::size_t countID = 1;
    std::ifstream file;
    file.open(filename.c_str());
    double k1, k2, k3, k4;
    if(!file.is_open()){
        std::cout << "Could not open file\n";
    }
    while(file >> k1 >> k2 >> k3 >> k4){
        if(k1 < k3){
            p_beg = { .x = k1, .y = k2, .pt = BEG, .lineID = countID};
            p_end = { .x = k3, .y = k4, .pt = END, .lineID = countID};
        }
        else{
            p_beg = { .x = k1, .y = k2, .pt = END, .lineID = countID};
            p_end = { .x = k3, .y = k4, .pt = BEG, .lineID = countID};
        }
        ++countID;
        target.push_back(p_beg);
        target.push_back(p_end);
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
    point intersect_point = {.x = l2.p1.x + lambda2 * l2.p2.x, .y = l2.p1.y + lambda2 * l2.p2.y, .pt = SEC, .line1 = _l1.p1.lineID, .line2 = _l2.p1.lineID};
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
        if(l1.p1.y > l2.p1.y){
            p_intersect = calc_intersect_point(l1, l2);
            //std::cout << "line1: " << l1 << "\nline2: " << l2 << std::endl << std::endl ;
        }
        else{
            p_intersect = calc_intersect_point(l2, l1);
            //std::cout << "line1: " << l2 << "\nline2: " << l1 << std::endl << std::endl ;
        }
    } 
    return std::pair<bool, point>(retval, p_intersect);
}


bool point_in_point_list(point& p, std::vector<point>& point_list){
    for(auto& point : point_list){
        if(point == p)
            return true;
    }
    return false;
}