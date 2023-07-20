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
 
//template<typename T>
void printLots(Linkedlist* L, Linkedlist* P)
{
    Node* LTemp = L->head;
    Node* PTemp = P->head;
    int indexOfL = 0;
    while (PTemp != nullptr)
    {
        while(indexOfL < PTemp->data)
        {
            LTemp = LTemp->next;
            indexOfL++;
        }
        cout << LTemp->data << " ";
        PTemp = PTemp->next;
    }
    cout << endl;
}
int main()
{
    //List of int datatypes
    Linkedlist* L_One = new Linkedlist();
    L_One->insertNode(1);
    L_One->insertNode(2);
    L_One->insertNode(3);
    L_One->insertNode(4);
    L_One->insertNode(5);
    L_One->insertNode(6);
    L_One->insertNode(7);

    //List of indexes to print in List L
    Linkedlist* P_One = new Linkedlist();
    P_One->insertNode(1);
    P_One->insertNode(3);
    P_One->insertNode(4);
    P_One->insertNode(6);
    printLots(L_One, P_One);
}