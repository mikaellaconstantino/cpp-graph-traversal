#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;
typedef pair<int, int> pii;
void dijkstra(vector<vector<pii>> &adj, int start, int target, int n) {
    vector<int> dist(n + 1, INT_MAX);
    vector<int> parent(n + 1, -1);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dist[start] = 0;
    pq.push(make_pair(0, start));
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        for (auto p : adj[u]) {
            int v = p.first;
            int w = p.second;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    if (dist[target] == INT_MAX) {
        cout << "0" << endl;
        return;
    }
    cout << dist[target] << endl;
    vector<int> path;
    int curr = target;
    while (curr != -1) {
        path.push_back(curr);
        curr = parent[curr];
    }
    cout << path[path.size() - 1];
    for (int i = path.size() - 2; i >= 0; i--) {
        cout << " " << path[i];
    }
    cout << endl;
}
int main() {
    int n, e;
    cin >> n >> e;
    vector<vector<pii>> adj(n + 1);
    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back(make_pair(v, w));
    }
    int start, target;
    cin >> start >> target;
    dijkstra(adj, start, target, n);
    return 0;
}
