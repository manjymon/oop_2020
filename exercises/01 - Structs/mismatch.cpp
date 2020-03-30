#include <algorithm>
#include <iostream>

struct IteratorPair
{
    int * first{};
    int * second{};
};

IteratorPair mismatch(int * first_1, int * last_1, int * first_2, int * last_2)
{
    while (first_1 != last_1 && first_2 != last_2 && *first_1 == *first_2)
    {
        ++first_1;
        ++first_2;
    }

    return { first_1, first_2 };
}

int main()
{
    int arr1[]{ 1, 2, 3, 4, 5, 6 };
    int arr2[]{ 1, 2, 3, 40 };

    /* Bonus C++17 Structured Binding
    auto [first_1, first_2] = mismatch(arr1, std::end(arr1),
                                       arr2, std::end(arr2));
    */

    // Without structured binding
    IteratorPair result{mismatch(arr1, std::end(arr1),
                                 arr2, std::end(arr2))};

    int * first_1 = result.first;
    int * first_2 = result.second;

    std::for_each(first_1, std::end(arr1),
                  [](int num) { std::cout << num << ' '; });

    std::cout << '\n';

    std::for_each(first_2, std::end(arr2),
                  [](int num) { std::cout << num << ' '; });

    return 0;
}
