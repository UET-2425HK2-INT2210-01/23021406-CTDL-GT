#include<iostream>
#include<vector>

using namespace std;

int main() {
    int n, X;
    cin >> n >> X;

    vector<int> w(n), v(n);
    for(int i = 0; i < n; i++) {
        cin >> w[i] >> v[i];
    }

    vector<int> dp(X + 1, 0); // Khởi tạo mảng dp với kích thước X+1 và giá trị mặc định là 0

    for(int i = 0; i < n; i++) {
        for(int j = X; j >= w[i]; j--) { // Duyệt từ X đến w[i] để tránh việc sử dụng lại phần tử
            int val = dp[j - w[i]] + v[i]; // Tính giá trị mới nếu chọn phần tử i
            if(val > dp[j]) { // Nếu giá trị mới lớn hơn giá trị hiện tại
                dp[j] = val; // Cập nhật giá trị
            }
        }
    }

    cout << dp[X] << endl; // In ra giá trị lớn nhất có thể đạt được với trọng lượng tối đa X

    return 0;
}