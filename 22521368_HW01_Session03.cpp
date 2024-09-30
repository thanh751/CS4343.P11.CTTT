//Name: Trần Tịnh Đan Thanh
//Student's ID: 22521368
//Session 03- Homework 01
#include <iostream>
#include <unordered_map>
#include <set>

using namespace std;

class Node {
public:
    string tokenId;
    int expiryTime;
    
       Node(string id, int time){
        tokenId=id;
        expiryTime=time; 
    }

    bool operator<(const Node& other) const {
        return expiryTime < other.expiryTime || 
               (expiryTime == other.expiryTime && tokenId < other.tokenId);
    }
};

class AuthenticationManager {
private:
    int timeToLive;
    unordered_map<string, int> tokenMap;
    set<Node> tokenExpirySet;

    void removeExpiredTokens(int currentTime) {
        while (!tokenExpirySet.empty() && tokenExpirySet.begin()->expiryTime <= currentTime) {
            string expiredTokenId = tokenExpirySet.begin()->tokenId;
            tokenMap.erase(expiredTokenId);
            tokenExpirySet.erase(tokenExpirySet.begin());
        }
    }

public:
    AuthenticationManager(int ttl) : timeToLive(ttl) {}

    void generate(string tokenId, int currentTime) {
        removeExpiredTokens(currentTime);
        int expiryTime = currentTime + timeToLive;
        tokenMap[tokenId] = expiryTime;
        tokenExpirySet.insert(Node(tokenId, expiryTime));
    }

    void renew(string tokenId, int currentTime) {
        removeExpiredTokens(currentTime);
        if (tokenMap.find(tokenId) != tokenMap.end() && tokenMap[tokenId] > currentTime) {
            tokenExpirySet.erase(Node(tokenId, tokenMap[tokenId]));
            int newExpiryTime = currentTime + timeToLive;
            tokenMap[tokenId] = newExpiryTime;
            tokenExpirySet.insert(Node(tokenId, newExpiryTime));
        }
    }

    int countUnexpiredTokens(int currentTime) {
        removeExpiredTokens(currentTime);
        return tokenMap.size();
    }
};

int main() {
    AuthenticationManager authManager(5);
    authManager.generate("aaa", 2);
    cout << authManager.countUnexpiredTokens(6) << endl; 
    authManager.generate("bbb", 7);
    authManager.renew("aaa", 8);
    authManager.renew("bbb", 10); 
    cout << authManager.countUnexpiredTokens(15) << endl; 
    return 0;
}