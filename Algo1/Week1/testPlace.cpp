#include <iostream>

using namespace std;

int main() {
    string num = "12345";
    int size = num.length();
    string a = num.substr(0, size/2);
    string b = num.substr(size/2);
    cout<<a<<" "<<b<<"\n";
}