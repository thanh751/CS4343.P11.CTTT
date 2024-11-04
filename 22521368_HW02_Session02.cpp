//Name: Trần Tịnh Đan Thanh
//Student's ID: 22521368
//Session 02 - Homework 02
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct Node {
    string data;
    Node* next;
};

class Stack {
public:
    Node* top;

    Stack() : top(nullptr) {}

    void push(const string& data) {
        Node* newNode = new Node();
        newNode->data = data;
        newNode->next = top;
        top = newNode;
    }

    string pop() {
        if (isEmpty()) {
            throw out_of_range("Stack is empty");
        }
        Node* temp = top;
        string data = top->data;
        top = top->next;
        delete temp;
        return data;
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

class Browser {
private:
    Stack backStack;
    Stack forwardStack;
    string currentUrl;

public:
    Browser() : currentUrl("") {}

    void visit(const string& url) {
        if (!currentUrl.empty()) {
            backStack.push(currentUrl);
        }
        currentUrl = url;
        while (!forwardStack.isEmpty()) {
            forwardStack.pop();
        }
        cout << "Visited: " << currentUrl << endl;
    }

    string back() {
        if (backStack.isEmpty()) {
            cout << "No previous URL" << endl;
            return currentUrl;
        }
        forwardStack.push(currentUrl);
        currentUrl = backStack.pop();
        cout << "Back to: " << currentUrl << endl;
        return currentUrl;
    }

    string forward() {
        if (forwardStack.isEmpty()) {
            cout << "No forward URL" << endl;
            return currentUrl;
        }
        backStack.push(currentUrl);
        currentUrl = forwardStack.pop();
        cout << "Forward to: " << currentUrl << endl;
        return currentUrl;
    }
};

int main() {
    Browser browser;
    string input, command, url;

    while (true) {
        cout << "Enter command: ";
        getline(cin, input);
        stringstream ss(input);
        ss >> command;

        if (command == "visit") {
            ss >> url;
            browser.visit(url);
        } else if (command == "back") {
            browser.back();
        } else if (command == "forward") {
            browser.forward();
        } else if (command == "exit") {
            break;
        } else {
            cout << "Invalid command!" << endl;
        }
    }

    return 0;
}
