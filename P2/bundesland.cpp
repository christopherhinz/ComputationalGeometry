
#include "rapidXML/rapidxml_utils.hpp"
#include <iostream>

// https://www.setnode.com/blog/quick-notes-on-how-to-use-rapidxml/
// http://rapidxml.sourceforge.net/manual.html#classrapidxml_1_1xml__node

void print_node(rapidxml::xml_node<>* node){
    std::cout << node->name() << " ";
    //std::cout << node->first_attribute()->name() << " ";
    std::cout << node->last_attribute()->name() << " ";
    std::cout << node->last_attribute()->value() << "\n";
}



int main() {
    rapidxml::file<> xmlFile("DeutschlandMitStaedten.svg"); // Default template is char
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());


    auto svg_node = doc.first_node();
    //print_node(svg_node);

    auto g_node = svg_node->first_node();
    //print_node(g_node);
        
    auto path1_node = g_node->first_node();
    print_node(path1_node);

    auto path2_node = g_node->next_sibling();
    print_node(path2_node);

    std::cout << "Name of my first node is: " << doc.first_node()->first_node()->first_node()->name() << "\n";
    rapidxml::xml_node<> *node = doc.first_node("svg");
    rapidxml::xml_node<> *next = node->first_node("path");

    // path von Bremen einlesen!


    //for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()){
    //    std::cout << "Node foobar has attribute " << attr->name() << " ";
    //    std::cout << "with value " << attr->value() << "\n";
    //}
    return 0;
}
