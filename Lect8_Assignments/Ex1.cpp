#include<iostream>
#include<vector>

using namespace std;

// Hàm hoán đổi
void swap(int &a, int &b) {
    int tmp = a; // gán giá trị của cho tmp
    a = b; // gán giá trị của b cho a
    b = tmp; // gán giá trị của tmp tức là của a trước hoán đổi cho b
}

// Hàm phân vùng
int partition(vector<int> &arr, int low, int high) {
    int pivot = arr[high]; // chọn giá trị cuối mảng làm pivot
    int i = low - 1; // vị trí của phần tử nhỏ hơn pivot

    for(int j = low; j < high; j++) {// duyệt từ phần tử đầu đến phần tử trước pivot
        if(arr[j] < pivot) { // nếu phần tử nhỏ hơn pivot
            i++; // tăng vị trí của phần tử nhỏ hơn pivot
            swap(arr[i], arr[j]); // hoán đổi vị trí của phần tử nhỏ hơn với phần tử hiện tại
        }
    }
    swap(arr[i + 1], arr[high]); // đưa pivot về đúng vị trí của nó
    return i + 1; // trả về vị trí của pivot
}

// Hàm quicksort
void quickSort(vector<int> &arr, int low, int high) {
    if(low < high) { // điểm neo cho đệ quy (có ít nhất 2 phần tử mới xử lý)
        int pi = partition(arr, low, high); // gọi đệ quy để phân vùng mảng rồi trả về vị trí của pivot
        quickSort(arr, low, pi - 1); // gọi đệ quy cho nửa bên trái của pivot
        quickSort(arr, pi + 1, high); // gọi đệ quy cho nửa bên phải của pivot
    }
}

int main() {
    int n;
    cin >> n;

    vector<int> arr(n);
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    quickSort(arr, 0, n - 1);

    for(int i = 0; i < n; i++) {
        cout << arr[i];
        if(i < n - 1){
            cout << " ";
        }
    }
    cout << endl;

    return 0;
}