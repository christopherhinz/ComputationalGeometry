
#include "rapidXML/rapidxml_utils.hpp"
#include <iostream>
#include <string>
#include <vector>

// https://www.setnode.com/blog/quick-notes-on-how-to-use-rapidxml/
// http://rapidxml.sourceforge.net/manual.html#classrapidxml_1_1xml__node

void print_node(rapidxml::xml_node<>* node){
    std::cout << node->name() << " ";
    std::cout << node->first_attribute()->name() << " ";
    std::cout << node->first_attribute()->value() << "\n";
}
struct koord{
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
                tmp_koord.x = std::stof(token.substr(1, token.find(',')-1));
                tmp_koord.y = std::stof(token.substr(token.find(',')+1, token.length()));
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
    os << b.name << " verteilt auf " << b.parts << " Fläche(n)";
    for(int i = 0; i < b.polygon_vec.size(); ++i){
        os << i << ". Polygonnetz hat " << b.polygon_vec[i].size() << " Punkte";
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

    std::vector<bundesland> bundeslaender;
    while(path_node){
        if(!std::strcmp(path_node->first_attribute()->value(), (char*)"Berlin")){ // std::strcmp returns 0 in case of equality
            bundeslaender.push_back(bundesland(path_node->first_attribute()->value(), path_node->last_attribute()->value()));
            std::cout << bundeslaender[0] << "\n";
        }
        path_node = path_node->next_sibling();
    }

    return 0;
}
