
#include "rapidXML/rapidxml_utils.hpp"
#include <iostream>
#include <string>
#include <vector>

#include "../P1/p1_lib.h"

// --------------------------------------------------------------------
// Klassen zum Speichern der relevanten Informationen aus der XML-Datei 
// --------------------------------------------------------------------

struct koord{
    float x, y;
};

struct stadt{
    std::string name;
    koord ko;
};

struct bundesland{
    std::string name;
    unsigned int parts;
    std::vector<std::vector<koord>> polygon_vec;
    bundesland(char* n, char* path_content) : name{n}, parts{0}{
        split_content(path_content);
    }
    void split_content(char* path_content){
        std::string str{path_content};
        std::vector<koord> koord_vec;
        koord tmp_koord;
        std::string delimiter = "\n";
        std::size_t pos = 0;
        std::string token;
        float start_x, start_y;
        while ((pos = str.find(delimiter)) != std::string::npos) {
            token = str.substr(0, pos);
            if(token[0] == 'M'){
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
                polygon_vec.push_back(koord_vec);
                ++parts;
            }
            str.erase(0, pos + delimiter.length());
        }
    }
};
std::ostream& operator<<(std::ostream& os, bundesland b){
    os << "Bundesland: " << b.name << "\n";
    for(int i = 0; i < b.polygon_vec.size(); ++i){
        os << i+1 << ". Polygonnetz hat " << b.polygon_vec[i].size() << " Punkte\n";
        for(auto elem: b.polygon_vec[i]){
            os << "\t" << elem.x << " " << elem.y << "\n";
        }
    }
    return os;
}


// -----------------------------------------------------------------------
// Funktionen zum Testen ob Stadt (Punkt) in Bundesland (mind. 1 Polygon)
// -----------------------------------------------------------------------

// ccw: wird glaube ich gebraucht, ist klein also hab ichs reinkopiert -> dann vermischen sich die Praktika nicht
double ccw(koord p, koord q, koord r){
    double res = (p.x*q.y - p.y*q.x)+ (q.x*r.y - q.y*r.x) + (p.y*r.x  - p.x*r.y);
    return res;
}

bool punkt_in_polygon(koord ko, std::vector<koord> vec_koords){
    //
    // HIER MUSS NUN DER PUNKT IN POLYGON TEST IMPLEMENTIERT WERDEN
    //
    return true;
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