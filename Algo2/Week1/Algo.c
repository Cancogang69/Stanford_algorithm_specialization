#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int size;
    int used;
    int *list;
} node;

bool isEmpty(node list);
void push(node *list, int value);
int top(node stack);
void pop(node *stack);
void* init1DArray(size_t typeSize, size_t arraySize);
node* initGraph(int graphSize, const int initListSize);
node initStack();
void addVertex(node *graph, const int sourceV, const int destinationV);
void readGraph(node *graph, node *revGraph, const char fileName[], size_t *graphSize);
void DFS(node *graph, int v, int *fPointer, bool *isExplored, 
        bool *isCaptured, int *fArray, int *leaderArray);
void freeGraph(node *graph, size_t graphSize);

int main() {
    char input[] = "data_file.txt";
    const int initListSize = 10;
    size_t graphSize = 876000;
    node *graph = initGraph(graphSize, initListSize);
    node *revGraph = initGraph(graphSize, initListSize);
    readGraph(graph, revGraph, input, &graphSize);

    bool *isExplored = init1DArray(sizeof(bool), graphSize);
    bool *isCaptured = init1DArray(sizeof(bool), graphSize);
    //first loop in kosaraju
    for(int i=0; i<graphSize; i++) {
        isCaptured[i]=false;
        isExplored[i]=false;
    }
    int *fArray = init1DArray(sizeof(int), graphSize);
    int fPointer = graphSize-1;
    for(int i=graphSize-1; i>=0; i--) {
        if(isExplored[i]==false) {
            DFS(revGraph, i, &fPointer, isExplored, isCaptured, fArray, NULL);
        }
    }

    freeGraph(revGraph, graphSize);

    int *leaderArray = init1DArray(sizeof(int), graphSize);
    for(int i=0; i<graphSize; i++) {
        isCaptured[i]=false;
        isExplored[i]=false;
        leaderArray[i] = 0;
    }
    //second loop in kosaraju
    for(int i=0; i<graphSize; i++) {
        int node = fArray[i];
        if(isExplored[node]==false) {
            DFS(graph, node, &fPointer, isExplored, isCaptured, NULL, leaderArray);
        }
    }

    freeGraph(graph, graphSize);
    free(isCaptured);
    free(isExplored);

    int top5[5] = {0};
    for(int i=0; i<graphSize; i++) {
        int scc = leaderArray[i];
        for(int j=0; j<5; j++)
            if(top5[j]<scc) {
                int temp = top5[j];
                top5[j] = scc;
                scc = temp;
            }
    }

    free(leaderArray);

    for(int i=0; i<5; i++)
        printf("%d ", top5[i]);
}

void push(node *list, int value) {
    if(list->used == list->size) {
        list->size *= 2;
        int *temp = realloc(list->list, sizeof(int) * list->size);
        if(temp == NULL) {
            printf("Cannot reallocating memory for vertex's list!");
            exit(0);
        }
        list->list = temp;
    }

    list->list[list->used++] = value;
}

bool isEmpty(node stack) {
    return stack.used==0 ? true : false;
}

int top(node stack) {
    if(isEmpty(stack)) {
        printf("stack is empty!");
        return -1;
    }
    return stack.list[stack.used-1]; 
}

void pop(node *stack) { 
    if(isEmpty(*stack)) 
        exit(1);
    stack->used--;
}

void* init1DArray(size_t typeSize, size_t arraySize) {
    void *array = malloc(typeSize * arraySize);
    if(array==NULL) {
        printf("Cannot allocating memory!");
        exit(1);
    }
    return array;
}

node* initGraph(int graphSize, const int initListSize) {
    node *graph = init1DArray(sizeof *graph, graphSize);

    for(int i=0; i< graphSize; i++) {
        graph[i].list = init1DArray(sizeof(int), initListSize);
        graph[i].used = 0;
        graph[i].size = initListSize;
    }
    return graph;
}

node initStack() {
    node stack;
    stack.size = 100;
    stack.used = 0;
    stack.list = init1DArray(sizeof(int), stack.size);
    return stack;
}

void addVertex(node *graph, const int sourceV, const int destinationV) {
    push(&graph[sourceV], destinationV);
}

// convert edge list to adjacency list
void readGraph(node *graph, node *revGraph, const char fileName[], size_t *graphSize) {
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

    //update No. of vertices
    (*graphSize) = largestV;
    fclose(inputFile);
}

void DFS(node *graph, int v, int *fPointer, bool *isExplored, 
        bool *isCaptured, int *fArray, int *leaderArray) 
{  
    node stack = initStack();
    push(&stack, v);
    while(!isEmpty(stack)) {
        int s = top(stack);

        if(isExplored[s]) {
            pop(&stack);
            if(isCaptured[s]) {
                continue;
            }
            isCaptured[s] = true;
            if(fArray!=NULL)
                fArray[(*fPointer)--] = s;
            continue;
        }

        isExplored[s] = true;
        if(leaderArray!=NULL) 
            leaderArray[v]++;
        node *vertex = &graph[s];
        for(int i=0; i<vertex->used; i++)
            if(!isExplored[vertex->list[i]])
                push(&stack, vertex->list[i]);
    }  
    free(stack.list);
}

void freeGraph(node *graph, size_t graphSize) {
    for(int i=0; i<graphSize; i++)
        free(graph[i].list);
    free(graph);
}
