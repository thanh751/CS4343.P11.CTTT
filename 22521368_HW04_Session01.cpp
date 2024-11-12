 //STT: 
 //Full Name: 

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "csv.h" // Include the CSV parser library

struct Product {
    std::string name;
    double price;
    double rating;
    int popularity;

    Product(const std::string& n, double p, double r, int pop)
        : name(n), price(p), rating(r), popularity(pop) {}
};

// Quick Sort implementation
int partition(std::vector<Product>& products, int low, int high, bool (*compare)(const Product&, const Product&)) {
    Product pivot = products[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; ++j) {
        if (compare(products[j], pivot)) {
            ++i;
            std::swap(products[i], products[j]);
        }
    }
    std::swap(products[i + 1], products[high]);
    return i + 1;
}

void quickSort(std::vector<Product>& products, int low, int high, bool (*compare)(const Product&, const Product&)) {
    if (low < high) {
        int pi = partition(products, low, high, compare);
        quickSort(products, low, pi - 1, compare);
        quickSort(products, pi + 1, high, compare);
    }
}

// Merge Sort implementation
void merge(std::vector<Product>& products, int left, int mid, int right, bool (*compare)(const Product&, const Product&)) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<Product> L;
std::vector<Product> R;

// Reserve space to improve performance (optional)
L.reserve(n1);
R.reserve(n2);

for (int i = 0; i < n1; ++i)
    L.push_back(products[left + i]);

for (int j = 0; j < n2; ++j)
    R.push_back(products[mid + 1 + j]);

    for (int i = 0; i < n1; ++i)
        L[i] = products[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = products[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (compare(L[i], R[j])) {
            products[k++] = L[i++];
        } else {
            products[k++] = R[j++];
        }
    }

    while (i < n1)
        products[k++] = L[i++];
    while (j < n2)
        products[k++] = R[j++];
}

void mergeSort(std::vector<Product>& products, int left, int right, bool (*compare)(const Product&, const Product&)) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(products, left, mid, compare);
        mergeSort(products, mid + 1, right, compare);
        merge(products, left, mid, right, compare);
    }
}

// Heap Sort implementation
void heapify(std::vector<Product>& products, int n, int i, bool (*compare)(const Product&, const Product&)) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && compare(products[left], products[largest]))
        largest = left;
    if (right < n && compare(products[right], products[largest]))
        largest = right;

    if (largest != i) {
        std::swap(products[i], products[largest]);
        heapify(products, n, largest, compare);
    }
}

void heapSort(std::vector<Product>& products, bool (*compare)(const Product&, const Product&)) {
    int n = products.size();
    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(products, n, i, compare);
    for (int i = n - 1; i >= 0; --i) {
        std::swap(products[0], products[i]);
        heapify(products, i, 0, compare);
    }
}

// Comparison functions
bool compareByPrice(const Product& a, const Product& b) {
    return a.price < b.price;
}

bool compareByRating(const Product& a, const Product& b) {
    return a.rating > b.rating;
}

bool compareByPopularity(const Product& a, const Product& b) {
    return a.popularity > b.popularity;
}

void sortProducts(std::vector<Product>& products, const std::string& criteria) {
    if (criteria == "price") {
        quickSort(products, 0, products.size() - 1, compareByPrice);
    } else if (criteria == "rating") {
        mergeSort(products, 0, products.size() - 1, compareByRating);
    } else if (criteria == "popularity") {
        heapSort(products, compareByPopularity);
    }
}

void analyzePerformance(const std::vector<Product>& products, const std::string& criteria) {
    std::vector<Product> tempProducts = products;
    auto start = std::chrono::high_resolution_clock::now();
    sortProducts(tempProducts, criteria);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken to sort by " << criteria << ": " << duration.count() << " seconds" << std::endl;
}

int main() {
    std::vector<Product> products;

    // Read the CSV file
    io::CSVReader<4> in("D:/Lab4/Lab4.1/ElectronicsProductsPricingData.csv");
    in.read_header(io::ignore_extra_column, "name", "price", "rating", "popularity");
    std::string name;
    double price;
    double rating;
    int popularity;
    while (in.read_row(name, price, rating, popularity)) {
        products.emplace_back(name, price, rating, popularity);
    }

    // Analyze performance for sorting by price
    analyzePerformance(products, "price");

    // Analyze performance for sorting by rating
    analyzePerformance(products, "rating");

    // Analyze performance for sorting by popularity
    analyzePerformance(products, "popularity");

    return 0;
}