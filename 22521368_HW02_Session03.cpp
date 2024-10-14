//Name: Trần Tịnh Đan Thanh
//Student's ID: 22521368
//Session 03 - Homework 02
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

struct Node {
    int data;
    Node* next;
};

class Stack {
public:
    Node* top;

    Stack() : top(nullptr) {}

    void push(int data) {
        Node* newNode = new Node();
        newNode->data = data;
        newNode->next = top;
        top = newNode;
    }

    int pop() {
        if (isEmpty()) {
            throw out_of_range("Stack is empty");
        }
        Node* temp = top;
        int data = top->data;
        top = top->next;
        delete temp;
        return data;
    }

    int peek() {
        if (isEmpty()) {
            throw out_of_range("Stack is empty");
        }
        return top->data;
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

vector<int> canSeePersonsCount(vector<int>& heights) {
    int n = heights.size();
    vector<int> answer(n, 0);
    Stack stack;

    for (int i = n - 1; i >= 0; --i) {
        int count = 0;
        while (!stack.isEmpty() && stack.peek() < heights[i]) {
            stack.pop();
            count++;
        }
        if (!stack.isEmpty()) {
            count++;
        }
        answer[i] = count;
        stack.push(heights[i]);
    }

    return answer;
}

int main() {
    string input;
    cout << "Enter heights (space-separated): ";
    getline(cin, input);
    stringstream ss(input);
    vector<int> heights;
    int height;

    while (ss >> height) {
        heights.push_back(height);
    }

    vector<int> result = canSeePersonsCount(heights);

    cout << "Output: [";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << result[i];
        if (i < result.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;

    return 0;
}
