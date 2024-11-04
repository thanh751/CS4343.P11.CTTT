//MSSV: 22521368
//Full name: Tran Tinh Dan Thanh
//Classwork 3

#include <iostream>
#include <cmath>
#include <string>
#include <algorithm> 
#include <chrono>
#include <thread>
#include <vector>

using namespace std::chrono;
using namespace std;

void inputArray(int arr[], int& n) {
    cout << "Enter the number of elements: ";
    cin >> n;
    cout << "Enter the elements:\n";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
}
void inputStringArray(string arr[], int& n) {
    cout << "Enter the number of elements: ";
    cin >> n;
    cin.ignore();
    cout << "Enter the elements (one per line):\n";
    for (int i = 0; i < n; ++i) {
        getline(cin, arr[i]);
    }
}
//Ex1: Binary Search
int countOccurrences(int arr[], int n, int x) {
    // Find the index of the first occurrence of x
    int left = 0, right = n - 1, first = -1;
    cout<<"Binary Search starts:"<<endl
        <<"Searching for "<<x<<"..."<<endl
        <<"Step 1: Look for the first occurence of "<<x<<endl;
        while (left <= right) {
        cout<<"- Left = "<<left<<"; Right = "<<right<<endl;
        int mid = left + (right - left) / 2;
        cout<<"Middle index: "<<mid<<" - Value: "<<arr[mid]<<endl;
        if (arr[mid] == x) {
            first = mid;
            right = mid - 1; // Look for occurrences to the left
        } else if (arr[mid] < x) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    // If x is not present in arr[]
    if (first == -1){
        cout<<"Not found.";
        return 0;
    }
    cout<<"The index of the first occurrence of X is: "<<first<<endl
        <<"Step 2: Look for the last occurence of "<<x<<endl;
    // Find the index of the last occurrence of x
    left = first + 1;
    right = n - 1;
    int last = first;
    while (left <= right) {
        cout<<"- Left = "<<left<<"; Right = "<<right<<endl;
        int mid = left + (right - left) / 2;
        cout<<"Middle index: "<<mid<<" - Value: "<<arr[mid]<<endl;
        if (arr[mid] == x) {
            last = mid;
            left = mid + 1; // Look for occurrences to the right
        } else if (arr[mid] < x) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    cout<<"The index of the last occurrence of X is: "<<last<<endl;
    // Return the count
    return last - first + 1;
}
void Ex1(){
    int arr[100];
    int n;
    inputArray(arr,n);
    int x;
    cout<<"Enter X: "<<endl; cin>>x;
    int count = countOccurrences(arr, n, x);
    cout << "Count of " << x << " is " << count << endl;
}

//Ex2:
int jumpSearch(int arr[], int n, int x, int &step) {
    int prev = 0;
    cout<<"Jump Search starts:"<<endl
    <<"Searching for "<<x<<"..."<<endl;
    while (arr[min(step, n) - 1] < x) {
        prev = step;
        step += sqrt(n);
        cout<<"Step: "<<step<<endl;
        if (prev >= n)
            return -1;
    }
    while (arr[prev] < x) {
        prev++;
        if (prev == min(step, n))
            return -1;
    }
    if (arr[prev] == x){
        return prev;
    }
    return -1;
}
void Ex2(){
    int arr[100];
    int n;
    inputArray(arr,n);
    int x;
    cout<<"Enter X: "<<endl; cin>>x;
    int step = sqrt(n);
    int index = jumpSearch(arr, n, x, step);
    if (index != -1)
        cout << "Element " << x << " is found at index " << index << endl;
    else
        cout << "Element " << x << " is not found in array" << endl;
}

//Ex3:
int interpolationSearch(string arr[], int n, string x) {
    int low = 0, high = n - 1;
    cout<<"Interpolation Search starts:"<<endl
    <<"Searching for "<<x<<" in the array..."<<endl;
    while (low <= high && x >= arr[low] && x <= arr[high]) {
        if (low == high) {
            if (arr[low] == x) return low;
            return -1;
        }
        // Calculate the position using interpolation formula
        int pos = low + ((high - low) * (x.compare(arr[low]))) / (arr[high].compare(arr[low]));
        cout<<"Postition: "<<pos<<endl;
        // Check if the element at pos is the target
        if (arr[pos] == x) return pos;
        // If x is larger, x is in the upper part
        if (arr[pos] < x) low = pos + 1;
        // If x is smaller, x is in the lower part
        else high = pos - 1;
    }
    return -1;
}
void Ex3(){
    string arr[100];
    int n;
    inputStringArray(arr,n);
    string x;
    cout<<"Enter X: "<<endl; cin>>x;
    int index = interpolationSearch(arr, n, x);
    if (index != -1)
        cout <<"Element found at index "<<index<<endl;
    else
        cout<<"Element not found." <<endl;
}

//Ex4:
int findMissingNumber(int arr[], int n) {
    cout<<"Finding the missing number.."<<endl
        <<"Step 1: Sorting the unsorted array."<<endl;
    sort(arr, arr + n); // Ensure the array is sorted
    int left = 0, right = n - 1;
    cout<<"Step 2: Searching for the missing number in the array..."<<endl
    <<"Binary Search starts:"<<endl;
    while (left <= right) {
        cout<<"- Left = "<<left<<"; Right = "<<right<<endl;
        int mid = left + (right - left) / 2;
        cout<<"Middle index: "<<mid<<" - Value: "<<arr[mid]<<endl;
        // Check if the missing number is on the left side
        if (arr[mid] != mid) {
            if (mid == 0 || arr[mid - 1] == mid - 1) {
                return mid;
            }
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    // If no missing number is found in the range, it must be n
    return n;
}
void Ex4(){
    int arr[100];
    int n;
    inputArray(arr,n);
    int missingNumber = findMissingNumber(arr, n);
    if (missingNumber != -1) {
        cout << "The missing number is: " << missingNumber << endl;
    } else {
        cout << "No missing number found." << endl;
    }
}

//Ex5:
struct SearchResult {
    int index;
    int comparisons;
    duration<double> timeTaken;
};
SearchResult linearSearch(int arr[], int n, int x) {
    auto start = high_resolution_clock::now();
    auto start_time_t = system_clock::to_time_t(start);
    // Print the time
    cout<<"Linear Search starts at: "<<ctime(&start_time_t);
    int comparisons = 0;
    for (int i = 0; i < n; i++) {
        comparisons++;
        if (arr[i] == x) {
            auto end = high_resolution_clock::now();
            auto end_time_t = system_clock::to_time_t(end);
            // Print the time
            cout<<"Linear Search ends at: "<<ctime(&end_time_t);
            return {i, comparisons, end - start};
        }
    }
    auto end = high_resolution_clock::now();
    auto end_time_t = system_clock::to_time_t(end);
    // Print the time
    cout<<"Linear Search ends at: "<<ctime(&end_time_t);
    return {-1, comparisons, end - start};
}
SearchResult binarySearch(int arr[], int left, int right, int x) {
    auto start = high_resolution_clock::now();
    auto start_time_t = system_clock::to_time_t(start);
    // Print the time
    cout<<"Binary Search starts at: "<<ctime(&start_time_t);
    int comparisons = 0;
    while (left <= right) {
        cout<<"- Left = "<<left<<"; Right = "<<right<<endl;
        comparisons++;
        int mid = left + (right - left) / 2;
        cout<<"Middle index: "<<mid<<" - Value: "<<arr[mid]<<endl;
        if (arr[mid] == x) {
            auto end = high_resolution_clock::now();
            auto end_time_t = system_clock::to_time_t(end);
            // Print the time
            cout<<"Binary Search ends at: "<<ctime(&end_time_t);
            return {mid, comparisons, end - start};
        }
        if (arr[mid] < x)
            left = mid + 1;
        else
            right = mid - 1;
    }
    auto end = high_resolution_clock::now();
    auto end_time_t = system_clock::to_time_t(end);
    // Print the time
    cout<<"Binary Search ends at: "<<ctime(&end_time_t);
    return {-1, comparisons, end - start};
}
SearchResult jumpSearch(int arr[], int n, int x) {
    auto start = high_resolution_clock::now();
    auto start_time_t = system_clock::to_time_t(start);
    // Print the time
    cout<<"Jump Search starts at: "<<ctime(&start_time_t);
    int comparisons = 0;
    int step = sqrt(n);
    int prev = 0;
    while (arr[min(step, n) - 1] < x) {
        comparisons++;
        prev = step;
        step += sqrt(n);
        if (prev >= n) {
            auto end = high_resolution_clock::now();
            auto end_time_t = system_clock::to_time_t(end);
            // Print the time
            cout<<"Jump Search ends at: "<<ctime(&end_time_t);
            return {-1, comparisons, end - start};
        }
    }
    while (arr[prev] < x) {
        comparisons++;
        prev++;
        if (prev == min(step, n)) {
            auto end = high_resolution_clock::now();
            auto end_time_t = system_clock::to_time_t(end);
            // Print the time
            cout<<"Jump Search ends at: "<<ctime(&end_time_t);
            return {-1, comparisons, end - start};
        }
    }
    comparisons++;
    if (arr[prev] == x) {
        auto end = high_resolution_clock::now();
         auto end_time_t = system_clock::to_time_t(end);
        // Print the time
        cout<<"Jump Search ends at: "<<ctime(&end_time_t);
        return {prev, comparisons, end - start};
    }
    auto end = high_resolution_clock::now();
    auto end_time_t = system_clock::to_time_t(end);
    // Print the time
    cout<<"Jump Search ends at: "<<ctime(&end_time_t);
    return {-1, comparisons, end - start};
}
void Ex5(){
    int arr[100];
    int n;
    inputArray(arr,n);
    int x;
    cout<<"Enter X: "<<endl; cin>>x;
    SearchResult linearResult, binaryResult, jumpResult;

    thread linearThread([&]() { linearResult = linearSearch(arr, n, x); });
    thread binaryThread([&]() { binaryResult = binarySearch(arr, 0, n - 1, x); });
    thread jumpThread([&]() { jumpResult = jumpSearch(arr, n, x); });

    linearThread.join();
    binaryThread.join();
    jumpThread.join();

    cout << "Linear Search: Index = " << linearResult.index << ", Comparisons = " << linearResult.comparisons << ", Duration = " << linearResult.timeTaken.count() << " seconds" << endl;
    cout << "Binary Search: Index = " << binaryResult.index << ", Comparisons = " << binaryResult.comparisons << ", Duration = " << binaryResult.timeTaken.count() << " seconds" << endl;
    cout << "Jump Search: Index = " << jumpResult.index << ", Comparisons = " << jumpResult.comparisons << ", Duration = " << jumpResult.timeTaken.count() << " seconds" << endl;
}

//Ex6:
SearchResult bidirectionalBinarySearch(int arr[], int n, int x) {
    auto start = high_resolution_clock::now();
    auto start_time_t = system_clock::to_time_t(start);
    // Print the time
    cout<<"Bidirectional Binary Search starts at: "<<ctime(&start_time_t);
    int left = 0, right = n - 1;
    int comparisons = 0;
    while (left <= right) {
        cout<<"- Left = "<<left<<"; Right = "<<right<<endl;
        comparisons++;
        int midLeft = left + (right - left) / 2;
        cout<<"Middle left index: "<<midLeft<<" - Value: "<<arr[midLeft]<<endl;
        int midRight = right - (right - left) / 2;
        cout<<"Middle right index: "<<midRight<<" - Value: "<<arr[midRight]<<endl;
        if (arr[midLeft] == x) {
            auto end = high_resolution_clock::now();
            auto end_time_t = system_clock::to_time_t(end);
            // Print the time
            cout<<"Bidirectional Binary Search ends at: "<<ctime(&end_time_t);
            return {midLeft, comparisons, end - start};
        }
        if (arr[midRight] == x) {
            auto end = high_resolution_clock::now();
            auto end_time_t = system_clock::to_time_t(end);
            // Print the time
            cout<<"Bidirectional Binary Search ends at: "<<ctime(&end_time_t);
            return {midRight, comparisons, end - start};
        }

        if (arr[midLeft] < x) {
            left = midLeft + 1;
        } else {
            right = midLeft - 1;
        }

        if (arr[midRight] > x) {
            right = midRight - 1;
        } else {
            left = midRight + 1;
        }
    }

    auto end = high_resolution_clock::now();
    auto end_time_t = system_clock::to_time_t(end);
    // Print the time
    cout<<"Bidirectional Binary Search ends at: "<<ctime(&end_time_t);
    return {-1, comparisons, end - start};
}
void Ex6(){
    int arr[100];
    int n;
    inputArray(arr,n);
    int x;
    cout<<"Enter X: "<<endl; cin>>x;
    SearchResult bidirectionalResult = bidirectionalBinarySearch(arr, n, x);
    SearchResult traditionalResult = binarySearch(arr, 0, n - 1, x);

    cout << "Bidirectional Binary Search: Index = " << bidirectionalResult.index 
        << ", Comparisons = " << bidirectionalResult.comparisons 
        << ", Duration = " << bidirectionalResult.timeTaken.count() << " seconds" << endl;
    cout << "Traditional Binary Search: Index = " << traditionalResult.index 
        << ", Comparisons = " << traditionalResult.comparisons 
        << ", Duration = " << traditionalResult.timeTaken.count() << " seconds" << endl;
}

//Ex7:
//Sorting the array
int partition(int arr[], int left, int right) {
    int pivot = arr[right];
    int i = left;
    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[right]);
    return i;
}
//Implement binary search
int quickselect(int arr[], int left, int right, int k) {
    if (left == right) {
        return arr[left];
    }
    int pivotIndex = partition(arr, left, right);
    if (k == pivotIndex) {
        return arr[k];
    } else if (k < pivotIndex) {
        return quickselect(arr, left, pivotIndex - 1, k);
    } else {
        return quickselect(arr, pivotIndex + 1, right, k);
    }
}
void Ex7(){
    int arr[100];
    int n;
    inputArray(arr,n);
    int x;
    cout<<"Enter k: "<<endl; cin>>x;
    int result = quickselect(arr, 0, n - 1, x);
    cout << "The " << x << "rd smallest element is " << result << endl;
}


int main(){
    cout<<"--DSA Lab 3 Exercises--"<<endl
        <<"1. Counting the Occurrences of a Specified Number Using Modified Binary Search"<<endl
        <<"2. Dynamic Step Size Jump Search Implementation"<<endl
        <<"3. Lexicographically Sorted String Array Interpolation Search Modification"<<endl
        <<"4. Binary Search Missing Number Identification in Integer Array"<<endl
        <<"5. Concurrent Multi-Threaded Searching System Implementation"<<endl
        <<"6. Bidirectional Binary Search Algorithm Implementation and Performance Analysis"<<endl
        <<"7. Modified Binary Search Algorithm for Finding kth Smallest Element in Unsorted Array"<<endl
        <<"0. Exit"<<endl
        <<"---"<<endl;
    while(1){
        int n;
        cin>>n;
        switch (n){
            case 0:
                return 0;
            case 1:
                Ex1();
                break;
            case 2:
                Ex2();
                break;
            case 3:
                Ex3();
                break;
            case 4:
                Ex4();
                break;
            case 5:
                Ex5();
                break;
            case 6:
                Ex6();
                break;
            case 7:
                Ex7();
                break;
            default:
                cout<<"Retry.";
                break;
        }
    }
    return 0;
}