#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

// Cấu trúc để lưu thông tin 1 cạnh: u, v, chi phí d
struct Edge {
    int u, v, d;
    bool operator<(const Edge& other) const {
        return d < other.d; // Sắp xếp theo chi phí tăng dần
    }
};

// Cấu trúc Union-Find 
class DSU {
    vector<int> parent, rank;

public:
    DSU(int n) {
        parent.resize(n + 1); // Đánh số từ 1 đến n
        rank.resize(n + 1, 0);
        for (int i = 1; i <= n; ++i)
            parent[i] = i;
    }

    int find(int u) {
        if (u != parent[u])
            parent[u] = find(parent[u]); // Path compression
        return parent[u];
    }

    bool unite(int u, int v) {
        int pu = find(u);
        int pv = find(v);
        if (pu == pv) return false; // u và v đã thuộc cùng 1 nhóm

        // Union by rank
        if (rank[pu] < rank[pv])
            parent[pu] = pv;
        else {
            parent[pv] = pu;
            if (rank[pu] == rank[pv])
                rank[pu]++;
        }
        return true;
    }
};

int main() {
    ifstream fin("connection.txt");
    ofstream fout("connection.out");

    int n, m;
    fin >> n >> m; // Số đỉnh, số cạnh

    vector<Edge> edges;

    // Đọc danh sách cạnh
    for (int i = 0; i < m; ++i) {
        int u, v, d;
        fin >> u >> v >> d;
        edges.push_back({u, v, d});
    }

    // Sắp xếp các cạnh theo chi phí tăng dần
    sort(edges.begin(), edges.end());

    DSU dsu(n);
    int total_cost = 0;
    vector<Edge> mst_edges;

    // Kruskal's algorithm
    for (const Edge& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            total_cost += e.d;
            mst_edges.push_back(e);
        }
    }

    fout << total_cost << "\n";
    for (const Edge& e : mst_edges) {
        fout << e.u << " " << e.v << " " << e.d << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}