 //STT: 
 //Full Name: 

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <random>

// Define the Student structure
struct Student {
    std::string name;
    double grade;
    int age;

    Student(const std::string& n, double g, int a)
        : name(n), grade(g), age(a) {}
};

// Quick Sort implementation
int partition(std::vector<Student>& students, int low, int high, bool (*compare)(const Student&, const Student&)) {
    Student pivot = students[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; ++j) {
        if (compare(students[j], pivot)) {
            ++i;
            std::swap(students[i], students[j]);
        }
    }
    std::swap(students[i + 1], students[high]);
    return i + 1;
}

void quickSort(std::vector<Student>& students, int low, int high, bool (*compare)(const Student&, const Student&)) {
    if (low < high) {
        int pi = partition(students, low, high, compare);
        quickSort(students, low, pi - 1, compare);
        quickSort(students, pi + 1, high, compare);
    }
}

// Merge Sort implementation
void merge(std::vector<Student>& students, int left, int mid, int right, bool (*compare)(const Student&, const Student&)) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary vectors
    std::vector<Student> L(students.begin() + left, students.begin() + mid + 1);
    std::vector<Student> R(students.begin() + mid + 1, students.begin() + right + 1);

    int i = 0, j = 0, k = left;

    // Merge the temporary vectors back into students
    while (i < n1 && j < n2) {
        if (compare(L[i], R[j])) {
            students[k++] = L[i++];
        } else {
            students[k++] = R[j++];
        }
    }

    // Copy any remaining elements
    while (i < n1) {
        students[k++] = L[i++];
    }
    while (j < n2) {
        students[k++] = R[j++];
    }
}

void mergeSort(std::vector<Student>& students, int left, int right, bool (*compare)(const Student&, const Student&)) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(students, left, mid, compare);
        mergeSort(students, mid + 1, right, compare);
        merge(students, left, mid, right, compare);
    }
}

// Heap Sort implementation
void heapify(std::vector<Student>& students, int n, int i, bool (*compare)(const Student&, const Student&)) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && compare(students[left], students[largest]))
        largest = left;
    if (right < n && compare(students[right], students[largest]))
        largest = right;

    if (largest != i) {
        std::swap(students[i], students[largest]);
        heapify(students, n, largest, compare);
    }
}

void heapSort(std::vector<Student>& students, bool (*compare)(const Student&, const Student&)) {
    int n = students.size();
    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(students, n, i, compare);
    for (int i = n - 1; i >= 0; --i) {
        std::swap(students[0], students[i]);
        heapify(students, i, 0, compare);
    }
}

// Comparison functions
bool compareByName(const Student& a, const Student& b) {
    return a.name < b.name;
}

bool compareByGrade(const Student& a, const Student& b) {
    return a.grade > b.grade; // Higher grades first
}

bool compareByAge(const Student& a, const Student& b) {
    return a.age < b.age; // Younger students first
}

// Sorting options
void sortStudents(std::vector<Student>& students, const std::string& criteria, const std::string& algorithm) {
    bool (*compare)(const Student&, const Student&) = nullptr;
    if (criteria == "name") {
        compare = compareByName;
    } else if (criteria == "grade") {
        compare = compareByGrade;
    } else if (criteria == "age") {
        compare = compareByAge;
    } else {
        std::cerr << "Invalid sorting criteria." << std::endl;
        return;
    }

    if (algorithm == "quick") {
        quickSort(students, 0, students.size() - 1, compare);
    } else if (algorithm == "merge") {
        mergeSort(students, 0, students.size() - 1, compare);
    } else if (algorithm == "heap") {
        heapSort(students, compare);
    } else {
        std::cerr << "Invalid sorting algorithm." << std::endl;
        return;
    }
}

// Function to analyze performance
void analyzePerformance(const std::vector<Student>& students, const std::string& criteria) {
    std::vector<std::string> algorithms = {"quick", "merge", "heap"};
    for (const auto& algorithm : algorithms) {
        std::vector<Student> tempStudents = students; // Copy the original data
        auto start = std::chrono::high_resolution_clock::now();
        sortStudents(tempStudents, criteria, algorithm);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Time taken by " << algorithm << " sort for " << criteria << ": " << duration.count() << " seconds." << std::endl;
    }
}

int main() {
    std::vector<Student> students;

    // Read the CSV file
    std::ifstream file("D:/Lab4/Lab4.3/StudentsPerformance.csv");
    if (!file.is_open()) {
        std::cerr << "Error opening file 'StudentsPerformance.csv'" << std::endl;
        return 1;
    }

    std::string line;
    // Skip the header
    std::getline(file, line);

    // Random age generation
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dist(14, 18);

    while (std::getline(file, line)) {
        std::vector<std::string> tokens;
        std::stringstream ss(line);
        std::string token;
        bool insideQuote = false;

        // Parse CSV line handling commas inside quotes
        while (std::getline(ss, token, ',')) {
            if (!insideQuote && token.front() == '"') {
                insideQuote = true;
                token.erase(0, 1);
            }
            if (insideQuote && token.back() == '"') {
                insideQuote = false;
                token.pop_back();
            }
            tokens.push_back(token);
        }

        if (tokens.size() < 8)
            continue; // Ensure there are enough columns

        // Extract fields
        std::string name = tokens[0]; // Using 'gender' as a placeholder for name
        double mathScore = std::stod(tokens[5]);
        double readingScore = std::stod(tokens[6]);
        double writingScore = std::stod(tokens[7]);
        double averageGrade = (mathScore + readingScore + writingScore) / 3.0;
        int age = dist(gen);

        students.emplace_back(name, averageGrade, age);
    }

    file.close();

    // Provide options for sorting
    std::string criteria;
    std::cout << "Enter sorting criteria (name, grade, age): ";
    std::cin >> criteria;

    analyzePerformance(students, criteria);

    return 0;
}