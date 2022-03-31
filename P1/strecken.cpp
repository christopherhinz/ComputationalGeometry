


#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define MAX 20

void read_dat(std::vector<float>& v){
    std::ifstream file;
    file.open("strecken/s_1000_1.dat");
    float data;
    for(int i = 0; i < MAX; ++i){
        file >> data;
        v.push_back(data);
        //std::cout << data << std::endl;
    }
    file.close();
}

int main()
{
    std::vector<float> vec;
    read_dat(vec);
    std::cout << "size: " << vec.size() << "\n";
    for(int i = 0; i < MAX-1; ++i)
        std::cout << vec[i] << " "; 
    std::cout << "\n";

        
    return 0;
}
