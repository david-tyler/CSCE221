#include <iostream>

#include <chrono>
using namespace std::chrono;

int Fragment2()
{
    int sum = 0;
    int n;
    std::cout << "Enter n for Fragment2: ";
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2 * i; j++) {
        sum = sum + i + j;
        }
    }
    return sum;
}

int main()
{

    auto start2 = high_resolution_clock::now();
    Fragment2();
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2 - start2);
    std::cout << "Actual Running Time for n: " << duration2.count() << std::endl;
    
}