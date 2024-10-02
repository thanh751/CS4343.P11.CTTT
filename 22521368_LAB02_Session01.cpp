//MSSV: 22521368
//Full name: Trần Tịnh Đan Thanh
//Session 02 - Exercise - Part 01

#include <iostream>
using namespace std;

struct node{
    node* link;
    int data;
    node(int input){
        data = input;
        link = NULL;
    }
};
struct stack{
    node* top;
    int maxNumb; 
    int count=0;
    // 1. Write a function to initialize the stack
    void initializeStack(){
        top = NULL;
        cout<<"Enter the total number of nodes included in the stack: "; 
        cin>>maxNumb;
        int n;
        while (1){
            if (count <= maxNumb){
                cout<<"Enter a value: "; cin>>n;
                if (n==0) break;
                push(n);
                count++;
            }
            else{
                cout<<"The stack has been full.";
                break;
            }
        }
    }
    //4. Write a function to push an element onto the stack.
    void push(int input){
        node* newTop = new node(input);
        if (top == NULL){
            top = newTop;
        }
        else {
            newTop->link = top;
            top = newTop;
        }
    }
    //5. Write a function to pop an element from the stack.
    int pop(){
        int result = top->data;
        node* tmp = top;
        top = top->link;
        delete tmp;
        return result;
    }
    // 2. Write a function to check if the stack is empty. If empty, return true, otherwise return false
    bool isEmpty(){
        if (top == NULL) return true;
        else return false;
    }
    //3. Write a function to check if the stack is full (if applicable). If full, return true, otherwise return false.
    bool isFull(){
        if (count>=maxNumb) return true;
        else return false;
    }
};
int main() {
    stack s;
    s.initializeStack();
    cout << "Is stack empty? " << (s.isEmpty() ? "Yes" : "No") << endl;
    cout << "Is stack full? " << (s.isFull() ? "Yes" : "No") << endl;
    cout << "Pushing 10 onto the stack." << endl;
    s.push(10);
    s.count++;
    cout << "Is stack full? " << (s.isFull() ? "Yes" : "No") << endl;
    int poppedValue = s.pop();
    cout << "Popped value: " << poppedValue << endl;
    cout << "Is stack empty? " << (s.isEmpty() ? "Yes" : "No") << endl;

    return 0;
}


