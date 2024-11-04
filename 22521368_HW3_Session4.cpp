 //STT: 39 (Example)
 //Full Name: X, With X is you, don’t need to find X anywhere else.
 //Homework - Exercise 01
 //Notes or Remarks: ....

#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

struct Point {
    vector<double> features;
    int label;
};

class ThreadedKNN {
private:
    vector<Point> dataset;
    int k;
    int num_threads;
    mutex mtx;

    double calculateDistance(const Point& p1, const Point& p2) {
        double sum = 0.0;
        for (size_t i = 0; i < p1.features.size(); ++i) {
            sum += pow(p1.features[i] - p2.features[i], 2);
        }
        return sqrt(sum);
    }

    vector<pair<double, int>> findKNearest(const Point& query, int start, int end) {
        priority_queue<pair<double, int>> pq;
        
        for (int i = start; i < end; ++i) {
            double dist = calculateDistance(query, dataset[i]);
            pq.push({-dist, dataset[i].label});
            if (pq.size() > k) {
                pq.pop();
            }
        }

        vector<pair<double, int>> result;
        while (!pq.empty()) {
            result.push_back({-pq.top().first, pq.top().second});
            pq.pop();
        }
        return result;
    }

public:
    ThreadedKNN(int k_neighbors, int threads) : k(k_neighbors), num_threads(threads) {}

    void loadData(const string& filename) {
        ifstream file(filename);
        string line;
        
        while (getline(file, line)) {
            stringstream ss(line);
            string value;
            Point point;
            
            while (getline(ss, value, ',')) {
                if (point.features.size() < 4) {
                    point.features.push_back(stod(value));
                } else {
                    point.label = stoi(value);
                }
            }
            dataset.push_back(point);
        }
    }

    int predict(const Point& query) {
        vector<thread> threads;
        vector<vector<pair<double, int>>> thread_results(num_threads);
        
        int chunk_size = dataset.size() / num_threads;
        
        auto start_time = chrono::high_resolution_clock::now();

        for (int i = 0; i < num_threads; ++i) {
            int start = i * chunk_size;
            int end = (i == num_threads - 1) ? dataset.size() : (i + 1) * chunk_size;
            
            threads.emplace_back([this, &query, start, end, i, &thread_results]() {
                thread_results[i] = findKNearest(query, start, end);
            });
        }

        for (auto& thread : threads) {
            thread.join();
        }

        // Merge results from all threads
        vector<pair<double, int>> merged_results;
        for (const auto& thread_result : thread_results) {
            merged_results.insert(merged_results.end(), 
                                thread_result.begin(), 
                                thread_result.end());
        }

        sort(merged_results.begin(), merged_results.end());
        merged_results.resize(k);

        // Vote for the most common class
        vector<int> votes(10, 0);  // Assuming 10 possible classes
        for (const auto& result : merged_results) {
            votes[result.second]++;
        }

        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
        cout << "Prediction time: " << duration.count() << " ms" << endl;

        return max_element(votes.begin(), votes.end()) - votes.begin();
    }
};

int main() {
    // Initialize KNN with k=5 and 4 threads
    ThreadedKNN knn(5, 4);
    
    // Load dataset
    knn.loadData("KNNAlgorithmDataset.csv");

    // Test query point
    Point query;
    query.features = {5.1, 3.5, 1.4, 0.2};  // Example features

    // Perform prediction
    int predicted_class = knn.predict(query);
    cout << "Predicted class: " << predicted_class << endl;

    return 0;
}