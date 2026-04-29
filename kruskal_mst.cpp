#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <climits>
using namespace std;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

int findParent(vector<int>& parent, int u) {
    if (parent[u] == -1) return u;
    return parent[u] = findParent(parent, parent[u]);
}

void unionSet(vector<int>& parent, vector<int>& rank, int u, int v) {
    u = findParent(parent, u);
    v = findParent(parent, v);
    if (rank[u] < rank[v]) {
        parent[u] = v;
    } else if (rank[u] > rank[v]) {
        parent[v] = u;
    } else {
        parent[v] = u;
        rank[u]++;
    }
}

int minCostConnectAreas(int n, vector<tiii>& edges, vector<pii>& mandatory) {
    vector<int> parent(n, -1), rank(n, 0);
    int totalCost = 0;

    sort(edges.begin(), edges.end());

    for (auto& [u, v] : mandatory) {
        if (findParent(parent, u) != findParent(parent, v)) {
            int minEdgeIndex = -1;
            int minEdgeWeight = INT_MAX;
            for (size_t i = 0; i < edges.size(); i++) {
                int w, x, y;
                tie(w, x, y) = edges[i];
                if ((x == u && y == v) || (x == v && y == u)) {
                    if (w < minEdgeWeight) {
                        minEdgeWeight = w;
                        minEdgeIndex = i;
                    }
                }
            }
            if (minEdgeIndex != -1) {
                totalCost += minEdgeWeight;
                unionSet(parent, rank, u, v);
            }
        }
    }

    for (auto& edge : edges) {
        int w, u, v;
        tie(w, u, v) = edge;
        if (findParent(parent, u) != findParent(parent, v)) {
            totalCost += w;
            unionSet(parent, rank, u, v);
        }
    }

    int root = findParent(parent, 0);
    for (int i = 1; i < n; i++) {
        if (findParent(parent, i) != root) {
            return -1;
        }
    }
    return totalCost;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<tiii> edges;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.emplace_back(w, u - 1, v - 1);
    }
    int k;
    cin >> k;
    vector<pii> mandatory;
    for (int i = 0; i < k; i++) {
        int u, v;
        cin >> u >> v;
        mandatory.emplace_back(u - 1, v - 1);
    }
    int minCost = minCostConnectAreas(n, edges, mandatory);
    cout << minCost << endl;
    return 0;
}
