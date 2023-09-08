#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

typedef struct Edge {
    int src;
    int des;
} Edge;

typedef struct Graph {
    std::vector<int> vParent;
    std::vector<Edge> listEdge;
} Graph;

void readData(std::string inputFile, Graph& graph) {
    std::ifstream input(inputFile);
    if(!input) {
        std::cerr<<"Cannot open input file!\n";
        exit(-1);
    }
    
    std::string line;
    while(std::getline(input, line)) {
        std::stringstream ss(line);
        int vertex;
        ss>>vertex;
        graph.vParent.push_back(vertex);
        for(int num; ss>>num; )
            if(num>vertex)
                graph.listEdge.push_back({vertex, num});
    }   
    input.close();
}

void swap(Edge& edge1, Edge& edge2) {
    Edge temp = edge1;
    edge1 = edge2;
    edge2 = temp;
}

int random(int start, int end) {
    return rand() % end + start;
}

int findParent(Graph graph, int vertex) {
    while(graph.vParent[vertex-1] != vertex)
        vertex = graph.vParent[vertex-1];
    return vertex;
}

int countMinimumCut(const Graph& graph) {
    Graph temp = graph;
    int nV = temp.vParent.size(),
        pointer = temp.listEdge.size() - 1;
    while(nV>2) {
        int pos = random(0, pointer);
        Edge edge = temp.listEdge[pos];
        int srcParent = findParent(temp, edge.src),
            desParent = findParent(temp, edge.des);
        //remove the randomly chosen edge from edgeList
        swap(temp.listEdge[pos], temp.listEdge[pointer--]);
        if(srcParent == desParent)
            continue;

        nV--;
        temp.vParent[desParent-1] = srcParent;
    }

    int minCut = 0;
    for(int i=0; i<=pointer; i++) {
        Edge edge = temp.listEdge[i];
        if(findParent(temp, edge.src) != findParent(temp, edge.des))
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
    int min = graph.vParent.size();
    for(int i=0; i<200; i++) {
        int edge = countMinimumCut(graph);
        min = min > edge ? edge : min;
    }
    std::cout<<min<<"\n";
}