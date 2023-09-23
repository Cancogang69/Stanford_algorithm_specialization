#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
    int src, des, weight;
} Edge;

typedef struct Node {
    int nE;
    Edge *adjencyList;
} Node;

void printError(char *error) {
    printf("%s\n", error);
    abort();
}

void* allocate(size_t size, size_t tSize) {
    void *array = malloc(tSize*size);
    if(!array) printError("Cannot allocating memory!");

    return array;
}

int str2int(const char *source, int *index) {
    char *str = allocate(100, sizeof *str);
    int j=0;
    while((int) source[*index]>=48 && (int) source[*index]<=57)
        str[j++] = source[(*index)++];
    (*index)++;
    return atoi(str);
}

void readFile(const char *inputFile, Node *graph) {
    FILE *input = fopen(inputFile, "r");
    if(!input) printError("Cannot open input file!");
    //read input file and store it into a buffer
    if(fseek(input, 0L, SEEK_END) != 0) 
        printError("Cannot reach to the end of input file!");
    long buffSize = ftell(input);
    if(buffSize == -1) printError("Cannot read buffer size!");
    char *source = allocate(buffSize, sizeof *source);
    rewind(input);
    size_t newSize = fread(source, sizeof *source, buffSize, input);
    if(ferror(input) != 0) printError("Error reading file!");
    source[newSize] = '\0';
    fclose(input);
    //count for how many vertices are in the graph
    //when a line is a vertex and its neighbor
    int nV = 0;
    for(int i=0; i<newSize; i++)
        if(source[i]=='\n')
            nV++;
    
    graph = allocate(nV, sizeof *graph);
    for(int i=0; i<nV; i++) {
        graph[i].nE=0;
        graph[i].adjencyList = allocate(nV, sizeof(Edge));
    }
    
    for(int i=0; i<newSize; i++) {
        int vertex = str2int(source, &i),
            j = 0, nE = graph[vertex-1].nE;
        while(source[i]!='\n') {
            int desV = str2int(source, &i);
            int weight = str2int(source, &i);
            Edge e = {vertex, desV, weight};
            graph[vertex-1].adjencyList[nE++] = e;
        }
        graph[vertex-1].nE = nE;
    }
    free(source);
}

int main() {
    Node *graph = NULL;
    const char *inputFile = "data_file.txt";
    readFile(inputFile, graph);
}