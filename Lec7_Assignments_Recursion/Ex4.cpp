#include<iostream>

using namespace std;

int power();

int x, n;
int val = 0;

int power(int x, int n) {
    if(n == 0) {
        return val = 1;
    } 
    else if(n == 1) {
        return val = x;
    }
    else {
        return val = x * x * (n - 1);
    }
}

int main() {
    cin >> n >> x;
    power(x, n);

    cout << val;

    return 0;
}