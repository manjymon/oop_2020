#include <vector>
#include <iostream>

int memoized_fibonacci(size_t n)
{
    static std::vector<int> memo{0, 1};
    if (n + 1 > memo.size())
    {
        memo.resize(n + 1);
    }
    
    if (n != 0 && memo[n] == 0)
    {
        std::cout << "Calculating for " << n << std::endl;
        return memo[n] = memoized_fibonacci(n - 1) + memoized_fibonacci(n - 2);
    }
    
    return memo[n];
}

int main()
{
    std::cout << memoized_fibonacci(10);
    return 0;
}
