
#include <iostream>

#include <chrono>
using namespace std::chrono;
int Fragment1()
{
    int sum = 0;
    int n;
    std::cout << "Enter n for Fragment1: ";
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n-i; j++) {
            sum = sum + i + j;
        }
    }
    
    return sum;
}


int main()
{
    auto start = high_resolution_clock::now();
    Fragment1();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Actual Running Time for n: " << duration.count() << std::endl;

    
}