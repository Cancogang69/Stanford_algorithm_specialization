#include <iostream>
#include <fstream>

void readData(std::string inputFile, int array[10000]) {
    std::ifstream input(inputFile);
    if(!input) {
        std::cerr<<"Cannot open input file!\n";
        exit(-1);
    }

    for(int i=0, num; input>>num; i++)
        array[i] = num;
    
    input.close();
}

int main() {
    std::string inputFile = "data_file.txt";
    int array[10000];
    readData(inputFile, array);
    for(int i=0; i<10; i++)
        std::cout<<array[i]<<" ";
}