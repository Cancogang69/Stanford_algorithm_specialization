#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct vertex {
    int size;
    int used;
    int *list;
} vertex;

void* init1DArray(size_t typeSize, size_t arraySize) {
    void *array = malloc(typeSize * arraySize);
    if(array==NULL) {
        printf("Cannot allocating memory!");
        exit(1);
    }
    return array;
}

vertex* initGraph(int graphSize, const int initListSize) {
    vertex *graph = init1DArray(sizeof *graph, graphSize);

    for(int i=0; i< graphSize; i++) {
        graph[i].list = init1DArray(sizeof(int), initListSize);
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
            printf("Cannot reallocating memory for vertex's list!");
            exit(0);
        }
        v->list = temp;
    }

    v->list[v->used++] = destinationV;
}

// convert edge list to adjacency list
void readGraph(vertex *graph, vertex *revGraph, const char fileName[], size_t *graphSize) {
    FILE *inputFile = fopen(fileName, "r");
    if(inputFile==NULL) {
        printf("Cannot read the input file!");
        exit(1);
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

    *graphSize = largestV;
}

void printGraph(vertex *graph, int nRows) {
    for(int i=0; i<nRows; i++) {
        int n = graph[i].used;
        printf("\nvertex %d, %d : ", i+1, n);
        for(int j=0; j<n; j++)
            printf("%d ", graph[i].list[j]);
    }
}

void DFS(vertex *graph, int v, const int leaderV, int *fTime, 
        bool *isExplored, int *fArray, int *leaderArray, int *fP) 
{
    isExplored[v] = true;
    if(leaderV!=-1) 
        leaderArray[leaderV]++;
    vertex *node = &graph[v];
    for(int i=0; i<node->used; i++)
        if(isExplored[node->list[i]]==false)
            DFS(graph, i, leaderV, fTime, isExplored, fArray, leaderArray, fP);
    
    (*fTime)++;
    fArray[(*fP)++] = (*fTime);
}

int main() {
    char input[] = "data_file.txt";
    const int initListSize = 10;
    size_t graphSize = 876000;
    vertex *graph = initGraph(graphSize, initListSize);
    vertex *revGraph = initGraph(graphSize, initListSize);
    readGraph(graph, revGraph, input, &graphSize);

    bool *isExplored = init1DArray(sizeof(bool), graphSize);
    for(int i=0; i<graphSize; i++)
        isExplored[i]=false;
    int *fArray = init1DArray(sizeof(int), graphSize);
    int fTime = -1;
    int fPointer = 0;
    for(int i=graphSize-1; i>=0; i--) {
        if(isExplored[i]==false) {
            DFS(graph, i, -1, &fTime, isExplored, fArray, NULL, &fPointer);
        }
    }
    FILE *output = fopen("output.txt", "w");
    for(int i=0; i<graphSize; i++) 
        fprintf(output, "%d %d\n", i+1, fArray[i]);
    fclose(output);
}