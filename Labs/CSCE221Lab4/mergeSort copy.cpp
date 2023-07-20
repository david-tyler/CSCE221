#include <iostream>
#include <assert.h>
using namespace std;


// TODO (student): sort the numbers into nonincreasing order using a merge sort
// TODO (student): implement the following two functions
void merge(int* A, int p, int q, int r) {
//p = left q = mid r = right
    auto leftArrSize = q - p + 1;
    auto rightArrSize = r-q;

    auto *leftArr = new int[leftArrSize];
    auto *rightArr = new int[rightArrSize];

    for(auto i = 0; i < leftArrSize; i++)
    {
        leftArr[i] = A[p + i];
    }
    for(auto j = 0; j < rightArrSize; j++)
    {
        rightArr[j] = A[q + 1 + j];
    }

    auto indexLeftArr = 0;
    auto indexRightArr = 0;
    int indexMergeArr = p;

    while(indexLeftArr < leftArrSize && indexRightArr < rightArrSize)
    {
        if(leftArr[indexLeftArr] >= rightArr[indexRightArr])
        {
            A[indexMergeArr] = leftArr[indexLeftArr];
            indexLeftArr++;
        }
        else if(leftArr[indexLeftArr] < rightArr[indexRightArr])
        {
            A[indexMergeArr] = rightArr[indexRightArr];
            indexRightArr++;
        }

        indexMergeArr++;
    }
    while(indexLeftArr < leftArrSize)
    {
        A[indexMergeArr] = leftArr[indexLeftArr];
        indexLeftArr++;
        indexMergeArr++;
    }
    while(indexRightArr < rightArrSize)
    {
        A[indexMergeArr] = rightArr[indexRightArr];
        indexRightArr++;
        indexMergeArr++;
    }
    delete[] leftArr;
    delete[] rightArr;

}


void mergeSort(int* A, int p, int r) {
    if (p >= r )
    {
        return;
    }
    int mid = p + (r - p) / 2;
    mergeSort(A, p, mid);
    mergeSort(A, mid+1, r);
    merge(A, p, mid, r);

}

int main() {
    // Don't modify the main function
    int test[] = {100, 3, 45, 7, 45, 57, 34, 12, 10};
    int sol[] = {100, 57, 45, 45, 34, 12, 10, 7, 3};
    mergeSort(test, 0, 9);

    for (int i = 0; i < 9; i++)
        assert(test[i]==sol[i]);

    cout << "Test passed." << endl;

    return 0;
}
