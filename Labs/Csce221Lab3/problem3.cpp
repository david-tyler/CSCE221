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

void Intersection(Linkedlist* L1, Linkedlist* L2)
{
    Node* L1_pos = L1->head;
    Node* L2_pos = L2->head;
   

    while(L1_pos != NULL && L2_pos != NULL)
    {
        if(L1_pos->data == L2_pos->data)
        {
            
            cout << L1_pos->data << " ";
            L1_pos = L1_pos->next;
            L2_pos = L2_pos->next;
        }
        else if(L1_pos->data < L2_pos->data)
        {
            L1_pos = L1_pos->next;
        }
        else if(L1_pos->data > L2_pos->data)
        {
            L2_pos = L2_pos->next;
        }
    }
   cout << endl;
}

int main(){
    Linkedlist* List1 = new Linkedlist();
    List1->insertNode(0); 
    List1->insertNode(2); 
    List1->insertNode(4); 
    List1->insertNode(6); 
    
    Linkedlist* List2 = new Linkedlist();
    List2->insertNode(1); 
    List2->insertNode(2); 
    List2->insertNode(3); 
    List2->insertNode(6);
    List2->insertNode(7); 

    Intersection(List1, List2);
}

