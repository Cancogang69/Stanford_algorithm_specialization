#include <iostream>
#include <math.h>

int char2int(char num) {
    return (int)num - (int)'0'; 
}

char int2char(int num) {
    return (char) (num + (int)'0');
}

std::string int2string(int num) {
    std::string revResult = "";
    while(num>0) {
        int lastDigit = num%10;
        revResult.push_back(int2char(lastDigit));
        num/=10;
    }
    std::string result = "";
    int revLength = revResult.length();
    for(int i=0; i<revLength; i++) {
        result.push_back(revResult[revLength-i-1]);
    }
    return result;
}

std::string mul(std::string num1, std::string num2) {
    int n1 = char2int(num1[0]);
    int n2 = char2int(num2[0]);
    int product = n1*n2;
    if(product==0)
        return "0";
    return int2string(product);
}

void balancing(std::string& num1, std::string& num2) {
    int n1 = num1.length(),
        n2 = num2.length();
    if(n1 == n2) 
        return;
    std::string newStr (abs(n1-n2), '0');

    if(n1>n2)
        num2 = newStr + num2;
    else
        num1 = newStr + num1;
}

std::string add(std::string num1, std::string num2) {
    balancing(num1, num2);
    std::string result = "0" + num1;
    int remainder = 0;
    for(int i=num1.length()-1; i>=0; i--) {
        int e1 = char2int(num1[i]);
        int e2 = char2int(num2[i]);
        int sum = e1 + e2 + remainder;
        result[i+1] = int2char(sum%10);
        remainder = sum/10;
    }
    if(remainder!=0)
        result[0] = int2char(remainder);
    else
        result.erase(0, 1);
    return result;
}

void removeHeadZeros(std::string& num) {
    int n = 0;
    int i=0;
    while(num[i]=='0') {
        n++;
        i++;
    }
    num.erase(0, n);
}

// this function just works for this case because 
// str3 is always greater than sum of str2 and str1
std::string subtract(std::string num1, std::string num2) {
    balancing(num1, num2);
    std::string result = num1;
    int remainder = 0;
    for(int i=num1.length()-1; i>=0; i--) {
        int e1 = char2int(num1[i]);
        int e2 = char2int(num2[i]) + remainder;
        if(e1<e2) {
            e1 += 10;
            remainder = 1;
        } 
        int sub = e1 - e2;
        result[i] = int2char(sub);
    }
    if(result[0] == '0')
        result.erase(0, 1);
    return result;
}

void seperateInto2String(const std::string& num, std::string result[2]) {
    int mid = num.length()/2;
    result[0] = num.substr(0, mid);
    result[1] = num.substr(mid);
}

std::string KaratsubaAlgo(std::string num1, std::string num2) {
    if(num1.length() == 1 && num2.length()== 1) {
        return mul(num1, num2);
    }
    std::string ab[2], cd[2];
    balancing(num1, num2);
    seperateInto2String(num1, ab);
    seperateInto2String(num2, cd);
    std::string str1 = KaratsubaAlgo(ab[0], cd[0]);
    std::string str2 = KaratsubaAlgo(ab[1], cd[1]);
    std::string str3 = KaratsubaAlgo(add(ab[0], ab[1]), add(cd[0], cd[1]));
    str3 = subtract(str3, str1);
    str3 = subtract(str3, str2);
    std::string tenExp (num1.length(), '0');
    std::string tenExpn (num1.length()/2, '0');
    str1 += tenExp;
    str3 += tenExpn;
    std::string result = add(str1, str3);
    result = add(result, str2);
    removeHeadZeros(result);
    return result;
}

int main() {
    std::string num1 = "2718281828459045235360287471352662497757247093699959574966967627";
    std::string num2 = "3141592653589793238462643383279502884197169399375105820974944592";
    std::string num3 = "1234";
    std::string num4 = "5678";
    std::cout<<KaratsubaAlgo(num3, num4)<<"\n";
}