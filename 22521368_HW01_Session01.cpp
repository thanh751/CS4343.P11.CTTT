//Name: Trần Tịnh Đan Thanh
//Student's ID: 22521368
//Session 01 - Homework 02
#include <iostream>
#include <string>

using namespace std;

class Node {
public:
    string url;
    Node* back;
    Node* forward;
    Node(string u){
        u=url;
        back=NULL;
        forward=NULL;
    }
};

class BrowserHistory{
private:
    Node* current;
public: 
    BrowserHistory(string homepage) {
        current = new Node(homepage);
    }
    void visit(string url){
        Node* newNode = new Node(url);
        current->forward = newNode;
        newNode->back = current;
        current = newNode;
    }
    string back(int steps){
        while(steps>0 && current->back!=NULL){
            current=current->back;
            steps--;
        }
        return current->url;
    }
    string forward(int steps){
        while(steps>0 && current->forward!=NULL){
            current=current->forward;
            steps--;
        }
        return current->url;
    }
    ~BrowserHistory() {
        Node* temp;
        while (current != nullptr) {
            temp = current;
            current = current->back; 
            delete temp;             
        }
    }
};
int main(){
    BrowserHistory* browserHistory = new BrowserHistory("uit.edu.vn");
    browserHistory->visit("google.com");
    browserHistory->visit("facebook.com");
    browserHistory->visit("youtube.com");

    cout << browserHistory->back(1) << endl; 
    cout << browserHistory->back(1) << endl; 
    cout << browserHistory->forward(1) << endl; 
    
    browserHistory->visit("linkedin.com");

    cout << browserHistory->forward(2) << endl; 
    cout << browserHistory->back(2) << endl;
    cout << browserHistory->back(7) << endl;

    delete browserHistory;

    return 0;
}