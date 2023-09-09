#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

typedef struct Edge {
    int src;
    int des;
} Edge;

typedef struct Graph {
    int nV, nE;
    Edge *listEdge;
} Graph;

void readData(std::string inputFile, Graph& graph) {
    std::ifstream input(inputFile);
    if(!input) {
        std::cerr<<"Cannot open input file!\n";
        exit(-1);
    }

    graph.nV = 0;
    graph.nE = 0;
    std::string line;
    while(std::getline(input, line)) {
        std::istringstream ss(line);
        int vertex;
        ss>>vertex;
        graph.nV++;
        for(int num; ss>>num; )
            if(num>vertex) graph.nE++;     
    }   
    input.clear();
    input.seekg(0);
    
    graph.listEdge = new Edge[graph.nE];
    for(int vertex, p=0; std::getline(input, line); ) {
        std::stringstream ss(line);
        ss>>vertex;
        for(int num; ss>>num; )
            if(num>vertex)
                graph.listEdge[p++] = {vertex, num};
    }   
    input.close();
}

int random(int start, int end) {
    return rand() % end + start;
}

int findParent(int *parentList, int vertex) {
    while(parentList[vertex-1] != vertex)
        vertex = parentList[vertex-1];
    return vertex;
}

int countMinimumCut(const Graph& graph) {
    int nV = graph.nV;
    int *tempParent = new int[nV];
    for(int i=0; i<graph.nV; i++)
        tempParent[i] = i+1; 
    while(nV>2) {
        int pos = random(0, graph.nE-1);
        Edge edge = graph.listEdge[pos];
        int srcParent = findParent(tempParent, edge.src),
            desParent = findParent(tempParent, edge.des);
        if(srcParent == desParent)
            continue;

        nV--;
        tempParent[desParent-1] = srcParent;
    }

    int minCut = 0;
    for(int i=0; i<graph.nE; i++) {
        Edge edge = graph.listEdge[i];
        if(findParent(tempParent, edge.src) != findParent(tempParent, edge.des))
            minCut++;
    }
    return minCut;
}

int main() {
    srand(time(NULL));
    std::string inputFile = "data_file.txt";
    //inputFile = "test_data.txt";
    Graph graph;
    readData(inputFile, graph);
    
    int min = graph.nE;
    for(int i=0; i<200; i++) {
        int edge = countMinimumCut(graph);
        min = min > edge ? edge : min;
    }
    std::cout<<min<<"\n";
}