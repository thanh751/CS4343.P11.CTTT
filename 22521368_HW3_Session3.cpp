 //STT: 39 (Example)
 //Full Name: X, With X is you, don’t need to find X anywhere else.
 //Homework - Exercise 01
 //Notes or Remarks: .....

#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;

bool searchOperation() {
    // Simulate a search operation that may fail
    return rand() % 2 == 0; // 50% chance of success
}

void exponentialBackoffSearch(int maxRetries, int baseDelay) {
    int attempt = 0;
    while (attempt < maxRetries) {
        if (searchOperation()) {
            cout << "Search successful on attempt " << attempt + 1 << endl;
            return;
        } else {
            cout << "Search failed on attempt " << attempt + 1 << ". Retrying..." << endl;
            int delay = baseDelay * (1 << attempt); // Exponential backoff
            this_thread::sleep_for(chrono::milliseconds(delay));
            attempt++;
        }
    }
    cout << "Search failed after " << maxRetries << " attempts." << endl;
}

int main() {
    srand(time(0)); // Seed for random number generation

    int maxRetries = 5;
    int baseDelay = 100; // Base delay in milliseconds

    exponentialBackoffSearch(maxRetries, baseDelay);

    return 0;
}
/*
This approach is particularly useful in distributed systems where multiple clients may be making requests simultaneously, and it helps to balance the load and improve overall system stability.
*/