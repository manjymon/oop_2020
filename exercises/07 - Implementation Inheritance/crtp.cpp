// CRTP

#include <iostream>

// Any class that inherits from this gets all comparisons (other than <) for free
template<typename Derived>
// Requires <
class Comparable
{
 public:
    bool operator==(const Comparable<Derived>& other) const { return !(underlying() < other.underlying() || other.underlying() < underlying()); }
    bool operator!=(const Comparable<Derived>& other) const { return !(underlying() == other.underlying()); }
    bool operator> (const Comparable<Derived>& other) const { return other.underlying() < underlying(); }
    bool operator>=(const Comparable<Derived>& other) const { return !(underlying() < other.underlying()); }
    bool operator<=(const Comparable<Derived>& other) const { return !(underlying() > other.underlying()); }
 private:
    const Derived& underlying() const { return static_cast<const Derived&>(*this); }
    // Unneeded here, this is just for example
    Derived& underlying() { return static_cast<Derived&>(*this); }
};

struct Int : public Comparable<Int>
{
    Int() = default;
    Int(int a) : x{a} {}
    int x = 0;
};

// We can "override" == with a better performing one
bool operator==(const Int& lhs, const Int& rhs)
{
    return lhs.x == rhs.x;
}

bool operator<(const Int& lhs, const Int& rhs)
{
    return lhs.x == rhs.x;
}

int main()
{
    Int a{10};
    Int b{20};
    std::cout << std::boolalpha << (a != b);

    return 0;
}
