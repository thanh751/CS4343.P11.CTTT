//Name: Trần Tịnh Đan Thanh
//Student's ID: 22521368
//Session 04 - Homework 02
#include <iostream>
#include <climits>

using namespace std;


struct Node {
    int index; 
    Node* next; 

    Node(int i) : index(i), next(nullptr) {}
};


class Stack {
private:
    Node* topNode; 

public:
    Stack() : topNode(nullptr) {}

   
    void push(int index) {
        Node* newNode = new Node(index);
        newNode->next = topNode;
        topNode = newNode;
    }

    
    void pop() {
        if (topNode) {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }

   
    int top() {
        if (topNode) {
            return topNode->index;
        }
        return -1; 
    }

    
    bool isEmpty() {
        return topNode == nullptr;
    }

   
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }
};


int minimumCoins(int prices[], int n) {

    Stack stack;


    for (int i = 0; i < n; ++i) {
        stack.push(i);
    }


    for (int i = (n - 1) / 2; i > 0; --i) {

        int minPriceIndex = -1;
        int minPrice = INT_MAX;

        for (int j = i; j < 2 * i + 1 && j < n; ++j) {
            if (prices[j] < minPrice) {
                minPrice = prices[j];
                minPriceIndex = j;
            }
        }

        prices[i - 1] += prices[minPriceIndex];
    }

    return prices[0];
}

int main() {
    int prices[] = {3,1,2};
	int prices2[] = {1,10,1,1};
	int prices3[] = {26,18,6,12,49,7,45,45};
    int n = sizeof(prices) / sizeof(prices[0]); 
	int k = sizeof(prices2) / sizeof(prices2[0]); 
    int l = sizeof(prices3) / sizeof(prices3[0]); 

    int result = minimumCoins(prices, n); 
    int result2 = minimumCoins(prices2, k); 
    int result3 = minimumCoins(prices3, l);

    cout << "Minimum coins needed: " << result << endl; 
    cout << "Minimum coins needed: " << result2 << endl; 
    cout << "Minimum coins needed: " << result3 << endl; 

    return 0;
}