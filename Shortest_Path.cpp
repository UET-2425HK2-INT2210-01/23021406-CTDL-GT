#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

const int INF = 1000000000; 

struct Edge { // tạo struct để lưu thông tin một cạnh
    int from;
    int to;
    int dirty;
};

int n, m, s, e; 
/* n là sl thành phố (1 -> n)
   m là sl đường đi tới các thành phố
   s là điểm xuất phát
   e là điểm đích 
*/
vector<Edge> edges; //danh sách các cạnh
vector<int> dist; // tạo mảng để lưu khoảng cách từ s đến các đỉnh
vector<int> trace; // tạo mảng để lưu đường đã đi

void bellmanFord(int start) {
    dist.assign(n + 1, INF); //gắn các giá trị ban đầu của mảng dist
    trace.assign(n + 1, -1); // gắn -1 cho các giá trị trong mảng trace vì chưa có đỉnh trước đó
    dist[start] = 0; // khoảng cách giữa vị trí hiện tại với thành hiện tại là 0

    for(int i = 1; i <= n - 1; i++) {
        for(Edge edge:edges) {
            int u = edge.from;
            int v = edge.to;
            int d = edge.dirty;

            if(dist[u] != INF && dist[u] + d < dist[v]) { // đã tìm được đường ngắn hơn
                dist[v] = dist[u] + d; // cập nhập đường đi ngắn hơn
                trace[v] = u; //chọn đi từ u tới v
            }
        }
    }
}

vector<int> reconstructPath(int end) { // Hàm truy ngược đường đi ngắn nhất từ s đến end
    vector<int> path; // tạo mảng lưu đường đi
    while(end != -1) { //duyệt ngược từ end về s
        path.push_back(end); //lưu các đỉnh vào path
        end = trace[end]; // lùi về đỉnh trước đó
    }
    reverse(path.begin(), path.end()); // đảo thứ tự 
    return path;
}

vector<vector<int>> allDist; // tạo ma trận khoảng cách

void floydWarshall() {
    allDist.assign(n + 1, vector<int>(n + 1, INF));

    for(int i = 1; i <= n; i++) {
        allDist[i][i] = 0;
    }

    for(Edge edge:edges) {
        int u = edge.from;
        int v = edge.to;
        int d = edge.dirty;

        if(d < allDist[u][v]) {
            allDist[u][v] = d;
        }
    }

    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(allDist[i][k] < INF && allDist[k][j] < INF) {
                    allDist[i][j] = min(allDist[i][j], allDist[i][k] + allDist[k][j]);
                }
            }
        }
    }
}

int main() {
    ifstream fin("dirty.txt");
    ofstream fout("dirty.out");

    // Đọc dữ liệu đầu vào
    fin >> n >> m >> s >> e;
    for (int i = 0; i < m; i++) {
        int u, v, d;
        fin >> u >> v >> d;
        edges.push_back({u, v, d});
    }

    // Phần a: Tìm đường đi ngắn nhất từ s đến e
    bellmanFord(s);

    if (dist[e] == INF) {
        fout << "INF\n";
        fout << "No path\n";
    } else {
        fout << dist[e] << "\n";
        vector<int> path = reconstructPath(e);
        for (int i = 0; i < path.size(); i++) {
            fout << path[i];
            if (i != path.size() - 1) fout << " ";
        }
        fout << "\n";
    }

    // Phần b: Tính đường đi ngắn nhất giữa mọi cặp đỉnh
    floydWarshall(); 

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (allDist[i][j] == INF)
                fout << "INF";
            else
                fout << allDist[i][j];

            if (j != n) fout << " ";
        }
        fout << "\n";
    }

    return 0;
}