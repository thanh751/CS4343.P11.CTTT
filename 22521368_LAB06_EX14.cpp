//Name: Trần Tịnh Đan Thanh
//Student's ID: 22521368
//Exercise 14 
#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <string>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;

class RecommendationSystem {
private:
    map<string, map<string, double>> userItemRatings;
    vector<string> users;
    vector<string> items;

    double calculateSimilarity(const string& user1, const string& user2) {
        vector<double> ratings1, ratings2;
        for (const auto& item : items) {
            if (userItemRatings[user1].count(item) && userItemRatings[user2].count(item)) {
                ratings1.push_back(userItemRatings[user1][item]);
                ratings2.push_back(userItemRatings[user2][item]);
            }
        }
        
        if (ratings1.empty()) return 0.0;

        // Cosine similarity
        double dot = 0.0, norm1 = 0.0, norm2 = 0.0;
        for (size_t i = 0; i < ratings1.size(); i++) {
            dot += ratings1[i] * ratings2[i];
            norm1 += ratings1[i] * ratings1[i];
            norm2 += ratings2[i] * ratings2[i];
        }
        
        if (norm1 == 0.0 || norm2 == 0.0) return 0.0;
        return dot / (sqrt(norm1) * sqrt(norm2));
    }

public:
    void addRating(const string& user, const string& item, double rating) {
        userItemRatings[user][item] = rating;
        if (find(users.begin(), users.end(), user) == users.end())
            users.push_back(user);
        if (find(items.begin(), items.end(), item) == items.end())
            items.push_back(item);
    }

    vector<pair<string, double>> getRecommendations(const string& user, int k = 5) {
        map<string, double> predictions;
        map<string, bool> userItems;
        
        // Mark items already rated by user
        for (const auto& rating : userItemRatings[user]) {
            userItems[rating.first] = true;
        }

        // Calculate predictions for unrated items
        for (const auto& item : items) {
            if (!userItems[item]) {
                double weightedSum = 0.0;
                double similaritySum = 0.0;

                for (const auto& otherUser : users) {
                    if (otherUser != user && userItemRatings[otherUser].count(item)) {
                        double similarity = calculateSimilarity(user, otherUser);
                        weightedSum += similarity * userItemRatings[otherUser][item];
                        similaritySum += abs(similarity);
                    }
                }

                if (similaritySum > 0) {
                    predictions[item] = weightedSum / similaritySum;
                }
            }
        }

        // Get top k recommendations
        priority_queue<pair<double, string>> pq;
        for (const auto& pred : predictions) {
            pq.push({pred.second, pred.first});
        }

        vector<pair<string, double>> recommendations;
        while (!pq.empty() && recommendations.size() < k) {
            recommendations.push_back({pq.top().second, pq.top().first});
            pq.pop();
        }

        return recommendations;
    }
};

int main() {
    RecommendationSystem rs;

    // Add sample ratings (1-5 scale)
    rs.addRating("User1", "Book1", 5.0);
    rs.addRating("User1", "Book2", 3.0);
    rs.addRating("User1", "Book3", 4.0);
    
    rs.addRating("User2", "Book1", 3.0);
    rs.addRating("User2", "Book2", 4.0);
    rs.addRating("User2", "Book4", 5.0);
    
    rs.addRating("User3", "Book1", 4.0);
    rs.addRating("User3", "Book3", 3.0);
    rs.addRating("User3", "Book4", 4.0);
    
    rs.addRating("User4", "Book2", 4.0);
    rs.addRating("User4", "Book3", 5.0);
    rs.addRating("User4", "Book4", 4.0);

    cout << "E-commerce Recommendation System Demo\n";
    cout << "===================================\n\n";

    vector<string> testUsers = {"User1", "User2", "User3", "User4"};
    
    for (const auto& user : testUsers) {
        cout << "Recommendations for " << user << ":\n";
        auto recommendations = rs.getRecommendations(user, 3);
        
        for (const auto& rec : recommendations) {
            cout << rec.first << " (Predicted Rating: " 
                 << fixed << setprecision(2) << rec.second << ")\n";
        }
        cout << "\n";
    }

    return 0;
}