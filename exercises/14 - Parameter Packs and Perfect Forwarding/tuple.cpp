#include <tuple>
#include <string>
#include <iostream>

// std::tie can combine multiple things into a single tuple
// tuples implement lexicographical ordering using the comparison operator of its members

struct Student
{
    unsigned int fn;
    std::string name;
};

bool operator<(const Student& lhs, const Student& rhs)
{
    return std::tie(lhs.fn, lhs.name) < std::tie(rhs.fn, rhs.name);
}

bool operator==(const Student& lhs, const Student& rhs)
{
    return std::tie(lhs.fn, lhs.name) == std::tie(rhs.fn, rhs.name);
}

int main()
{
    return 0;
}
