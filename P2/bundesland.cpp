
#include "rapidXML/rapidxml_utils.hpp"
#include <iostream>
#include <string>
#include <vector>


struct koord{
    float x, y;
};

struct stadt{
    std::string name;
    float x, y;
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

int main() {
    rapidxml::file<> xmlFile("DeutschlandMitStaedten.svg"); // Default template is char
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    auto svg_node = doc.first_node();
    auto g_node = svg_node->first_node();
    auto path_node = g_node->first_node();

    // Bundesländer auslesen und bundesland Instanz erstellen
    std::vector<bundesland> bundeslaender;
    while(path_node){
        bundeslaender.push_back(bundesland(path_node->first_attribute()->value(), path_node->last_attribute()->value()));
        path_node = path_node->next_sibling();
    }
    for(int i = 0; i < bundeslaender.size(); i++)
        std::cout << bundeslaender[i] << "\n";


    // Städte die zu testen sind auslesen und stadt Instanz erstellen
    auto path_node2 = g_node->next_sibling();
    std::vector<stadt> staedte;
    stadt st;
    while(path_node2){
        st.name = path_node2->first_attribute("id")->value();
        st.x = std::stof(path_node2->first_attribute("sodipodi:cx")->value());
        st.y = std::stof(path_node2->first_attribute("sodipodi:cy")->value());
        staedte.push_back(st);
        path_node2 = path_node2->next_sibling();
    }
    //for(auto st: staedte){
    //    std::cout << st.name << ": " << st.x << " " << st.y << "\n";
    //}

    return 0;
}


// Compilieren und Ausgabe in Datei schreiben
// clang++ -std=c++14 bundesland.cpp && ./a.out > koords_to_test.txt

// Normal Compilieren
// clang++ -std=c++14 bundesland.cpp && ./a.out