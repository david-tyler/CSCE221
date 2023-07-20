// A C++ program to demonstrate common Binary Max-Heap Operations

#include<iostream>
#include <assert.h>
using namespace std;

// implement this function to insert the element x into the heap
void insert(int heap[], int& n, int x)
{
}

// implement this function to remove the root
void remove(int heap[], int& n)
{
}

int main() 
{
    int heap[100]; // The array to store the max-heap
    int n = 0;  // keep track the number of elements in the heap

    insert(heap, n, 1);
    insert(heap, n, 2);
    insert(heap, n, 4);
    insert(heap, n, 6); 
    insert(heap, n, 10);
    insert(heap, n, 11);
    insert(heap, n, 13);
    insert(heap, n, 15);

    assert(n==8);
    int sol1[] = {15, 13, 11, 6, 4, 2, 10, 1};
    int i = 0;

    for (i = 0; i < 8; i++)
        assert(heap[i]==sol1[i]);

    cout << "Test case 1 passed. " << endl;

    remove(heap, n);
    remove(heap, n);

    int sol2[] = {11, 6, 10, 1, 4, 2};
    for (i = 0; i < 6; i++)
        assert(heap[i]==sol2[i]);

    cout << "Test case 2 passed. " << endl;
    return 0;
}
