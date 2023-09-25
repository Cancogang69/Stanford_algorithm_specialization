#include <stdio.h>
#include <stdlib.h>

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

int main() {
    const char *inputFile = "data_file.txt";
    int n = 10000;
    int *list = readFile(inputFile, n);
    for(int i=9990; i<n; i++)
        printf("%d ", list[i]);
}