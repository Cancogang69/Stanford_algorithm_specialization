#include <iostream>
#include <fstream>

#define size 100000

void readData(std::string inputFile, int array[size]) {
    std::ifstream input;
    input.open(inputFile);

    if(!input) {
        std::cerr << "Can't open input file!\n";
        exit(-1);
    }
    
    int num;
    for(int i=0; i<size && input>>num; i++)
        array[i] = num;

    input.close();
}

int main() {
    std::string inputFile = "data_file.txt";
    int array[size];
    readData(inputFile, array);
    for(int i=0; i<20; i++)
        std::cout<<array[i]<<" ";
    
}