#include <iostream>

int char2int(char oneDigitnum) {
    return (int)oneDigitnum - (int)'0'; 
}

std::string int2string(int num) {
    std::string result = "";
    while(num>0) {
        int lastDigit = num%10;
    }
}

std::string mul(std::string num1, std::string num2) {
    int n1 = char2int(num1[0]);
    int n2 = char2int(num2[0]);
    int mul = n1*n2;
    std::string product = int2string(mul);
}

void KaratsubaAlgo(std::string num1, std::string num2) {
    if(num1.length() == 1 && num2.length()== 1) {

    }
        return;
}

int main() {
    std::string num1 = "2718281828459045235360287471352662497757247093699959574966967627";
    std::string num2 = "3141592653589793238462643383279502884197169399375105820974944592";
    std::cout<<num1.length();
}