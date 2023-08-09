#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define Size 876000

typedef struct vertex {
    int size;
    int used;
    int *list;
} vertex;

vertex* initGraph(const int initListSize) {
    vertex *graph = malloc(sizeof *graph * Size);
    if(graph==NULL) {
        printf("cannot allocating memory!");
        exit(1);
    }

    for(int i=0; i< Size; i++) {
        graph[i].list = malloc(sizeof(int) * initListSize);
        if(graph[i].list==NULL) {
            printf("cannot allocating memory!");
            exit(1);
        }
        graph[i].used = 0;
        graph[i].size = initListSize;
    }
    return graph;
}

void addVertex(vertex *graph, const int sourceV, const int destinationV) {
    vertex *v = &graph[sourceV];
    if(v->used == v->size) {
        v->size *= 2;
        int *temp = realloc(v->list, sizeof(int) * v->size);
        if(temp == NULL) {
            printf("Cannot reallocating memory!");
            exit(0);
        }
        v->list = temp;
    }

    v->list[v->used++] = destinationV;
}

// convert edge list to adjacency list
void readGraph(vertex *graph, vertex *revGraph, const char fileName[], int *nV) {
    FILE *inputFile = fopen(fileName, "r");
    if(inputFile==NULL) {
        printf("Cannot read the input file!");
        exit(0);
    }

    int largestV = 0;
    while(!feof(inputFile)){
        int sourceV, destinationV;
        fscanf(inputFile, "%d %d", &sourceV, &destinationV);
        if(sourceV==destinationV)
            continue;
        int biggerV = sourceV > destinationV ? sourceV : destinationV;
        largestV = largestV >= biggerV ? largestV : biggerV;
        addVertex(graph, sourceV-1, destinationV-1);
        addVertex(revGraph, destinationV-1, sourceV-1);
    }

    *nV = largestV;
}

void printGraph(vertex *graph, int nRows) {
    for(int i=0; i<nRows; i++) {
        int n = graph[i].used;
        printf("\nvertex %d, %d : ", i+1, n);
        for(int j=0; j<n; j++)
            printf("%d ", graph[i].list[j]);
    }
}

// void KosarajuAlgo(int (*graph)[desV]) {
//     int finishTime = 0;
//     int leaderV = -1;
//     bool isExplored[876000] = {false};
//     for(int i=876000; i>0; i++) {

//     }

// }

int main() {
    char input[] = "data_file.txt";
    const int initListSize = 10;
    vertex *graph = initGraph(initListSize);
    vertex *revGraph = initGraph(initListSize);
    bool flag[Size] = {false};
    int nV;
    readGraph(graph, revGraph, input, &nV);
}