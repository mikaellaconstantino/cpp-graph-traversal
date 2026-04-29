#include <iostream> 
#include <vector> 

// Union-Find data structure
class UnionFind {
private:
    std::vector<int> parent; // Vector to store parent ng node
public:
    UnionFind(int n) { // Iinitialize yung data structure
        parent.resize(n); // Resize the parent vector to have n elements
        for (int i = 0; i < n; i++) { // lloop sa lahat ng nodes
            parent[i] = i; // Initially, each node is its own parent (root)
        }
    }
    int find(int x) { // Find the root of the set containing node x
        if (parent[x] != x) // If x is not the root
            parent[x] = find(parent[x]); // Path compression: set x's parent to its grandparent
        return parent[x]; // Return the root of the set containing x
    }
    void unionSets(int x, int y) { // Union the sets containing x and y
        int xroot = find(x); // Find the root of x's set
        int yroot = find(y); // Find the root of y's set
        if (xroot != yroot) // If x and y are in different sets
            parent[xroot] = yroot; // Make the root of x's set a child of the root of y's set
    }
};

int main() {
    int n, m; // n: number of users, m: number of friendships
    std::cin >> n >> m; // Read n and m from input
    UnionFind uf(n); // Create a UnionFind data structure with n nodes
    for (int i = 0; i < m; i++) { // Loop through all friendships
        int u, v; // u and v yung users na friends
        std::cin >> u >> v; // Read the users from input
        uf.unionSets(u - 1, v - 1); // Union the sets containing users u and v (adjust for 0-based indexing)
    }
    std::vector<bool> visited(n, false); // Vector to mark visited nodes
    int numCliques = 0; // Counter for the number of cliques
    for (int i = 0; i < n; i++) { // Lloop sa lahat ng nodes
        if (!visited[uf.find(i)]) { // If the root of this node's set di pa navvisit
            visited[uf.find(i)] = true; // Mark root as visited
            numCliques++; // tas iincrement clique counter
        }
    }
    std::cout << numCliques << std::endl; // Output the number of cliques
    return 0; // Exit the program
}
