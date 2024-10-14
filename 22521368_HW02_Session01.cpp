//Name: Trần Tịnh Đan Thanh
//Student's ID: 22521368
//Session 01 - Homework 02
#include <iostream>
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

    bool isEmpty() {
        return top == nullptr;
    }

    void print() {
        Node* current = top;
        cout << "STACK = < ";
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << ">\n";
    }
};

void printTowers(Stack& A, Stack& B, Stack& C) {
    cout << "A Tower\n";
    A.print();
    cout << "========================\n";
    cout << "B Tower\n";
    B.print();
    cout << "========================\n";
    cout << "C Tower\n";
    C.print();
    cout << "========================\n";
    cout << "Please input: ";
}

void moveDisk(Stack& src, Stack& dest, char s, char d) {
    if (src.isEmpty()) return;
    int disk = src.pop();
    dest.push(disk);
    cout << "Move disk " << disk << " from " << s << " to " << d << endl;
}

void hanoi(int n, Stack& A, Stack& B, Stack& C, char a, char b, char c) {
    if (n == 1) {
        moveDisk(A, C, a, c);
        printTowers(A, B, C);
        return;
    }
    hanoi(n - 1, A, C, B, a, c, b);
    moveDisk(A, C, a, c);
    printTowers(A, B, C);
    hanoi(n - 1, B, A, C, b, a, c);
}

int main() {
    Stack A, B, C;
    int n = 3;  // Number of disks

    for (int i = n; i >= 1; --i) {
        A.push(i);
    }

    cout << "======== Demo Stack ========\n0. Creating Tower.\n";
    printTowers(A, B, C);

    hanoi(n, A, B, C, 'A', 'B', 'C');

    cout << "\nFinished status\n";
    printTowers(A, B, C);

    return 0;
}
