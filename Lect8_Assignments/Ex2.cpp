#include<iostream>
#include<vector>

using namespace std;

bool isSubsetSum(const vector<int> &A, int n, int X) { //Hàm kiểm tra tập con xem có tổng bằng X cho trước ko 
    vector<vector<bool>> dp(n + 1, vector<bool>(X + 1, false)); // khởi tạo mảng 2 chiều dp với kích thước (n+1) x (X+1) và giá trị mặc định là false
    /* Mảng dp[i][j] sẽ hoạt động như sau:
       dp[i][j] = true nếu có một tập con của A[0..i-1] có tổng bằng j
       dp[i][j] = false nếu không có tập con nào như vậy
    */

    //Tổng bằng 0 luôn có thể được tạo ra bằng cách không chọn bất kỳ phần tử nào
    for(int i = 0; i <= n; i++) {
        dp[i][0] = true;
        // tạo base case cho dp[i][0]
    }

    //Quy hoạch động 
    for(int i = 1; i <= n; i++) {
        for(int sum = 1; sum <= X; sum++) {
            if(A[i - 1] <= sum) { // nếu phần tử hiện tại nhỏ hơn hoặc bằng sum
                /* Có hai lựa chọn:
                   - Không chọn phần tử hiện tại: dp[i - 1][sum]
                   - Chọn phần tử hiện tại: dp[i - 1][sum - A[i - 1]]
                   Chọn một trong hai lựa chọn này để kiểm tra xem có thể tạo ra tổng sum hay không
                */
                dp[i][sum] = dp[i - 1][sum] || dp[i - 1][sum - A[i - 1]]; 
            } else {
                dp[i][sum] = dp[i - 1][sum]; // nếu phần tử hiện tại lớn hơn sum, không thể chọn nó
            }
        }
    }

    return dp[n][X]; // trả về giá trị cuối cùng của dp[n][X]
}

int main() {
    int n, X;
    cin >> n >> X;

    vector<int> A(n);
    for(int i = 0; i < n; i++) {
        cin >> A[i];
    }

    if(isSubsetSum(A, n, X)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}