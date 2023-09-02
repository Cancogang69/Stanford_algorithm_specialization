#include <iostream>
#include <fstream>
#include <vector>

void readData(std::string inputFile, std::vector<int>& array) {
    std::ifstream input(inputFile);

    if(!input) {
        std::cerr << "Can't open input file!\n";
        exit(-1);
    }

    for(int i=0, num; input>>num; i++)
        array.push_back(num);

    input.close();
}

unsigned long SortingandCountInver(std::vector<int>& array, 
    std::vector<int> first, std::vector<int> second) {
    
    unsigned long count = 0;
    int firstP = 0, secondP = 0;
    while(firstP<first.size() && secondP<second.size()) {
        if(first[firstP] > second[secondP]) {
            array.push_back(second[secondP++]);
            count += first.size() - firstP;
        }
        else
            array.push_back(first[firstP++]);
    }

    while(firstP<first.size())
        array.push_back(first[firstP++]);
    
    while(secondP<second.size())
        array.push_back(second[secondP++]);

    return count;
}

void split(std::vector<int>& array, 
    std::vector<int>& first, std::vector<int>& second) {

    int size = array.size();
    for(int i=0; i<size/2; i++)
        first.push_back(array[i]);
    for(int i=size/2; i<size; i++)
        second.push_back(array[i]);

    array.clear();
}

unsigned long countInversion(std::vector<int>& array) {
    if(array.size() == 1) return 0;

    std::vector<int> firstHalf, secondHalf;
    split(array, firstHalf, secondHalf);
    unsigned long inver1 = countInversion(firstHalf),
        inver2 = countInversion(secondHalf),
        inver3 = SortingandCountInver(array, firstHalf, secondHalf);
    return inver1 + inver2 + inver3;
}

int main() {
    std::string inputFile = "data_file.txt";
    std::vector<int> array;
    readData(inputFile, array);
    std::cout<<countInversion(array)<<"\n";
}