#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <time.h>

#define graphSize 200

void readData(std::string inputFile, std::vector<int> graph[graphSize]) {
    std::ifstream input(inputFile);
    if(!input) {
        std::cerr<<"Cannot open input file!\n";
        exit(-1);
    }

    std::string line;
    while(std::getline(input, line)) {
        std::vector<int> nums;
        std::stringstream ss(line);
        int vertex;
        ss>>vertex;
        for(int num; ss>>num; )
            graph[vertex-1].push_back(num);
    }

    input.close();
}

int randomlyChoose(std::vector<int> array) {
    srand(time(NULL));
    return array[rand() % array.size()];
}

int main() {
    std::string inputFile = "data_file.txt";
    std::vector<int> graph[graphSize];
    readData(inputFile, graph);
    std::vector<int> array = {1, 2, 3, 4, 7, 5, 6, 9};
    std::cout<<"randomly choose a num in array: "<<randomlyChoose(array)<<"\n";
        
}