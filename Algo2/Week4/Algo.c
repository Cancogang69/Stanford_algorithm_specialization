#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef long long llong;

void printError(char *error) {
    printf("%s\n", error);
    abort();
}

void* allocate(size_t size, size_t tSize) {
    void *array = malloc(tSize*size);
    if(!array) printError("Cannot allocating memory!");

    return array;
}

int char2int(char digit) {
    return (int) digit - (int) '0';
}

llong str2long(const char *source, int *index) {
    llong num = 0;
    int j=0, sign = 1 ;
    if(source[*index]=='-') {
        sign = -1;
        (*index)++;
    }

    while((int) source[*index]>=48 && (int) source[*index]<=57)
        num = num*10 + char2int(source[(*index)++]);
    (*index)++;
    return num*sign;
}

llong * readFile(const char *inputFile, const int nV) {
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
    
    llong *list = allocate(nV, sizeof *list);
    for(int i=0, j=0; i<newSize; j++) {
        llong num = str2long(source, &i);
        list[j] = num;
    }
    free(source);
    return list;
}

void swap(void *n1, void *n2, size_t tSize) {
    void *temp = allocate(1, tSize);
    memmove(temp, n1, tSize);
    memmove(n1, n2, tSize);
    memmove(n2, temp, tSize);
    free(temp);
}

int partition(llong *list, int left, int right) {
    llong pivot = list[left];
    int i=left;
    swap(&list[i], &list[right], sizeof *list);
    for(int j=left; j<right; j++)
        if(list[j]<pivot)
            swap(&list[i++], &list[j], sizeof *list);
    swap(&list[i], &list[right], sizeof *list);
    return i;
}

void QuickSort(llong *list, int left, int right) {
    if(left>=right) return;

    int p = partition(list, left, right);
    QuickSort(list, left, p-1);
    QuickSort(list, p+1, right);
}

int main() {
    const char *inputFile = "data_file.txt";
    const int n = 1000000;
    llong *list = readFile(inputFile, n);
    QuickSort(list, 0, n-1);

    //use 2 pointer to cut down the sum range
    int left = 0, right = n-1,
        zeroPos = 10000, count = 0;
    bool flag[20001] = {false};
    while(left<=right) {
        llong sum = list[left] + list[right];
        if(sum<-(zeroPos))
            left++;
        else if(sum>zeroPos)
            right--;
        else {
            while(sum<=zeroPos) {
                if(!flag[sum+zeroPos]) {
                    flag[sum+zeroPos] = true;
                    count++;
                }
                sum = list[++left] + list[right];
            }
        }
    }
    printf("%d", count);
}