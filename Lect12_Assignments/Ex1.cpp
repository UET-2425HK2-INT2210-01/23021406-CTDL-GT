#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

// Hàm đọc dữ liệu từ file
void read_input(const string& filename, int& n, int& m, vector<vector<int>>& graph, vector<int>& in_degree) {
    ifstream fin(filename); // Mở file input
    fin >> n >> m; // Đọc số lượng công việc và số yêu cầu

    // Khởi tạo danh sách kề và mảng độ vào (in-degree)
    graph.assign(n + 1, vector<int>());
    in_degree.assign(n + 1, 0);

    // Đọc các cặp u v và xây dựng đồ thị
    for (int i = 0; i < m; ++i) {
        int u, v;
        fin >> u >> v;
        graph[u].push_back(v); // u → v
        in_degree[v]++;        // v có thêm 1 công việc phải làm trước
    }

    fin.close(); // Đóng file
}

// Thuật toán sắp xếp topo (Topological Sort) bằng BFS (Kahn's Algorithm)
vector<int> topological_sort(int n, const vector<vector<int>>& graph, vector<int> in_degree) {
    queue<int> q;        // Hàng đợi cho các node có in-degree = 0
    vector<int> result;  // Kết quả thứ tự công việc

    // Đưa các công việc không bị phụ thuộc vào queue
    for (int i = 1; i <= n; ++i) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    // Duyệt theo thứ tự topo
    while (!q.empty()) {
        int u = q.front(); // Lấy công việc đầu hàng đợi
        q.pop();
        result.push_back(u); // Thêm vào kết quả

        // Giảm độ vào của các công việc phụ thuộc vào u
        for (int v : graph[u]) {
            in_degree[v]--;
            // Nếu độ vào bằng 0, thêm vào hàng đợi
            if (in_degree[v] == 0) {
                q.push(v);
            }
        }
    }

    return result; // Trả về danh sách công việc theo thứ tự hợp lệ
}

// Hàm ghi kết quả ra file
void write_output(const string& filename, const vector<int>& order) {
    ofstream fout(filename); // Mở file output

    // Ghi từng công việc ra file
    for (int x : order) {
        fout << x << " ";
    }
    fout << endl;

    fout.close(); // Đóng file
}

int main() {
    int n, m; // Số lượng công việc và số yêu cầu
    vector<vector<int>> graph;  // Danh sách kề của đồ thị
    vector<int> in_degree;      // Mảng đếm số lượng công việc phải làm trước mỗi công việc

    // Đọc dữ liệu
    read_input("jobs.txt", n, m, graph, in_degree);

    // Thực hiện sắp xếp topo
    vector<int> order = topological_sort(n, graph, in_degree);

    // Ghi ra file kết quả
    write_output("jobs.out", order);

    return 0;
}