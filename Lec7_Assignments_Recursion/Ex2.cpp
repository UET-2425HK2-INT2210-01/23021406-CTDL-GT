#include<iostream>

using namespace std;

int factorial();

int n;
int total = 0;


int factorial(int n) {
    if(n == 1) {
        return 1;
    }
    else {
        return total = n * factorial(n - 1);
    }
}

int main() {
    cin >> n;
    factorial(n);
    cout << total;
}