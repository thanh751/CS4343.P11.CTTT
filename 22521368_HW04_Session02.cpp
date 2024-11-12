 //STT: 
 //Full Name: 

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <regex>

// Define the Post structure
struct Post {
    std::string text;
    int likes;
    int shares;
    int comments;
    std::string timestamp;

    Post(const std::string& t, int l, int s, int c, const std::string& ts)
        : text(t), likes(l), shares(s), comments(c), timestamp(ts) {}
};

std::vector<std::string> parseCSVLine(const std::string& line) {
    std::vector<std::string> tokens;
    std::regex csv_regex(R"((?:^|,)(\"(?:[^\"]+|\"\")*\"|[^,]*))");
    auto begin = std::sregex_iterator(line.begin(), line.end(), csv_regex);
    auto end = std::sregex_iterator();

    for (std::sregex_iterator i = begin; i != end; ++i) {
        std::string token = (*i)[1].str();
        if (!token.empty() && token[0] == '"') {
            token = token.substr(1, token.length() - 2);
            std::string::size_type pos = 0;
            while ((pos = token.find("\"\"", pos)) != std::string::npos) {
                token.replace(pos, 2, "\"");
                pos += 1;
            }
        }
        tokens.push_back(token);
    }
    return tokens;
}

// Quick Sort implementation
int partition(std::vector<Post>& posts, int low, int high, bool (*compare)(const Post&, const Post&)) {
    Post pivot = posts[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; ++j) {
        if (compare(posts[j], pivot)) {
            ++i;
            std::swap(posts[i], posts[j]);
        }
    }
    std::swap(posts[i + 1], posts[high]);
    return i + 1;
}

void quickSort(std::vector<Post>& posts, int low, int high, bool (*compare)(const Post&, const Post&)) {
    if (low < high) {
        int pi = partition(posts, low, high, compare);
        quickSort(posts, low, pi - 1, compare);
        quickSort(posts, pi + 1, high, compare);
    }
}

// Merge Sort implementation
void merge(std::vector<Post>& posts, int left, int mid, int right, bool (*compare)(const Post&, const Post&)) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary vectors
    std::vector<Post> L(posts.begin() + left, posts.begin() + mid + 1);
    std::vector<Post> R(posts.begin() + mid + 1, posts.begin() + right + 1);

    int i = 0, j = 0, k = left;

    // Merge the temporary vectors back into posts
    while (i < n1 && j < n2) {
        if (compare(L[i], R[j])) {
            posts[k++] = L[i++];
        } else {
            posts[k++] = R[j++];
        }
    }

    // Copy any remaining elements
    while (i < n1) {
        posts[k++] = L[i++];
    }
    while (j < n2) {
        posts[k++] = R[j++];
    }
}

void mergeSort(std::vector<Post>& posts, int left, int right, bool (*compare)(const Post&, const Post&)) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(posts, left, mid, compare);
        mergeSort(posts, mid + 1, right, compare);
        merge(posts, left, mid, right, compare);
    }
}

// Heap Sort implementation
void heapify(std::vector<Post>& posts, int n, int i, bool (*compare)(const Post&, const Post&)) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && compare(posts[left], posts[largest]))
        largest = left;
    if (right < n && compare(posts[right], posts[largest]))
        largest = right;
    if (largest != i) {
        std::swap(posts[i], posts[largest]);
        heapify(posts, n, largest, compare);
    }
}

void heapSort(std::vector<Post>& posts, bool (*compare)(const Post&, const Post&)) {
    int n = posts.size();
    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(posts, n, i, compare);
    for (int i = n - 1; i >= 0; --i) {
        std::swap(posts[0], posts[i]);
        heapify(posts, i, 0, compare);
    }
}

// Comparison functions
bool compareByLikes(const Post& a, const Post& b) {
    return a.likes > b.likes;
}

bool compareByShares(const Post& a, const Post& b) {
    return a.shares > b.shares;
}

bool compareByComments(const Post& a, const Post& b) {
    return a.comments > b.comments;
}

bool compareByTimestamp(const Post& a, const Post& b) {
    return a.timestamp > b.timestamp; // Assumes timestamp format is comparable
}

void sortPosts(std::vector<Post>& posts, const std::string& criteria) {
    if (criteria == "likes") {
        quickSort(posts, 0, posts.size() - 1, compareByLikes);
    } else if (criteria == "shares") {
        mergeSort(posts, 0, posts.size() - 1, compareByShares);
    } else if (criteria == "comments") {
        heapSort(posts, compareByComments);
    } else if (criteria == "time") {
        quickSort(posts, 0, posts.size() - 1, compareByTimestamp);
    }
}

void analyzePerformance(std::vector<Post> posts, const std::string& criteria) {
    auto start = std::chrono::high_resolution_clock::now();
    sortPosts(posts, criteria);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken to sort by " << criteria << ": " << duration.count() << " seconds." << std::endl;
}

int main() {
    std::vector<Post> posts;

    // Read the CSV file
    std::ifstream file("D:/Lab4/Lab4.2/sentimentdataset.csv");
    if (!file.is_open()) {
        std::cerr << "Error opening file 'sentimentdataset.csv'" << std::endl;
        return 1;
    }

    std::string line;
    // Skip the header
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens = parseCSVLine(line);

        // Split the line by commas
        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() < 10)
            continue; // Ensure there are enough columns

        // Extract required fields (adjust indices based on your CSV structure)
        std::string text = tokens[2];
        int likes = std::stoi(tokens[9]);     // Assuming 'Likes' is at index 9
        int shares = std::stoi(tokens[8]);    // Assuming 'Retweets' or 'Shares' is at index 8
        int comments = 0;                     // Set to 0 if not available
        std::string timestamp = tokens[4];    // Assuming 'Timestamp' is at index 4

        posts.emplace_back(text, likes, shares, comments, timestamp);
    }

    file.close();

    // Analyze performance for different criteria
    analyzePerformance(posts, "likes");
    analyzePerformance(posts, "shares");
    analyzePerformance(posts, "comments");
    analyzePerformance(posts, "time");

    return 0;
}