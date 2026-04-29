#include <iostream>  
#include <vector>  
#include <queue>  
#include <algorithm>  
#include <climits>  
#include <tuple>  
using namespace std; 

const int MAX_N = 1000;
const int MAX_M = 100000;

class UnionFind {
private:
    vector<int> parent, rank;

public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int findSet(int u) {
        if (parent[u] != u)
            parent[u] = findSet(parent[u]);
        return parent[u];
    }

    bool unionSet(int u, int v) {
        int pu = findSet(u);
        int pv = findSet(v);
        if (pu == pv)
            return false;
        if (rank[pu] > rank[pv])
            parent[pv] = pu;
        else if (rank[pu] < rank[pv])
            parent[pu] = pv;
        else {
            parent[pv] = pu;
            rank[pu]++;
        }
        return true;
    }
};

vector<pair<int, int>> adj[MAX_N];
vector<int> dist(MAX_N, INT_MAX);

void dijkstra(int src, vector<int>& distances, int n) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});
    distances[src] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > distances[u])
            continue;

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (distances[v] > distances[u] + weight) {
                distances[v] = distances[u] + weight;
                pq.push({distances[v], v});
            }
        }
    }
}

int main() {
    int n, k, m;
    cin >> n >> k >> m;

    vector<tuple<int, int, int>> airline_edges;

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        if (u < k && v < k) {
            airline_edges.push_back({w, u, v});
        }
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    sort(airline_edges.rbegin(), airline_edges.rend());

    UnionFind uf(k);
    int airline_profit = 0;
    vector<tuple<int, int, int>> selected_edges;

    for (auto& edge : airline_edges) {
        int w = get<0>(edge), u = get<1>(edge), v = get<2>(edge);
        if (uf.unionSet(u, v)) {
            selected_edges.push_back({u, v, w});
            airline_profit += w;
            if (selected_edges.size() == static_cast<size_t>(k - 1)) break;
        }
    }

    cout << "Airline Profit: " << airline_profit << endl;
    cout << "Flights:" << endl;
    for (auto& edge : selected_edges) {
        int u = get<0>(edge), v = get<1>(edge), w = get<2>(edge);
        cout << u << " " << v << " " << w << endl;
    }

    vector<int> nearest_airport_distance(n, INT_MAX);
    for (int i = 0; i < k; ++i) {
        fill(dist.begin(), dist.end(), INT_MAX);
        dijkstra(i, dist, n);
        for (int j = k; j < n; ++j) {
            nearest_airport_distance[j] = min(nearest_airport_distance[j], dist[j]);
        }
    }

    cout << "Distance of cities from the nearest airport:" << endl;
    for (int i = k; i < n; ++i) {
        cout << i << ": " << nearest_airport_distance[i] << endl;
    }

    return 0;
}
