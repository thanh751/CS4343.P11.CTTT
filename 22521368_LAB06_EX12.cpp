#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

class SocialNetwork {
private:
    map<string, vector<string>> adjacencyList;
    vector<string> users;

public:
    // Add a new user to the network
    void addUser(const string& username) {
        if (adjacencyList.find(username) == adjacencyList.end()) {
            adjacencyList[username] = vector<string>();
            users.push_back(username);
        }
    }

    // Add a friendship between two users
    void addFriendship(const string& user1, const string& user2) {
        adjacencyList[user1].push_back(user2);
        adjacencyList[user2].push_back(user1);
    }

    // Calculate degree centrality for all users
    map<string, int> findInfluentialUsers() {
        map<string, int> degreeCentrality;
        for (const auto& user : adjacencyList) {
            degreeCentrality[user.first] = user.second.size();
        }
        return degreeCentrality;
    }

    // Find communities using BFS
    vector<vector<string>> findCommunities() {
        vector<vector<string>> communities;
        map<string, bool> visited;

        for (const auto& user : users) {
            if (!visited[user]) {
                vector<string> community;
                queue<string> q;
                q.push(user);
                visited[user] = true;

                while (!q.empty()) {
                    string currentUser = q.front();
                    q.pop();
                    community.push_back(currentUser);

                    for (const string& friend_ : adjacencyList[currentUser]) {
                        if (!visited[friend_]) {
                            visited[friend_] = true;
                            q.push(friend_);
                        }
                    }
                }
                communities.push_back(community);
            }
        }
        return communities;
    }

    // Print the network structure
    void printNetwork() {
        for (const auto& user : adjacencyList) {
            cout << user.first << " is friends with: ";
            for (const string& friend_ : user.second) {
                cout << friend_ << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    SocialNetwork network;

    // Add users
    network.addUser("Alice");
    network.addUser("Bob");
    network.addUser("Charlie");
    network.addUser("David");
    network.addUser("Eve");
    network.addUser("Frank");

    // Add friendships
    network.addFriendship("Alice", "Bob");
    network.addFriendship("Bob", "Charlie");
    network.addFriendship("Charlie", "Alice");
    network.addFriendship("David", "Eve");
    network.addFriendship("Eve", "Frank");

    cout << "Social Network Structure:\n";
    cout << "------------------------\n";
    network.printNetwork();

    cout << "\nInfluential Users (by degree centrality):\n";
    cout << "----------------------------------------\n";
    auto influentialUsers = network.findInfluentialUsers();
    for (const auto& user : influentialUsers) {
        cout << user.first << " has " << user.second << " connections\n";
    }

    cout << "\nCommunities in the Network:\n";
    cout << "-------------------------\n";
    auto communities = network.findCommunities();
    for (size_t i = 0; i < communities.size(); i++) {
        cout << "Community " << i + 1 << ": ";
        for (const string& user : communities[i]) {
            cout << user << " ";
        }
        cout << endl;
    }

    return 0;
}