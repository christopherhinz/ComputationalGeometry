#include <svgpp/svgpp.hpp>

void read_dat(char* filename, std::vector<line>& target){
    line temp;
    std::ifstream file;
    file.open(filename);
    double k1, k2, k3, k4;
    if(!file.is_open()){
        std::cout << "Could not open file\n";
    }
    while(file >> k1 >> k2 >> k3 >> k4){
        temp.p1.x = k1;
        temp.p1.y = k2;
        temp.p2.x = k3;
        temp.p2.y = k4;
        target.push_back(temp);
    }
    file.close();
}

int main(){



    return 0;
}
