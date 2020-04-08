#include <iostream>

struct Empty { };

struct HasEmpty
{
    Empty e;
    int x;
};

struct InheritsEmpty : Empty
{
    int x;
};

int main()
{
    std::cout << sizeof(Empty) << '\n'; // 1: objects cannot have size 0
    std::cout << sizeof(HasEmpty) << '\n'; // 8: 1 byte for empty, 3 padding, 4 int
    std::cout << sizeof(InheritsEmpty) << '\n'; // 4: Empty base optimization, empty base classes don't need an unique address in their child
    return 0;
}
