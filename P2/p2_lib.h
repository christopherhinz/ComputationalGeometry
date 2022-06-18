#define NDEBUG
#include "rapidXML/rapidxml_utils.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

// --------------------------------------------------------------------
// Klassen zum Speichern der relevanten Informationen aus der XML-Datei
// --------------------------------------------------------------------

struct koord{
    double x, y;
};

struct stadt{
    std::string name;
    koord ko;
};


// -----------------------------------------------------------------------
// Funktionen zum Testen ob Stadt (Punkt) in Bundesland (mind. 1 Polygon)
// -----------------------------------------------------------------------

// ccw: wird glaube ich gebraucht, ist klein also hab ichs reinkopiert -> dann vermischen sich die Praktika nicht
double ccw(koord p, koord q, koord r){
    double res = (p.x*q.y - p.y*q.x)+ (q.x*r.y - q.y*r.x) + (p.y*r.x  - p.x*r.y);
    return res;
}


bool punkt_in_polygon(koord p_requested, std::vector<koord> cornerpoints){
    double ccw_res;

    // Keine negativen Koordinaten
    koord p_outside = {-1, -1};

    // Eckpunkt soll nicht auf der Geraden von p_outside und p_requested liegen
    int i = 0;
    while(ccw(p_outside, p_requested, cornerpoints[i]) == 0) ++i;

    ccw_res = ccw(p_outside, p_requested, cornerpoints[i]);

    int intersec_counter = 0;
    // sgn function for ccw_res
    int lr = (ccw_res > 0) - (ccw_res < 0);

    for(auto iter = cornerpoints.begin()+i+1; iter != cornerpoints.end(); ++iter){
        ccw_res = ccw(p_outside, p_requested, *iter);
        int lr_new = (ccw_res > 0) - (ccw_res < 0);
        volatile int absolute = std::abs(lr_new - lr);
        if(std::abs(lr_new - lr) == 2){
            lr = lr_new;
            if(ccw(*(iter-1), *iter, p_outside)*ccw(*(iter-1), *iter, p_requested) <= 0){
                ++intersec_counter;
            }
        }
    }
    return (intersec_counter % 2 == 0) ? false : true;
}

struct bundesland{
    std::string name;
    unsigned int parts;
    std::vector<std::vector<koord>> polygon_vec;
    double area;
    stadt capital;

    bundesland(char* n, char* path_content) : name{n}, parts{0}, area{0}{
        split_content(path_content);
        calc_area();
    }

    // Funktion zur Flaechenberechnung einzelner Polygone
    double polygon_area(std::vector<koord> polygon){
        double local_area_part = 0;

        for(auto iter = polygon.begin(); iter != polygon.end(); ++iter) {
            if(iter == polygon.begin()){
                // Previous element is at the end of the vector
                local_area_part += (*iter).y * (polygon.back().x - (*(iter+1)).x);
            } else if(std::next(iter) == polygon.end()){
                // Next element is at the beginning of the vector
                local_area_part += (*iter).y * ((*(iter-1)).x - polygon.front().x);
            } else {
                // Dreiecksformel: sum(y * (prev_x - next_x));
                local_area_part += (*iter).y * ((*(iter-1)).x - (*(iter+1)).x);
            }
        }
        // Flaechen Unabhaengig von der Orientierung aufaddieren
        if(local_area_part < 0) local_area_part *= -1;
        return local_area_part/2;
    }

    void calc_area(){
        for(int i = 0; i < polygon_vec.size(); ++i){
            bool flag;
            for(int j = 0; j < polygon_vec.size(); ++j){
                if(i != j){
                    // Liegt i in j, dann von der Gesamtflaeche abziehen
                    if(punkt_in_polygon(polygon_vec[i][0], polygon_vec[j])){
                        flag = true;
                    }
                }
            }
            if(flag == true){
                area -= polygon_area(polygon_vec[i]);
            } else {
                area += polygon_area(polygon_vec[i]);
            }

        }
        // Geschaetzter Skalierungsfaktor (Anhand von Bayern)
        // area *= 1.175341649;
    }

    void split_content(char* path_content){
        std::string str{path_content};
        std::vector<koord> koord_vec;
        koord tmp_koord;
        std::string delimiter = "\n";
        std::size_t pos = 0;
        std::string token;
        double start_x, start_y;
        while ((pos = str.find(delimiter)) != std::string::npos) {
            token = str.substr(0, pos);
            if(token[0] == 'M'){
                start_x = std::stof(token.substr(1, token.find(',')-1));
                start_y = std::stof(token.substr(token.find(',')+1, token.length()));
                tmp_koord.x = start_x;
                tmp_koord.y = start_y;
                koord_vec.push_back(koord(tmp_koord));
            }
            if(token[0] == 'L'){
                start_x = std::stof(token.substr(1, token.find(',')-1));
                start_y = std::stof(token.substr(token.find(',')+1, token.length()));
                tmp_koord.x = start_x;
                tmp_koord.y = start_y;
                koord_vec.push_back(koord(tmp_koord));
            }
            else if(token[0] =='l'){
                start_x += std::stof(token.substr(1, token.find(',')-1));
                start_y += std::stof(token.substr(token.find(',')+1, token.length()));
                tmp_koord.x = start_x;
                tmp_koord.y = start_y;
                koord_vec.push_back(koord(tmp_koord));
            }
            else if(token[0] == 'z'){
                // First and last coordinate are the same in the svg file
                if((koord_vec.front().x == koord_vec.back().x) &&
                   (koord_vec.front().y == koord_vec.back().y)){
                       koord_vec.pop_back();
                }
                polygon_vec.push_back(koord_vec);
                koord_vec.clear();
                ++parts;
            }
            str.erase(0, pos + delimiter.length());
        }

    }
};
std::ostream& operator<<(std::ostream& os, bundesland b){
    os << "Bundesland: " << b.name << "\n";
    os << "Anzahl der Polygone: " << b.parts << "\n";
    os << "Gesamtflaeche: " << b.area << "\n";
    os << "Hauptstadt: " << b.capital.name << "\n";

    // for(int i = 0; i < b.polygon_vec.size(); ++i){
    //     os << i+1 << ". Polygonnetz hat " << b.polygon_vec[i].size() << " Punkte\n";
    //     for(auto elem: b.polygon_vec[i]){
    //         os << "\t" << elem.x << " " << elem.y << "\n";
    //     }
    // }
    return os;
}

bool stadt_in_bundesland(stadt st, bundesland bund){
    // alle Polygone des gegebenen Bundeslandes durchlaufen
    bool res = false;
    for(auto polygon: bund.polygon_vec){
        if(punkt_in_polygon(st.ko, polygon)){
            res = true;
        }
    }
    return res;
}
