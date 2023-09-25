#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void printError(const char *error) {
    printf("%s\n", error);
    abort();
}

void* allocate(size_t size, size_t tSize) {
    void *array = malloc(tSize*size);
    if(!array) printError("Cannot allocating memory!");

    return array;
}

int* readFile(const char *inputFile, const int n) {
    FILE *input = fopen(inputFile, "r");
    if(!input) printError("Cannot open input file!");

    int *list = allocate(n, sizeof *list);
    for(int i=0; i<n; i++)
        fscanf(input, "%d", &list[i]);
    fclose(input);
    return list;
}

bool compare(int val1, int val2, bool isMinHeap) {
    if(isMinHeap)
        return val1<val2;
    else
        return val1>val2;
}

void swap(int *val1, int *val2) {
    int temp = *val1;
    *val1 = *val2;
    *val2 = temp;
}

void addHeap(int *heap, int *heapSize, int value, bool isMinHeap) {
    int temp = (*heapSize)++,
        parent = (temp-1)/2;
    heap[temp] = value;
    while(parent!=temp && parent>=0 &&
         heap[parent]>heap[temp]==isMinHeap) {
        swap(&heap[parent], &heap[temp]);
        temp = parent;
        parent = (temp-1)/2;
    }
}

//this function only remove the first element from heap
void pop(int *heap, int *heapSize, bool isMinHeap) {
    swap(&heap[0], &heap[--(*heapSize)]);
    int parent = 0, left = 1;
    while(left<(*heapSize)) {
        int right = left+1 >= (*heapSize) ? left : left+1;
        int swapPos = (heap[right]>heap[left])==isMinHeap ? left : right;
        if(heap[parent]<heap[swapPos]==isMinHeap)
            return;
        swap(&heap[parent], &heap[swapPos]);
        parent = swapPos;
        left = parent*2 + 1;
    }   
}

int main() {
    const char *inputFile = "data_file.txt";
    int n = 10000;
    int *list = readFile(inputFile, n);
    //highHeap is a min heap
    //lowHeap is a max heap
    int *highHeap = allocate((n/2)+1, sizeof *highHeap),
        *lowHeap = allocate((n/2)+1, sizeof *lowHeap),
        hSize=0, lSize=0, sum = list[0];
    addHeap(lowHeap, &lSize, list[0], false);
    for(int i=1; i<n; i++) {
        if(list[i]<lowHeap[0])
            addHeap(lowHeap, &lSize, list[i], false);
        else
            addHeap(highHeap, &hSize, list[i], true);
        if(lSize-hSize==2) {
            int value = lowHeap[0];
            pop(lowHeap, &lSize, false);
            addHeap(highHeap, &hSize, value, true);
        } else if(hSize-lSize==2) {
            int value = highHeap[0];
            pop(highHeap, &hSize, true);
            addHeap(lowHeap, &lSize, value, false);
        }

        if(hSize<=lSize) sum += lowHeap[0];
        else sum += highHeap[0];
    }
    
    printf("%d\n", sum%n);
}