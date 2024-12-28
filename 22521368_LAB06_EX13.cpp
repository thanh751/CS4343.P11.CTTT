#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <limits>
#include <algorithm>
using namespace std;

class CityNetwork {
private:
    struct Road {
        string destination;
        int capacity;
        int currentFlow;
        int lightTiming;
    };

    map<string, vector<Road>> network;
    
public:
    void addIntersection(const string& name) {
        if (network.find(name) == network.end()) {
            network[name] = vector<Road>();
        }
    }

    void addRoad(const string& from, const string& to, int capacity) {
        addIntersection(from);
        addIntersection(to);
        network[from].push_back({to, capacity, 0, 30}); // default 30s light timing
        network[to].push_back({from, capacity, 0, 30});
    }

    void updateTrafficFlow(const string& from, const string& to, int flow) {
        for (auto& road : network[from]) {
            if (road.destination == to) {
                road.currentFlow = flow;
                break;
            }
        }
    }

    vector<pair<string, double>> identifyBottlenecks() {
        vector<pair<string, double>> bottlenecks;
        for (const auto& intersection : network) {
            for (const auto& road : intersection.second) {
                double congestionLevel = (double)road.currentFlow / road.capacity;
                if (congestionLevel > 0.8) { // >80% capacity is considered bottleneck
                    bottlenecks.push_back({intersection.first + " -> " + road.destination, congestionLevel});
                }
            }
        }
        return bottlenecks;
    }

    map<string, int> optimizeTrafficLights() {
    map<string, int> optimizedTimings;
    for (auto& [intersection, roads] : network) {
        for (auto& road : roads) {
            // Simple optimization: adjust timing based on flow/capacity ratio
            double ratio = (double)road.currentFlow / road.capacity;
            int newTiming = max(20, min(60, int(30 * (1 + ratio))));
            optimizedTimings[intersection + " -> " + road.destination] = newTiming;
        }
    }
    return optimizedTimings;
}

    vector<string> findAlternativeRoute(const string& start, const string& end) {
        map<string, int> distance;
        map<string, string> previous;
        set<pair<int, string>> queue;

        for (const auto& node : network) {
            distance[node.first] = numeric_limits<int>::max();
        }
        distance[start] = 0;
        queue.insert({0, start});

        while (!queue.empty()) {
            string current = queue.begin()->second;
            queue.erase(queue.begin());

            if (current == end) break;

            for (const auto& road : network[current]) {
                int newDist = distance[current] + road.currentFlow;
                if (newDist < distance[road.destination]) {
                    queue.erase({distance[road.destination], road.destination});
                    distance[road.destination] = newDist;
                    previous[road.destination] = current;
                    queue.insert({newDist, road.destination});
                }
            }
        }

        vector<string> path;
        for (string at = end; at != ""; at = previous[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());
        return path;
    }
};

int main() {
    CityNetwork city;

    // Add sample road network
    city.addRoad("A", "B", 100);
    city.addRoad("B", "C", 80);
    city.addRoad("C", "D", 120);
    city.addRoad("A", "D", 90);
    city.addRoad("B", "D", 50);

    // Simulate traffic flow
    city.updateTrafficFlow("A", "B", 90);  // 90% capacity
    city.updateTrafficFlow("B", "C", 70);  // 87.5% capacity
    city.updateTrafficFlow("B", "D", 45);  // 90% capacity
    city.updateTrafficFlow("C", "D", 60);  // 50% capacity
    city.updateTrafficFlow("A", "D", 40);  // ~44% capacity

    cout << "Traffic Analysis Report\n";
    cout << "=====================\n\n";

    cout << "Identified Bottlenecks:\n";
    for (const auto& bottleneck : city.identifyBottlenecks()) {
        cout << bottleneck.first << ": " 
             << (bottleneck.second * 100) << "% capacity used\n";
    }

    cout << "\nOptimized Traffic Light Timings:\n";
    for (const auto& timing : city.optimizeTrafficLights()) {
        cout << timing.first << ": " << timing.second << " seconds\n";
    }

    cout << "\nAlternative Route from A to D:\n";
    vector<string> route = city.findAlternativeRoute("A", "D");
    for (size_t i = 0; i < route.size(); i++) {
        cout << route[i];
        if (i < route.size() - 1) cout << " -> ";
    }
    cout << endl;

    return 0;
}