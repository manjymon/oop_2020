#include <iostream>
#include <utility>

struct Noisy
{
    Noisy() { std::cout << "ctor\n"; }
    Noisy(const Noisy&) { std::cout << "copy ctor\n"; }
    Noisy(Noisy&&) { std::cout << "move ctor\n"; }
    Noisy& operator=(const Noisy&) { std::cout << "copy assignment\n"; return *this; }
    Noisy& operator=(Noisy&&) { std::cout << "move assignment\n"; return *this; }
};

class Holder1
{
 public:
    Holder1(const Noisy& n) :
        m_n{n}
    {}
 private:
    Noisy m_n;
};

class Holder2
{
 public:
    Holder2(Noisy n) :
        m_n{std::move(n)}
    {}
 private:
    Noisy m_n;
};

class Holder3
{
 public:
    Holder3(const Noisy& n) :
        m_n{n}
    {}

    Holder3(Noisy&& n) :
        m_n{std::move(n)}
    {}
 private:
    Noisy m_n;
};

class Holder4
{
 public:
    template<typename T>
    Holder4(T&& n) :
        m_n{std::forward<T>(n)}
    {}
 private:
    Noisy m_n;
};

int main()
{
    Noisy n{};
    // Holder1 takes a const ref and always makes a copy
    std::cout << "-------H1-------\n";
    std::cout << "-------LV-------\n";
    Holder1 h11{n};
    std::cout << "-------RV-------\n";
    Holder1 h12{Noisy{}};
    // Holder2 always makes a copy and then moves (one less copy for rvalues)
    std::cout << "\n-------H2-------\n";
    std::cout << "-------LV-------\n";
    Holder2 h21{n};
    std::cout << "-------RV-------\n";
    Holder2 h22{Noisy{}};
    // Holder3 has 2 overloads const ref + copy and rvalue ref + move (best performance)
    std::cout << "\n-------H3-------\n";
    std::cout << "-------LV-------\n";
    Holder3 h31{n};
    std::cout << "-------RV-------\n";
    Holder3 h32{Noisy{}};
    // Holder4 takes by universal reference and perfectly forwards to the correct ctor (same perf as H3 but less code)
    std::cout << "\n-------H4-------\n";
    std::cout << "-------LV-------\n";
    Holder4 h41{n};
    std::cout << "-------RV-------\n";
    Holder4 h42{Noisy{}};

    return 0;
}
