#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <limits>
#include <algorithm>

class Graph {
private:
    int V;
    std::vector<std::list<std::pair<int, int>>> adjList;
    std::vector<std::vector<int>> adjMatrix;

public:
    Graph(int vertices) : V(vertices) {
        adjList.resize(V);
        adjMatrix.resize(V, std::vector<int>(V, 0));
    }

    void addEdge(int src, int dest, int weight = 1) {
        adjList[src].push_back({dest, weight});
        adjMatrix[src][dest] = weight;
    }

    void DFS(int start) {
        std::vector<bool> visited(V, false);
        std::stack<int> stack;
        
        stack.push(start);
        while (!stack.empty()) {
            int vertex = stack.top();
            stack.pop();
            
            if (!visited[vertex]) {
                std::cout << vertex << " ";
                visited[vertex] = true;
            }
            
            for (auto& adj : adjList[vertex]) {
                if (!visited[adj.first]) {
                    stack.push(adj.first);
                }
            }
        }
    }

    void BFS(int start) {
        std::vector<bool> visited(V, false);
        std::queue<int> queue;
        
        visited[start] = true;
        queue.push(start);
        
        while (!queue.empty()) {
            int vertex = queue.front();
            std::cout << vertex << " ";
            queue.pop();
            
            for (auto& adj : adjList[vertex]) {
                if (!visited[adj.first]) {
                    visited[adj.first] = true;
                    queue.push(adj.first);
                }
            }
        }
    }

    bool hasCycle() {
        std::vector<bool> visited(V, false);
        std::vector<bool> recStack(V, false);
        
        for (int i = 0; i < V; i++) {
            if (hasCycleUtil(i, visited, recStack))
                return true;
        }
        return false;
    }

    std::vector<int> dijkstra(int start) {
        std::vector<int> dist(V, std::numeric_limits<int>::max());
        std::vector<bool> visited(V, false);
        
        dist[start] = 0;
        
        for (int count = 0; count < V - 1; count++) {
            int u = minDistance(dist, visited);
            visited[u] = true;
            
            for (auto& adj : adjList[u]) {
                if (!visited[adj.first] && dist[u] != std::numeric_limits<int>::max() 
                    && dist[u] + adj.second < dist[adj.first]) {
                    dist[adj.first] = dist[u] + adj.second;
                }
            }
        }
        return dist;
    }

private:
    bool hasCycleUtil(int v, std::vector<bool>& visited, std::vector<bool>& recStack) {
        if (!visited[v]) {
            visited[v] = true;
            recStack[v] = true;
            
            for (auto& adj : adjList[v]) {
                if (!visited[adj.first] && hasCycleUtil(adj.first, visited, recStack))
                    return true;
                else if (recStack[adj.first])
                    return true;
            }
        }
        recStack[v] = false;
        return false;
    }

    int minDistance(std::vector<int>& dist, std::vector<bool>& visited) {
        int min = std::numeric_limits<int>::max();
        int minIndex = -1;
        
        for (int v = 0; v < V; v++) {
            if (!visited[v] && dist[v] <= min) {
                min = dist[v];
                minIndex = v;
            }
        }
        return minIndex;
    }
};

int main() {
    Graph g(4);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 6);
    g.addEdge(2, 3, 7);

    std::cout << "DFS starting from vertex 0: ";
    g.DFS(0);
    std::cout << "\nBFS starting from vertex 0: ";
    g.BFS(0);
    std::cout << "\nHas cycle: " << (g.hasCycle() ? "Yes" : "No");
    
    std::vector<int> distances = g.dijkstra(0);
    std::cout << "\nShortest distances from vertex 0:\n";
    for (int i = 0; i < distances.size(); i++) {
        std::cout << "To " << i << ": " << distances[i] << "\n";
    }
    
    return 0;
}