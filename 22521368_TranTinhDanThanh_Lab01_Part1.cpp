//Name: Trần Tịnh Đan Thanh
//Student's ID: 22521368
//Session 01 - Exercise 01
#include <iostream>
#include <stack>

using namespace std;

class Node {
public:
    Node* next;
    int value;
    Node(int x) : value(x), next(NULL) {}
};

class LinkedList {
private:
    Node* head;
    Node* tail;

public:
    LinkedList() : head(NULL), tail(NULL) {}

    void print() {
        Node* temp = head;
        while (temp) {
            cout << temp->value << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Ex 1:
    void findMiddleNode() {
    if (head == NULL) return;
    Node* temp = head;
    int count = 0;
    while (temp != NULL) {
        temp = temp->next;
        count++;
    }
    int middle = count / 2;
    Node* temp1 = head;
    for (int i = 0; i < middle; i++) {
        temp1 = temp1->next;
    }
    if (count % 2 == 0) {
        Node* temp2 = head;
        for (int i = 0; i < middle - 1; i++) {
            temp2 = temp2->next;
        }
        cout << "The middle nodes are: " << temp2->value << " and " << temp1->value << endl;
    } else {
        cout << "The middle node is: " << temp1->value << endl;
    }
}

    // Ex 2:
    bool DetectCircle() {
        if (head == NULL) return false;

        Node* temp1 = head;
        Node* temp2 = head;
        while (temp2 != NULL && temp2->next != NULL) {
            temp1 = temp1->next;
            temp2 = temp2->next->next;
            if (temp1 == temp2) return true;
        }
        return false;
    }

    // Ex 3:
    static LinkedList* SortedLinkedList(LinkedList* list1, LinkedList* list2) {
        LinkedList* sortedList = new LinkedList();
        Node temp(0);
        Node* tail = &temp;
        temp.next = NULL;

        Node* list1Current = list1->head;
        Node* list2Current = list2->head;

        while (list1Current != NULL && list2Current != NULL) {
            if (list1Current->value < list2Current->value) {
                tail->next = list1Current;
                list1Current = list1Current->next;
            } else {
                tail->next = list2Current;
                list2Current = list2Current->next;
            }
            tail = tail->next;
        }

        if (list1Current != NULL) {
            tail->next = list1Current;
        }
        if (list2Current != NULL) {
            tail->next = list2Current;
        }

        sortedList->head = temp.next;
        return sortedList;
    }

    // Ex 4:
    void printCommonElements(LinkedList* other) {
        Node* temp1 = head;
        while (temp1) {
            Node* temp2 = other->head;
            while (temp2) {
                if (temp1->value == temp2->value) {
                    cout << temp1->value << " ";
                    break;
                }
                temp2 = temp2->next;
            }
            temp1 = temp1->next;
        }
        cout << endl;
    }

    // Ex 5:
    void reverse() {
        Node* prev = NULL;
        Node* temp = head;
        Node* next = NULL;
        while (temp != NULL) {
            next = temp->next;
            temp->next = prev;
            prev = temp;
            temp = next;
        }
        head = prev;
    }

    // Ex 6:
    void EliminateDuplicates() {
        Node* temp1 = head;
        while (temp1 != NULL && temp1->next != NULL) {
            if (temp1->value == temp1->next->value) {
                Node* temp2 = temp1->next;
                temp1->next = temp1->next->next;
                delete temp2;
            } else {
                temp1 = temp1->next;
            }
        }
    }

    // Ex 7:
    bool isPalindrome() {
        Node* temp1 = head;
        Node* temp2 = head;
        stack<int> s;

        while (temp2 && temp2->next) {
            s.push(temp1->value);
            temp1 = temp1->next;
            temp2 = temp2->next->next;
        }

        if (temp2) {
            temp1 = temp1->next;
        }

        while (temp1) {
            if (s.top() != temp1->value) {
                return false;
            }
            s.pop();
            temp1 = temp1->next;
        }
        return true;
    }

    // Ex 8:
    Node* searchValue(int x) {
        Node* temp = head;
        while (temp) {
            if (temp->value == x) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    ~LinkedList() {
        Node* temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }

    void append(int x) {
        Node* newNode = new Node(x);
        if (head == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
};

int main() {
    LinkedList list1;
    LinkedList list2;

    list1.append(1);
    list1.append(2);
    list1.append(3);
    list1.append(4);
    list1.append(5);

    list2.append(10);
    list2.append(20);
    list2.append(30);
    list2.append(40);
    list2.append(50);
    list2.append(60);

    int choice, value;
    
    do {
        cout << "Menu:\n";
        cout << "1. Find the Middle Node of List 1\n"; 
        cout << "2. Detect a Cycle in List 1\n";     
        cout << "3. Combine Two Sorted Linked Lists\n"; 
        cout << "4. Find the Intersection of Two Linked Lists\n"; 
        cout << "5. Reverse List 1\n";              
        cout << "6. Eliminate Duplicates from List 1\n"; 
        cout << "7. Check if List 1 is a Palindrome\n"; 
        cout << "8. Search for Value in List 1\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                list1.findMiddleNode();
                break;
            case 2:
                cout << (list1.DetectCircle() ? "Cycle detected" : "No cycle detected") << endl;
                break;
            case 3:
                {
                    LinkedList* mergedList = LinkedList::SortedLinkedList(&list1, &list2);
                    mergedList->print();
                    delete mergedList;
                }
                break;
            case 4:
                list1.printCommonElements(&list2); 
                break;
            case 5:
                list1.reverse();
                list1.print();
                break;
            case 6:
                list1.EliminateDuplicates();
                list1.print();
                break;
            case 7:
                cout << (list1.isPalindrome() ? "List is a palindrome" : "List is not a palindrome") << endl;
                break;
            case 8:
                cout << "Enter value to search: ";
                cin >> value;
                {
                    Node* result = list1.searchValue(value);
                    if (result) {
                        cout << "Value found: " << result->value << endl;
                    } else {
                        cout << "Value not found" << endl;
                    }
                }
                break;
            case 0:
                cout << "Exiting" << endl;
                break;
            default:
                cout << "Invalid choice." << endl;
        }
    } while (choice != 0);

    return 0;
}