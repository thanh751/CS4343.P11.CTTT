//Name: Trần Tịnh Đan Thanh
//Student's ID: 22521368
//Session 01 - Exercise 02 
//Name: Trần Tịnh Đan Thanh
//Student's ID: 22521368
//Session 01 - Exercise 02 
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Node {
public:
    Node* next;
    Node* random;
    int value;
    Node(int x) : value(x), next(NULL), random(NULL) {}
};

class LinkedList {
private:
    Node* head;
    Node* tail;

public:
    LinkedList() : head(NULL), tail(NULL) {}

    void printList() {
        Node* temp = head;
        while (temp != NULL) {
            cout << temp->value << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    //Ex 1:
    void addTwoNumbers(int val1, int val2, int position) {
        Node* newNode1 = new Node(val1);
        Node* newNode2 = new Node(val2);
        if (position == 0) { 
            newNode2->next = head;
            newNode1->next = newNode2;
            head = newNode1;
        } else {
            Node* temp = head;
            for (int i = 0; temp && i < position - 1; ++i) {
                temp = temp->next;
            }
            if (temp != NULL){ 
                temp = head;
                while (temp->next) {
                    temp = temp->next;
                }
                temp->next = newNode1;
                newNode1->next = newNode2;
            } else {
                newNode2->next = temp->next;
                newNode1->next = newNode2;
                temp->next = newNode1;
            }
        }
    }

    //Ex 2:
    LinkedList copyRandomList() {
        if (head == NULL) return LinkedList();
        Node* temp = head;
        Node* next;
        while (temp != NULL) {
            next = temp->next;
            Node* copy = new Node(temp->value);
            temp->next = copy;
            copy->next = next;
            temp = next;
        }
        temp = head;
        while (temp != NULL) {
            if (temp->random != NULL) {
                temp->next->random = temp->random->next;
            }
            temp = temp->next->next;
        }
        temp = head;
        Node* temp1 = new Node(0);
        Node* copy;
        Node* copytemp = temp1;
        while (temp != NULL) {
            next = temp->next->next;
            copy = temp->next;
            copytemp->next = copy;
            copytemp = copy;
            temp->next = next;
            temp = next;
        }
        LinkedList copiedList;
        copiedList.head = temp1->next;
        return copiedList;
    }

    //Ex 3:
    void swapNodes(int k) {
        if (head == NULL) return;
        Node* first = head;
        Node* second = head;
        Node* temp = head;
        int length = 0;
        while (temp != NULL) {
            length++;
            temp = temp->next;
        }
        for (int i = 1; i < k; ++i) {
            first = first->next;
        }
        for (int i = 1; i < length - k + 1; ++i) {
            second = second->next;
        }
        int tempValue = first->value;
        first->value = second->value;
        second->value = tempValue;
    }

    //Ex 4:
    void removeNthFromEnd(int n) {
        if (head == NULL) return;
        Node* temp1 = head;
        Node* temp2 = head;
        for (int i = 0; i < n; ++i) {
            if (temp1->next == NULL) {
                Node* temp3 = head;
                head = head->next;
                delete temp3;
                return;
            }
            temp1 = temp1->next;
        }
        while (temp1->next != NULL) {
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        Node* nodeToDelete = temp2->next;
        temp2->next = temp2->next->next;
        delete nodeToDelete;
    }

    //Ex 5:
    void separateOddEvenNodes() {
        if (head == NULL) return;
        Node* odd = head;
        Node* even = head->next;
        Node* evenHead = even;

        while (even && even->next) {
            odd->next = even->next;
            odd = odd->next;
            even->next = odd->next;
            even = even->next;
        }
        odd->next = evenHead;
    }

    //Ex 6:
    void splitListToParts(int k, Node** parts) {
        int length = 0;
        Node* current = head;
        while (current) {
            length++;
            current = current->next;
        }

        int partSize = length / k;
        int remainder = length % k;

        current = head;
        for (int i = 0; i < k; ++i) {
            Node* partHead = current;
            Node* partTail = partHead;

            for (int j = 0; j < partSize + (i < remainder ? 1 : 0) - 1; ++j) {
                if (partTail) partTail = partTail->next;
            }

            if (partTail) {
                Node* nextPart = partTail->next;
                partTail->next = NULL;
                current = nextPart;
            }

            parts[i] = partHead;
        }
    }

    //Ex 7:
    void removeZeroSum() {
        Node* temp = new Node(0);
        temp->next = head;
        Node* prev = temp;
        while (prev != NULL) {
            Node* curr = prev->next;
            int sum = 0;
            while (curr != NULL) {
                sum += curr->value;
                if (sum == 0) {
                    Node* toDelete = prev->next;
                    while (toDelete != curr) {
                        Node* nextToDelete = toDelete->next;
                        delete toDelete;
                        toDelete = nextToDelete;
                    }
                    prev->next = curr->next;
                    break;
                }
                curr = curr->next;
            }
            if (curr == NULL) prev = prev->next;
        }
        head = temp->next;
        delete temp;
    }

    //Ex 8:
    void addEnd(int x) {
        Node* newNode = new Node(x);
        if (head == NULL) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void automaticInput() {
        srand(time(0));
        int numEntries = (rand() % 21) + 39;
        for (int i = 0; i < numEntries; ++i) {
            int value = (rand() % 199) - 99; 
            addEnd(value);
        }
    }
};

int main() {
    LinkedList list;

    // Initialize list with some values
    list.addEnd(1);
    list.addEnd(2);
    list.addEnd(3);
    list.addEnd(4);
    list.addEnd(5);

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add two numbers\n";
        cout << "2. Copy random list\n";
        cout << "3. Swap nodes\n";
        cout << "4. Remove nth node from end\n";
        cout << "5. Separate odd and even nodes\n";
        cout << "6. Split list to parts\n";
        cout << "7. Remove zero sum sequences\n";
        cout << "8. Automatic input\n";
        cout << "9. Print list\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                int val1, val2, position;
                cout << "Enter first value: ";
                cin >> val1;
                cout << "Enter second value: ";
                cin >> val2;
                cout << "Enter position: ";
                cin >> position;
                list.addTwoNumbers(val1, val2, position);
                cout << "List after adding two numbers: ";
                list.printList();
                break;
            }
            case 2: {
                LinkedList copiedList = list.copyRandomList();
                cout << "Copied list: ";
                copiedList.printList();
                break;
            }
            case 3: {
                int k;
                cout << "Enter the position to swap: ";
                cin >> k;
                list.swapNodes(k);
                cout << "List after swapping nodes: ";
                list.printList();
                break;
            }
            case 4: {
                int n;
                cout << "Enter the position from the end to remove: ";
                cin >> n;
                list.removeNthFromEnd(n);
                cout << "List after removing nth node from end: ";
                list.printList();
                break;
            }
            case 5: {
                list.separateOddEvenNodes();
                cout << "List after separating odd and even nodes: ";
                list.printList();
                break;
            }
            case 6: {
                int k;
                cout << "Enter number of parts to split: ";
                cin >> k;
                Node* parts[k];
                list.splitListToParts(k, parts);
                cout << "List after splitting into " << k << " parts: ";
                for (int i = 0; i < k; ++i) {
                    Node* temp = parts[i];
                    cout << "Part " << i + 1 << ": ";
                    while (temp != NULL) {
                        cout << temp->value << " ";
                        temp = temp->next;
                    }
                    cout << endl;
                }
                break;
            }
            case 7: {
                list.removeZeroSum();
                cout << "List after removing zero sum sequences: ";
                list.printList();
                break;
            }
            case 8: {
                list.automaticInput();
                cout << "List after automatic input: ";
                list.printList();
                break;
            }
            case 9: {
                cout << "Current list: ";
                list.printList();
                break;
            }
            case 0:
                exit(0);
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
