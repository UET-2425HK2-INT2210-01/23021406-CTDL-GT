#include<iostream>
#include<vector>

using namespace std;

const int N = 1000; // đăt kích thước tối đa của mảng
vector<int> adj[N]; // tạo danh sách kề

bool visited[N]; // tạo mảng đánh dấu các đỉnh đã duyệt 

void DFS(int node) {
    visited[node] = true; // đánh dấu cạnh hiện tại đã duyệt
    for(int neighbor : adj[node]) { //sử dụng vòng lặp for-each để gắn giá trị của các đỉnh kề vào biến neighbor
        if(!visited[neighbor]) { // nếu đỉnh kề chưa được duyệt
            DFS(neighbor); // gọi đệ quy để duyệt đỉnh kề
        }
    }
}
/*  adj[1] = {2, 3}
    adj[2] = {1, 4}
    adj[3] = {1}
    adj[4] = {2, 5}
    adj[5] = {4}
    
    visited = {false, false, false, false, false, false}  -> gọi DFS(1)
    dfs(1) visited[2] = false -> gọi DFS(2)
    ├── dfs(2) visited[1] = true && visited[4] = false -> gọi DFS(4)
    │   └── dfs(4) visited[2] = true && visited[5] = false -> gọi DFS(5)
    │       └── dfs(5) visited[4] = true -> kết thúc đệ quy quay về dfs lớn hơn  
    └── dfs(3) visited[2] = true && visited[1] = true -> kết thúc đệ quy quay về dfs lớn hơn
*/

int main() {
    int n, m; // n là các node , m là các đỉnh
    cin >> n >> m;

    for(int i = 0; i < m; i++){
        int x, y; // x là đỉnh đầu , y là đỉnh cuối
        cin >> x >> y; // nhập vào đỉnh đầu và đỉnh cuối
        adj[x].push_back(y); // thêm đỉnh y vào danh sách kề của đỉnh x
        adj[y].push_back(x); // thêm đỉnh x vào danh sách kề của đỉnh y
    }

    int connectedComponents = 0;
    for(int i = 1; i <= n; i++) { // duyệt từ 1 đến n
        if(!visited[i]) { // nếu đỉnh chưa được duyệt
            DFS(i); // gọi hàm DFS để duyệt đỉnh
            connectedComponents++; // tăng số lượng thành phần liên thông
        }
    }

    cout << connectedComponents;

    return 0; 
}