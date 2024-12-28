#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

class NetworkGraph {
private:
    int V; // Number of vertices (devices)
    vector<vector<pair<int, int>>> adj; // Adjacency list with weights

public:
    NetworkGraph(int vertices) : V(vertices) {
        adj.resize(V);
    }

    // Add connection between devices
    void addConnection(int from, int to, int bandwidth) {
        adj[from].push_back({to, bandwidth});
        adj[to].push_back({from, bandwidth});
    }

    // Find shortest path using Dijkstra's algorithm
    vector<int> findOptimalPath(int source) {
        vector<int> dist(V, numeric_limits<int>::max());
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        dist[source] = 0;
        pq.push({0, source});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (auto& neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist;
    }

    // Calculate network reliability (number of alternative paths)
    int calculateReliability() {
        int alternativePaths = 0;
        for (int i = 0; i < V; i++) {
            alternativePaths += adj[i].size();
        }
        return alternativePaths / 2; // Divide by 2 as each edge is counted twice
    }
};

int main() {
    // Create a network with 5 devices
    NetworkGraph network(5);

    // Add connections with bandwidth values
    network.addConnection(0, 1, 10);
    network.addConnection(0, 2, 5);
    network.addConnection(1, 2, 2);
    network.addConnection(1, 3, 1);
    network.addConnection(2, 3, 8);
    network.addConnection(2, 4, 4);
    network.addConnection(3, 4, 7);

    // Find optimal paths from device 0 to all other devices
    vector<int> shortestPaths = network.findOptimalPath(0);

    cout << "Network Analysis Results:\n";
    cout << "Optimal paths from Device 0 to all other devices:\n";
    for (int i = 0; i < shortestPaths.size(); i++) {
        cout << "To Device " << i << ": " << shortestPaths[i] << " units\n";
    }

    cout << "\nNetwork Reliability Score: " << network.calculateReliability() 
         << " connections\n";

    return 0;
}