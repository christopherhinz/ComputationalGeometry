/*
Struktur von std::vector<bundesland>:
bundesland{
    name  = "Berlin"
    parts = 1
    std::vector<std::vector<koord>> polygon_vec = [ [ [0,0] , [1,1]   ,... ],      ...            ]
                                                    |koord1|, |koord2|,...
                                                    |  ein Polygon   |   weitere Polygone ...
}
*/

#include "p2_lib.h"

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
    //for(int i = 0; i < bundeslaender.size(); i++) std::cout << bundeslaender[i] << "\n";


    // Städte die zu testen sind auslesen und stadt Instanz erstellen
    auto path_node2 = g_node->next_sibling();
    std::vector<stadt> staedte;
    stadt st;
    while(path_node2){
        st.name = path_node2->first_attribute("id")->value();
        st.ko.x = std::stof(path_node2->first_attribute("sodipodi:cx")->value());
        st.ko.y = std::stof(path_node2->first_attribute("sodipodi:cy")->value());
        staedte.push_back(st);
        path_node2 = path_node2->next_sibling();
    }
    //for(auto st: staedte) std::cout << st.name << ": " << st.ko.x << " " << st.ko.y << "\n";


    for(auto st: staedte){
        for(auto bund: bundeslaender){
            stadt_in_bundesland(st, bund);
        }
    }

    return 0;
}


// Compilieren und Ausgabe in Datei umleiten
// clang++ -std=c++14 bundesland.cpp && ./a.out > koords_to_test.txt

// Normal Compilieren
// clang++ -std=c++14 bundesland.cpp && ./a.out