//Name: Trần Tịnh Đan Thanh
//Student's ID: 22521368
//Session 05 - Homework 04

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>

// Define the Artist structure
struct Artist {
    std::string uri;
    int popularity;
    std::vector<std::string> genres;
    int followers;

    // Parameterized Constructor
    Artist(const std::string& u, int p, const std::vector<std::string>& g, int f)
        : uri(u), popularity(p), genres(g), followers(f) {}

    // Default Constructor
    Artist()
        : uri(""), popularity(0), genres(), followers(0) {}
};

// Function to parse genres from a string
std::vector<std::string> parseGenres(const std::string& genreStr) {
    std::vector<std::string> genres;
    std::string genre = "";
    bool insideQuote = false;

    for (size_t i = 0; i < genreStr.size(); ++i) {
        char ch = genreStr[i];
        if (ch == '\'' && !insideQuote) {
            insideQuote = true;
            genre = "";
        }
        else if (ch == '\'' && insideQuote) {
            insideQuote = false;
            if (!genre.empty()) {
                genres.push_back(genre);
            }
            genre = "";
        }
        else if (insideQuote) {
            genre += ch;
        }
    }

    return genres;
}

// Function to get maximum value in a specific field
int getMax(const std::vector<Artist>& artists, bool useFollowers) {
    int max = useFollowers ? artists[0].followers : artists[0].popularity;
    for (const auto& artist : artists) {
        int value = useFollowers ? artist.followers : artist.popularity;
        if (value > max) {
            max = value;
        }
    }
    return max;
}

// Counting Sort used as a subroutine for Radix Sort
void countingSortForRadix(std::vector<Artist>& artists, int exp, bool useFollowers) {
    std::vector<Artist> output(artists.size());
    int count[10] = {0};

    // Store count of occurrences in count[]
    for (const auto& artist : artists) {
        int value = useFollowers ? artist.followers : artist.popularity;
        count[(value / exp) % 10]++;
    }

    // Change count[i] so that count[i] contains actual position of this digit in output[]
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array
    for (int i = artists.size() - 1; i >= 0; i--) {
        int value = useFollowers ? artists[i].followers : artists[i].popularity;
        int index = (value / exp) % 10;
        output[count[index] - 1] = artists[i];
        count[index]--;
    }

    // Copy the output array to artists[], so that artists now contains sorted numbers according to current digit
    artists = output;
}

// Radix Sort implementation
void radixSort(std::vector<Artist>& artists, bool useFollowers) {
    int max = getMax(artists, useFollowers);

    // Do counting sort for every digit. Note that instead of passing digit number, exp is passed.
    // exp is 10^i where i is the current digit number
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSortForRadix(artists, exp, useFollowers);
    }
}

// Counting Sort implementation for fixed range
void countingSort(std::vector<Artist>& artists, bool useFollowers) {
    int max = getMax(artists, useFollowers);
    std::vector<Artist> output(artists.size());
    std::vector<int> count(max + 1, 0);

    // Store count of each element
    for (const auto& artist : artists) {
        int value = useFollowers ? artist.followers : artist.popularity;
        count[value]++;
    }

    // Change count[i] so that count[i] contains actual position of this element in output[]
    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array
    for (int i = artists.size() - 1; i >= 0; i--) {
        int value = useFollowers ? artists[i].followers : artists[i].popularity;
        output[count[value] - 1] = artists[i];
        count[value]--;
    }

    artists = output;
}

// Comparison functions for different sorting criteria (if needed)
bool compareByPopularityDesc(const Artist& a, const Artist& b) {
    return a.popularity > b.popularity;
}

bool compareByFollowersDesc(const Artist& a, const Artist& b) {
    return a.followers > b.followers;
}

// Function to analyze performance
void analyzePerformance(const std::vector<Artist>& artists, const std::string& criteria) {
    std::cout << "\nSorting by " << criteria << ":\n";

    // Create a copy of artists for each sort to ensure fairness
    std::vector<Artist> radixSorted = artists;
    std::vector<Artist> countingSorted = artists;

    // Determine which field to sort
    bool useFollowers = false;
    if (criteria == "popularity") {
        useFollowers = false;
    }
    else if (criteria == "followers") {
        useFollowers = true;
    }
    else {
        std::cerr << "Invalid sorting criteria.\n";
        return;
    }

    // Radix Sort Performance
    auto start = std::chrono::high_resolution_clock::now();
    radixSort(radixSorted, useFollowers);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> radixDuration = end - start;
    std::cout << "Radix Sort time: " << radixDuration.count() << " seconds.\n";

    // Counting Sort Performance
    start = std::chrono::high_resolution_clock::now();
    countingSort(countingSorted, useFollowers);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> countingDuration = end - start;
    std::cout << "Counting Sort time: " << countingDuration.count() << " seconds.\n";

    // Optional: Verify that both sorted lists are equal
    bool areEqual = true;
    for (size_t i = 0; i < radixSorted.size(); ++i) {
        if (radixSorted[i].uri != countingSorted[i].uri ||
            radixSorted[i].popularity != countingSorted[i].popularity ||
            radixSorted[i].followers != countingSorted[i].followers ||
            radixSorted[i].genres != countingSorted[i].genres) {
            areEqual = false;
            break;
        }
    }
    std::cout << "Radix Sort and Counting Sort produce the same result: " << (areEqual ? "Yes" : "No") << "\n";
}

int main() {
    std::vector<Artist> artists;

    // Read CSV file
    std::ifstream file("D:/Lab4/Lab4.4/artists.csv");
    if (!file.is_open()) {
        std::cerr << "Error opening artists.csv\n";
        return 1;
    }

    std::string line;
    std::getline(file, line); // Skip header

    while (std::getline(file, line)) {
        std::vector<std::string> tokens;
        std::stringstream ss(line);
        std::string token;
        bool insideQuotes = false;
        std::string field = "";

        // Parse CSV line handling commas inside quotes
        for (size_t i = 0; i < line.size(); ++i) {
            char ch = line[i];
            if (ch == '"') {
                insideQuotes = !insideQuotes;
            }
            else if (ch == ',' && !insideQuotes) {
                tokens.push_back(field);
                field = "";
            }
            else {
                field += ch;
            }
        }
        tokens.push_back(field); // Add the last field

        if (tokens.size() >= 4) {
            std::string uri = tokens[0];
            int popularity = 0;
            int followers = 0;

            // Convert popularity
            try {
                popularity = std::stoi(tokens[1]);
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Invalid popularity value for URI " << uri << ": " << tokens[1] << "\n";
                continue; // Skip this record
            }

            // Parse genres
            std::vector<std::string> genres = parseGenres(tokens[2]);

            // Convert followers
            try {
                followers = std::stoi(tokens[3]);
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Invalid followers value for URI " << uri << ": " << tokens[3] << "\n";
                continue; // Skip this record
            }

            artists.emplace_back(uri, popularity, genres, followers);
        }
        else {
            std::cerr << "Insufficient data in line: " << line << "\n";
        }
    }

    file.close();

    if (artists.empty()) {
        std::cerr << "No valid artist data found.\n";
        return 1;
    }

    // Provide options for sorting
    std::string criteria;
    std::cout << "Enter sorting criteria (popularity, followers): ";
    std::cin >> criteria;

    if (criteria != "popularity" && criteria != "followers") {
        std::cerr << "Invalid sorting criteria entered.\n";
        return 1;
    }

    // Analyze performance for the chosen criteria
    analyzePerformance(artists, criteria);

    return 0;
}