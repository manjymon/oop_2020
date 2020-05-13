#include <iostream>

struct Noisy
{
    Noisy() { std::cout << "ctor\n"; }
    Noisy(const Noisy&) { std::cout << "copy\n"; }
    Noisy& operator=(const Noisy&) { std::cout << "copy=\n"; return *this; }
    Noisy& operator=(Noisy&&) { std::cout << "move=\n"; return *this; }
    Noisy(Noisy&&) { std::cout << "move\n"; }
};

struct Holder
{
    Noisy n;
    void set(const Noisy& other)
    {
        n = other;
    }

/*    void set(Noisy other)
    {
        n = std::move(other);
    }*/

    // overload
    void set(Noisy&& other)
    {
        n = std::move(other);
    }
};

void foo(const Noisy& other)
{
    std::cout << other.some_func();
}

int main()
{
    Holder h;
    Noisy n;
    std::cout << "==========LVALUE==================\n";
    h.set(n);
    std::cout << "===========RVALUE=================\n";
    h.set(Noisy{});
    std::cout << "============================\n";
    return 0;
}
