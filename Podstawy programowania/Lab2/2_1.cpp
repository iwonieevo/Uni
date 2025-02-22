#include <iostream>

int weirdSum(void);

int main()
{
    int result = weirdSum();
    std::cout << "\nWeird sum = " << result;
}

int weirdSum(void)
{
    int a = 0, sum = 0;
    while(a != 99)
    {
        std::cin >> a;
        if(-15 <= a && a <= 15)
            sum += a;
    }
    return sum;
}
