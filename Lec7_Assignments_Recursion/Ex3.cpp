#include<iostream>

using namespace std;

int fibo();

int n;
int fn = 0;

int fibo(int n) {
    if(n == 0) {
        return 0;
    }
    else if(n == 1) {
        return 1;
    }
    else {
        return  fibo(n - 1) + fibo(n -2);
    }
}

int main() {
    cin >> n;
    cout << fibo(n);;
}
