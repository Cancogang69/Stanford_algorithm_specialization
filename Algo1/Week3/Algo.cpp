#include <iostream>
#include <fstream>

#define size 10000

void readData(std::string inputFile, int array[size]) {
    std::ifstream input(inputFile);
    if(!input) {
        std::cerr<<"Cannot open input file!\n";
        exit(-1);
    }

    for(int i=0, num; input>>num; i++)
        array[i] = num;
    
    input.close();
}

int findMedian(const int arr[size], int pPos[3]) {
    int left = arr[pPos[0]],
        right = arr[pPos[1]],
        median = arr[pPos[2]],
        bigger = left > right ? left : right,
        smaller = left == bigger ? right : left;
    median = bigger > median ? median : bigger;
    median = smaller < median ? median : smaller;
    for(int i=0; i<2; i++)
        if(median==arr[pPos[i]])
            pPos[2] = pPos[i];
    return median;
}

void swap(int& num1, int& num2) {
    int temp = num1;
    num1 = num2;
    num2 = temp;
}

int Partition(int array[size], int left, int right, int method) {
    //pivot-choosing part
    int pPos[] = {left, right, (left+right)/2};
    int median = method == 2 ? findMedian(array, pPos) : 0;
    int pivots[] = {array[pPos[0]], array[pPos[1]], median};
    int pivot = pivots[method];
    swap(array[pPos[0]], array[pPos[method]]);

    //sorting part
    int i = left + 1;
    for(int j = left + 1; j<=right; j++) 
        if(array[j] < pivot)
            swap(array[j], array[i++]);
    swap(array[pPos[0]], array[--i]);
    return i;
}

void QuickSort(int array[size], int left, int right, int method, int &count) {
    if(left>=right) return;

    count += right-left;
    int pPos = Partition(array, left, right, method);
    QuickSort(array, left, pPos-1, method, count);
    QuickSort(array, pPos+1, right, method, count);
}

void copyArray(const int array[size], int desArray[size]) {
    for(int i=0; i<size; i++)
        desArray[i] = array[i];
}

int main() {
    std::string inputFile = "data_file.txt";
    int array[size];
    readData(inputFile, array);

    for(int i=0; i<3; i++) {
        int tempArray[size];
        copyArray(array, tempArray);
        int count = 0;
        QuickSort(tempArray, 0, size-1, i, count);
        std::cout<<count<<"\n";
    }
}