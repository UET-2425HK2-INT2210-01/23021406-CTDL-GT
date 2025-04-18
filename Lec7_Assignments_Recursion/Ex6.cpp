#include<iostream>

using namespace std;

int sumNumCount();

int n;
int sum = 0;

void sumNumCount(int n, int& sum) {
    if(n == 0) {
        return ;
    }
    else {
    sum += n % 10;
    sumNumCount(n / 10, sum);
    }
}

int main() {
    cin >> n;
    
    sumNumCount(n, sum);
    cout << sum;

    return 0;
}
