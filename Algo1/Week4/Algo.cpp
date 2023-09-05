#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

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

int main() {
    std::string inputFile = "data_file.txt";
    std::vector<int> graph[graphSize];
    readData(inputFile, graph);
    
        
}