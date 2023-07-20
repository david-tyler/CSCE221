#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node()
    {
        data = 0;
        next = NULL;
    }
    Node(int data)
    {
        this->data = data;
        this->next = NULL;
    }
};
 
class Linkedlist {
public:
    Node* head;
    Linkedlist() { head = NULL; }
    void insertNode(int);
    void printList();
    void reverse();
};

void Linkedlist::insertNode(int data)
{
    Node* newNode = new Node(data);
    if (head == NULL) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void Linkedlist::printList()
{
    Node* temp = head;
    if (head == NULL) {
        cout << "List empty" << endl;
        return;
    }
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

void Linkedlist::reverse()
{
    Node* curr = this->head;
    Node* newHead = nullptr;
    Node* temp = nullptr;

    while (curr != nullptr)
    {
        temp = curr->next;
        curr->next = newHead;
        newHead = curr;
        curr = temp;
    }
    this->head = newHead;
}

int main(){
    Linkedlist* List1 = new Linkedlist();

    
    List1->insertNode(1); 
    List1->insertNode(2); 
    List1->insertNode(3); 
    List1->insertNode(4); 
    List1->insertNode(5);  
    List1->insertNode(6);
    List1->insertNode(7); 
    List1->insertNode(8); 
    List1->insertNode(9); 

    cout << "List before reversal: " << endl;
    List1->printList();
    List1->reverse();
    cout << endl;
    cout << "List after reversal: ";
    List1->printList();
}