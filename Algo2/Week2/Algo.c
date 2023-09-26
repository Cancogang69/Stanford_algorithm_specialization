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

Node * readFile(const char *inputFile, int *nV) {
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
    for(int i=0; i<newSize; i++)
        if(source[i]=='\n')
            (*nV)++;
    
    Node *graph = allocate((*nV), sizeof *graph);
    for(int i=0; i<(*nV); i++) {
        graph[i].nE=0;
        graph[i].adjencyList = allocate((*nV), sizeof(Edge));
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
    return graph;
}

void swap(Edge *e1, Edge *e2) {
    Edge temp = *e1;
    *e1 = *e2;
    *e2 = temp;
}

void addHeap(Edge *heap, int *heapSize, Edge edge) {
    int temp = (*heapSize)++,
        parent = (temp-1)/2;
    heap[temp] = edge;
    while(parent!=temp && parent>=0 &&
         heap[parent].weight>heap[temp].weight) {
        swap(&heap[parent], &heap[temp]);
        temp = parent;
        parent = (temp-1)/2;
    }
}

//this function only remove the first element from heap
void pop(Edge *heap, int *heapSize) {
    swap(&heap[0], &heap[--(*heapSize)]);
    int parent = 0, left = 1;
    while(left<(*heapSize)) {
        int right = left+1 >= (*heapSize) ? left : left+1;
        int minPos = heap[right].weight>heap[left].weight ? left : right;
        if(heap[parent].weight<heap[minPos].weight)
            return;
        swap(&heap[parent], &heap[minPos]);
        parent = minPos;
        left = parent*2 + 1;
    }   
}

int * dijkstraAlgo(Node *graph, int src, int nV) {
    //this is a min heap
    Edge *heap = allocate(10000, sizeof *heap),
        init = {src, src, 0};
    int heapSize = 0,
        *list = allocate(nV, sizeof *list);
    addHeap(heap, &heapSize, init);
    list[src-1] = 0;
    while(nV>0) {
        Edge min = heap[0];
        pop(heap, &heapSize);
        if(graph[min.des-1].adjencyList[0].src==-1) 
            continue;

        nV--;
        list[min.des-1] = min.weight;
        for(int i=0; i<graph[min.des-1].nE; i++) {
        Edge new = graph[min.des-1].adjencyList[i];
        new.weight += list[min.des-1];
        addHeap(heap, &heapSize, new);
        }
        graph[min.des-1].adjencyList[0].src = -1;
    }
    free(heap);
    return list;
}

int main() {
    const char *inputFile = "data_file.txt";
    //inputFile = "test.txt";
    int nV = 0;
    Node *graph = readFile(inputFile, &nV);

    int *disList = dijkstraAlgo(graph, 1, nV);
    int size = 10,
        vertices[] = {7, 37, 59, 82, 99, 115, 133, 165, 188, 197};
    for(int i=0; i<size; i++) 
        printf("%d,", disList[vertices[i]-1]);
}