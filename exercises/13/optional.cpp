#include <iostream>
#include <string>
#include <optional>


std::optional<int> divide(int a, int b)
{
    if (b == 0)
    {
        return std::nullopt;
    }

    return std::optional<int>{a/b};
}

template<typename T, typename F>
auto map(const std::optional<T>& opt, F f)
{
    return opt ? std::make_optional(f(opt.value())) : std::nullopt;
}

template<typename T, typename F>
auto or_else(const std::optional<T>& opt, F f)
{
    if (!opt)
    {
        f();
    }

    return opt;
}

int main()
{
    int a;
    int b;
    std::cin >> a >> b;

    auto inc = [](int x) {
        return x + 1;
    };

    auto twice = [](int x) {
        return x * 2;
    };

    auto print = [](int x) {
        std::cout << x;
        return true;
    };

    auto print_error = []() {
        std::cout << "error";
    };


    or_else(map(map(map(divide(a, b), inc), twice), print), print_error);

    return 0;
}
