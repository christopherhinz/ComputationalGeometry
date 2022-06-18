#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

enum point_type { BEG = 0, END = 1, SEC = 2};

////////////////////////////////////////////
// POINT
////////////////////////////////////////////

struct point{
    double x;
    double y;
    point_type pt;
    long long lineID = -1;  // -1 = invalid value = uninitialized
    long long line1 = -1;   
    long long line2 = -1;
};
inline bool operator==(point& p1, point& p2){
    return p1.x == p2.x && p1.y == p2.y && p1.pt == p2.pt && p1.lineID == p2.lineID;
}
inline bool operator!=(point& p1, point& p2){
    return !(p1==p2);
}
inline std::ostream& operator<<(std::ostream& os, point& p){
    os << "pt=" << p.pt << ", lineID=" << p.lineID << ", koords=(" << p.x << "," << p.y << ")";
    return os;
}
inline void swap_points(point& p1, point& p2){
    point p_tmp = {.x = p1.x, .y = p1.y, .pt = p1.pt, .lineID = p1.lineID, .line1 = p1.line1, .line2 = p1.line2};
    p1 = {.x = p2.x, .y = p2.y, .pt = p2.pt, .lineID = p2.lineID, .line1 = p2.line1, .line2 = p2.line2};
    p2 = {.x = p_tmp.x, .y = p_tmp.y, .pt = p_tmp.pt, .lineID = p_tmp.lineID, .line1 = p_tmp.line1, .line2 = p_tmp.line2};
}

inline bool same_koords(point& p1, point& p2){
    return p1.x == p2.x && p1.y == p2.y;
}


////////////////////////////////////////////
// LINE
////////////////////////////////////////////

struct line{
    point p_beg;
    point p_end;
};
inline bool operator==(line& l1, line& l2){
    return l1.p_beg == l2.p_beg && l1.p_end == l2.p_end;
}
inline std::ostream& operator<<(std::ostream& os, line& l){
    os << l.p_beg << " <-> " << l.p_end;
    return os;
}
inline void swap_lines(line& l1, line& l2){
    swap_points(l1.p_beg, l2.p_beg);
    swap_points(l1.p_end, l2.p_end);
}
inline double calc_y_value(double x_current, line& l){
    double y_current = l.p_beg.y + (x_current - l.p_beg.x) / (l.p_end.x - l.p_beg.x) * (l.p_end.y - l.p_beg.y);
    return y_current;
}
inline bool same_line(line& l1, line& l2){
    return l1.p_beg.x == l2.p_beg.x && l1.p_beg.y == l2.p_beg.y && l1.p_end.x == l2.p_end.x && l1.p_end.y == l2.p_end.y;
}


////////////////////////////////////////////
// SWEEP LINE
////////////////////////////////////////////

struct sweep_line{
    point current_event;
    std::vector<line> segment_queue;
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
            std::cout   << "\tlineID" << elem.p_beg.lineID << "\n";
        std::cout << "\n";
    }
    void erase_segment(long long lineID){
        for(long long i = 0; i < segment_queue.size(); ++i){
            if(segment_queue[i].p_beg.lineID == lineID){
                segment_queue.erase(segment_queue.begin()+i);
                break;
            }
        }
    }
};


////////////////////////////////////////////
// HELPER FUNCS
////////////////////////////////////////////

bool point_in_point_list(point& p, std::vector<point>& point_list){
    for(auto& point : point_list){
        //if(point == p)
        if( same_koords(point, p) )
            return true;
    }
    return false;
}

void read_dat(std::string filename, std::vector<point>& target, std::vector<line>& all_lines){
    point p_beg, p_end;
    long long countID = 0;
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
                p_end = { .x = k1, .y = k2, .pt = END, .lineID = countID};
                p_beg = { .x = k3, .y = k4, .pt = BEG, .lineID = countID};
            }
            ++countID;

            all_lines.push_back( line{ .p_beg = p_beg, .p_end = p_end} );

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
    l1.p_beg = _l1.p_beg;
    l1.p_end = {.x = _l1.p_end.x - _l1.p_beg.x, .y = _l1.p_end.y - _l1.p_beg.y};
    l2.p_beg = _l2.p_beg;
    l2.p_end = {.x = _l2.p_end.x - _l2.p_beg.x, .y = _l2.p_end.y - _l2.p_beg.y};
    double lambda2 = (l1.p_beg.y + l2.p_beg.x*l1.p_end.y/l1.p_end.x - l2.p_beg.y - l1.p_beg.x*l1.p_end.y/l1.p_end.x)/(l2.p_end.y - l2.p_end.x*l1.p_end.y/l1.p_end.x);
    point intersect_point = {.x = l2.p_beg.x + lambda2 * l2.p_end.x, .y = l2.p_beg.y + lambda2 * l2.p_end.y, .pt = SEC, .line1 = _l1.p_beg.lineID, .line2 = _l2.p_beg.lineID};
    return intersect_point;
}

std::pair<bool, point> line_intersect_check(line l1, line l2){
    bool retval = false;
    point p_intersect = {.x = 0.0, .y = 0.0};

    double ccw_res1 = ccw(l1.p_beg, l1.p_end, l2.p_beg) * ccw(l1.p_beg, l1.p_end, l2.p_end);
    double ccw_res2 = ccw(l2.p_beg, l2.p_end, l1.p_beg) * ccw(l2.p_beg, l2.p_end, l1.p_end);
    double lambda1, lambda2;
    if(ccw_res1 <= 0.0 && ccw_res2 <= 0.0){
        retval = true;

        if(ccw_res1 == 0.0 && ccw_res2 == 0.0){
            lambda1 = (l2.p_beg.x-l1.p_beg.x)/(l1.p_end.x-l1.p_beg.x);
            lambda2 = (l2.p_end.x-l1.p_beg.x)/(l1.p_end.x-l1.p_beg.x);
            if ((lambda1 < 0.0 || lambda1 > 1.0) && (lambda2 < 0.0 || lambda2 > 1.0))
                retval = false;
        }
    }
    if(retval){
        if(l1.p_beg.y > l2.p_beg.y){
            p_intersect = calc_intersect_point(l1, l2);
        }
        else{
            p_intersect = calc_intersect_point(l2, l1);
        }
    } 
    return std::pair<bool, point>(retval, p_intersect);
}
