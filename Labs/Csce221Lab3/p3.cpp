#include <iostream>

int main()
{
    int value = 0;
    int polynomial[] = {1, 2, 3, 4};
    int n = 4;
    int x = 5;
    for(int i = 0; i < n; i++)
    {
        value = value*x + polynomial[i];
    }
    std::cout << value;
}