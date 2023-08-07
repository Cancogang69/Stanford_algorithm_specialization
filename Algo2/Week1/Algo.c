#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void initMatrix(int (*matrix)[30], const size_t size){
    for(int i=0; i<size; i++)
        for(int j=0; j<20; j++)
            matrix[i][j] = 0;
}

void addVertex(int (*graph)[30], const int sourceV, const int destinationV) {
    for(int i=0; i<20; i++)
        if(graph[sourceV][i]==0) {
            graph[sourceV][i]=destinationV;
            break;
        }
}

void readGraph(int (*graph)[30], int (*revGraph)[30], const char fileName[]) {
    FILE *inputFile = fopen(fileName, "r");
    if(inputFile==NULL) {
        printf("Cannot read the input file!");
        exit(0);
    }

    while(!feof(inputFile)){
        int sourceV, destinationV;
        fscanf(inputFile, "%d %d", &sourceV, &destinationV);
        if(sourceV==destinationV)
            continue;
        addVertex(graph, sourceV, destinationV);
        addVertex(revGraph, destinationV, sourceV);
    }

    fclose(inputFile);
}

void printGraph(int (*graph)[30], int nRows) {
    for(int i=0; i<nRows; i++) {
        for(int j=0; j<30; j++)
            printf("%d ", graph[i][j]);
        printf("\n");
    }
}

int main() {
    char input[] = "data_file.txt";
    const size_t rows = 876000;
    int (*graph)[30] = malloc(sizeof *graph * rows);
    int (*revGraph)[30] = malloc(sizeof *revGraph * rows);
    if(graph == NULL || revGraph == NULL) {
        printf("Cannot allocating memory!");
        exit(1);
        free(graph);
        free(revGraph);
    }

    ReadGraph(graph, revGraph, input);
    printGraph(graph, 20);
    printGraph(revGraph, 20);
    
    free(graph);
    free(revGraph);
    
}