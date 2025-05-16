#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int BFS(int n, vector<vector<int>>& adj, int start, int end) {
    vector<int> dist(n + 1, -1); // tạo mảng dist với n + 1 phần tử, khởi tạo giá trị của các phần tử trong mảng là -1 đại diện cho đỉnh chưa thăm hoặc khoảng cách chưa xác định
    queue<int> q; // tạo hàng đợi q

    dist[start] = 0; // gắn khoảng cách từ đỉnh start đến chính nó là 0
    q.push(start); // thêm đỉnh start vào hàng đợi

    while(!q.empty()) { // khi hàng đợi không rỗng
        int u = q.front(); // lấy đỉnh đầu tiên trong hàng đợi
        q.pop(); // khi đã gắn giá trị cho đỉnh đầu tiên cho u thì xóa khỏi hàng đợi

        for(int v : adj[u]) { // duyệt tất cả cá đỉnh kể 
            if(dist[v] == - 1) { 
                dist[v] = dist[u] + 1; // gán khoảng cách từ đỉnh u đến đỉnh v là khoảng cách từ u đến v cộng 1
                q.push(v); // thêm đỉnh v vào hàng đợi
            }
        }
    }

    return dist[end]; // trả về khoảng cách từ đỉnh start đến đỉnh end
}

int main() {
    int n, m, X, Y;
    cin >> n >> m >> X >> Y;

    vector<vector<int>> adj(n + 1);

    for(int i = 0; i < m; i++) {
        int u ,v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    int result = BFS(n, adj, X, Y);
    cout << result;

    return 0;
}