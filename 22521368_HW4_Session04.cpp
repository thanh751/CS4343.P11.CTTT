 //STT: 
 //Full Name: 

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>

// Define the Artist structure
struct Artist {
    std::string uri;
    int popularity;
    std::vector<std::string> genres;
    int followers;

    Artist(const std::string& u, int p, const std::vector<std::string>& g, int f)
        : uri(u), popularity(p), genres(g), followers(f) {}
};

// Function to parse genres from a string
std::vector<std::string> parseGenres(const std::string& genreStr) {
    std::vector<std::string> genres;
    std::string genre = "";
    bool insideQuote = false;

    for (char ch : genreStr) {
        if (ch == '\'' && !insideQuote) {
            insideQuote = true;
            genre = "";
        } else if (ch == '\'' && insideQuote) {
            insideQuote = false;
            genres.push_back(genre);
            genre = "";
        } else if (insideQuote) {
            genre += ch;
        }
    }

    return genres;
}

// Quick Sort implementation
int partition(std::vector<Artist>& artists, int low, int high, bool (*compare)(const Artist&, const Artist&)) {
    Artist pivot = artists[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; ++j) {
        if (compare(artists[j], pivot)) {
            ++i;
            std::swap(artists[i], artists[j]);
        }
    }
    std::swap(artists[i + 1], artists[high]);
    return i + 1;
}

void quickSort(std::vector<Artist>& artists, int low, int high, bool (*compare)(const Artist&, const Artist&)) {
    if (low < high) {
        int pi = partition(artists, low, high, compare);
        quickSort(artists, low, pi - 1, compare);
        quickSort(artists, pi + 1, high, compare);
    }
}

// Merge Sort implementation
void merge(std::vector<Artist>& artists, int left, int mid, int right, bool (*compare)(const Artist&, const Artist&)) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary vectors
    std::vector<Artist> L(artists.begin() + left, artists.begin() + mid + 1);
    std::vector<Artist> R(artists.begin() + mid + 1, artists.begin() + right + 1);

    int i = 0, j = 0, k = left;

    // Merge the temporary vectors back into artists
    while (i < n1 && j < n2) {
        if (compare(L[i], R[j])) {
            artists[k++] = L[i++];
        } else {
            artists[k++] = R[j++];
        }
    }

    // Copy any remaining elements
    while (i < n1) {
        artists[k++] = L[i++];
    }
    while (j < n2) {
        artists[k++] = R[j++];
    }
}

void mergeSort(std::vector<Artist>& artists, int left, int right, bool (*compare)(const Artist&, const Artist&)) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(artists, left, mid, compare);
        mergeSort(artists, mid + 1, right, compare);
        merge(artists, left, mid, right, compare);
    }
}

// Heap Sort implementation
void heapify(std::vector<Artist>& artists, int n, int i, bool (*compare)(const Artist&, const Artist&)) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && compare(artists[left], artists[largest]))
        largest = left;
    if (right < n && compare(artists[right], artists[largest]))
        largest = right;

    if (largest != i) {
        std::swap(artists[i], artists[largest]);
        heapify(artists, n, largest, compare);
    }
}

void heapSort(std::vector<Artist>& artists, bool (*compare)(const Artist&, const Artist&)) {
    int n = artists.size();
    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(artists, n, i, compare);
    for (int i = n - 1; i >= 0; --i) {
        std::swap(artists[0], artists[i]);
        heapify(artists, i, 0, compare);
    }
}

// Comparison functions
bool compareByPopularity(const Artist& a, const Artist& b) {
    return a.popularity > b.popularity; // Higher popularity first
}

bool compareByFollowers(const Artist& a, const Artist& b) {
    return a.followers > b.followers; // More followers first
}

bool compareByGenre(const Artist& a, const Artist& b) {
    if (a.genres.empty() && b.genres.empty()) return false;
    if (a.genres.empty()) return false;
    if (b.genres.empty()) return true;
    return a.genres[0] < b.genres[0]; // Compare first genre
}

// Sorting options
void sortArtists(std::vector<Artist>& artists, const std::string& criteria, const std::string& algorithm) {
    bool (*compare)(const Artist&, const Artist&) = nullptr;
    if (criteria == "popularity") {
        compare = compareByPopularity;
    } else if (criteria == "followers") {
        compare = compareByFollowers;
    } else if (criteria == "genre") {
        compare = compareByGenre;
    } else {
        std::cerr << "Invalid sorting criteria." << std::endl;
        return;
    }

    if (algorithm == "quick") {
        quickSort(artists, 0, artists.size() - 1, compare);
    } else if (algorithm == "merge") {
        mergeSort(artists, 0, artists.size() - 1, compare);
    } else if (algorithm == "heap") {
        heapSort(artists, compare);
    } else {
        std::cerr << "Invalid sorting algorithm." << std::endl;
        return;
    }
}

// Function to analyze performance
void analyzePerformance(const std::vector<Artist>& artists, const std::string& criteria) {
    std::vector<std::string> algorithms = {"quick", "merge", "heap"};
    for (const auto& algorithm : algorithms) {
        std::vector<Artist> tempArtists = artists; // Copy the original data
        auto start = std::chrono::high_resolution_clock::now();
        sortArtists(tempArtists, criteria, algorithm);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Time taken by " << algorithm << " sort for " << criteria << ": " << duration.count() << " seconds." << std::endl;
    }
}

int main() {
    std::vector<Artist> artists;

    // Read the CSV file
    std::ifstream file("D:/Lab4/Lab4.4/artists.csv");
    if (!file.is_open()) {
        std::cerr << "Error opening file 'artists.csv'" << std::endl;
        return 1;
    }

    std::string line;
    // Skip the header
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::vector<std::string> tokens;
        std::stringstream ss(line);
        std::string token;
        bool insideQuotes = false;
        std::string field = "";

        // Parse CSV line handling commas inside quotes
        for (char ch : line) {
            if (ch == '"' && !insideQuotes) {
                insideQuotes = true;
            } else if (ch == '"' && insideQuotes) {
                insideQuotes = false;
            } else if (ch == ',' && !insideQuotes) {
                tokens.push_back(field);
                field = "";
            } else {
                field += ch;
            }
        }
        tokens.push_back(field);

        if (tokens.size() < 4)
            continue; // Ensure there are enough columns

        // Extract fields
        std::string artistUri = tokens[0];
        int popularity = 0;
        try {
            popularity = std::stoi(tokens[1]);
        } catch (...) {
            popularity = 0;
        }
        std::vector<std::string> genres = parseGenres(tokens[2]);
        int followers = 0;
        try {
            followers = std::stoi(tokens[3]);
        } catch (...) {
            followers = 0;
        }

        artists.emplace_back(artistUri, popularity, genres, followers);
    }

    file.close();

    // Provide options for sorting
    std::string criteria;
    std::cout << "Enter sorting criteria (popularity, followers, genre): ";
    std::cin >> criteria;

    analyzePerformance(artists, criteria);

    return 0;
}