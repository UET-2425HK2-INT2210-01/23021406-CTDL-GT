#include <iostream>
using namespace std;

// Hàm đệ quy đảo ngược số
void daoNguocSo(int n, int& rev) {
    if (n == 0)
        return;
    rev = rev * 10 + n % 10;
    daoNguocSo(n / 10, rev);
}

int main() {
    int n;
    cout << "Nhap so nguyen duong: ";
    cin >> n;

    int soGoc = n;
    if (n < 0)
        n = -n; // Xử lý số âm nếu muốn

    int rev = 0;
    daoNguocSo(n, rev);

    if (soGoc < 0)
        rev = -rev; // Giữ dấu âm

    cout << "So dao nguoc la: " << rev << endl;
    return 0;
}
