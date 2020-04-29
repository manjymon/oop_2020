#include <iostream>
#include <variant>
#include <string>
#include <vector>

class Empty {};

using Printable = std::variant<int, float, std::string, Empty>;

struct print_visitor
{
    void operator()(Empty) { std::cout << "Empty" << std::endl; }
    template<typename T>
    void operator()(const T& t) { std::cout << t << std::endl; }
};

int main()
{
    std::vector<Printable> v;
    v.emplace_back(1);
    v.emplace_back(2.3f);
    v.emplace_back("alabala");
    v.emplace_back(Empty{});

    for (const Printable& p : v)
    {
        std::visit(
            print_visitor{},
            p
        );
    }

    return 0;
}

