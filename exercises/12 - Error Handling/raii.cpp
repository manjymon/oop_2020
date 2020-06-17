// RAII
#include <iostream>

struct Container
{
    int *ptr;
    Container(int a): ptr{new int{a}} {
        std::cout << "allocated int\n";
    }
    ~Container() { delete ptr; std::cout << "deleted int\n"; }
};

void foo()
{
    try
    {
        Container c{10};
        std::cout << *c.ptr << std::endl;
        throw "Error\n";
        // ...

    } // "garbage collection"
    catch(const char* msg)
    {
        std::cout << msg;
        // ..
    }
}

int main()
{
    try
    {
    foo();

    }
    catch(...)
    {
        std::cout << "tyk\n";
    }
    // ...
}
