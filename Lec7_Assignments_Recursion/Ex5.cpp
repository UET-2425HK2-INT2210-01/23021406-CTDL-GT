#include<iostream>
using namespace std;

int countNum();

int n;

int countNum(int n) {
    if(n < 10) {
        return 1;
    }
    else {
        return 1 + countNum(n / 10);
    }
}

int main() {
    cin >> n;

    if(n < 0) {
        n = -n;
    }
    
    cout << countNum(n);
    
    return 0;
}