#include<iostream>

using namespace std;

int Sum();

int sum = 0;
int n;

int Sum(int n) {
    if(n == 1) {
        return 1;
    }
    else {
        return sum = n + Sum(n - 1);
    }
}

int main() {
    cin >> n;
    Sum(n);
    cout << sum;

    return 0;
}