#include <iostream>

// More to read: https://en.cppreference.com/w/cpp/language/fold
// Use https://cppinsights.io/ to get a better feeling of how parameter packs expand

// Takes a bunch of values by const ref and sums them
template<typename... Args>
constexpr auto sum(const Args&... args) noexcept
{
    return (0 + ... + args);
}

// && has true as default value (if you pass 0 arguments)
template<typename... Args>
constexpr bool all(Args... args) noexcept
{
    return (args && ...);
}

// Sizeof example
// Note: && with a template means universal reference that can bind to anything
// std::forward is used to pass arguments to other functions while preserving constness and the value category (e.g. rvalues remain rvalues)
template<typename... Args>
constexpr auto average(Args&&... args) noexcept
{
    return sum(std::forward<Args>(args)...) / sizeof...(args);
}

// Can't be constexpr or noexcept because we are working with streams
template<typename ...Args>
void print(Args&& ... args)
{
    (std::cout << ... << args);
}

// Execute given function for every argument
template<typename F, typename ...Args>
constexpr void for_each(F&& f, Args&&... args) noexcept
{
    (std::forward<decltype(f)>(f)(std::forward<Args>(args)), ...);
}

template<typename F, typename Acc, typename... Args>
constexpr auto accumulate(F&& f, Acc init, Args&&... args) noexcept
{
    // common_type gives us a type that both Acc and Arg can be casted to
    std::common_type_t<Acc, Args...> acc = init;
    ((acc = std::forward<decltype(f)>(f)(acc, std::forward<Args>(args))), ...);
    return acc;
}

struct HackAdder
{
    int operator()(int a, int b) const &
    {
        std::cout << "LVALUE\n";
        return a + b;
    }

    // takes 'this' as an rvalue reference (just for a demonstration)
    int operator()(int a, int b) const &&
    {
        std::cout << "RVALUE\n";
        return a + b;
    }
};

// Useful trick to make lambdas with overload
template<typename... Ts>
// Parameter packs can be expanded for inheritance (overloaded inherits every given type)
struct overloaded : Ts...
{
    // Expanding with using. overloaded adds every operator() in this overload set
    using Ts::operator()...;
};
// Deduction guide (unneeded as of c++20)
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

int main()
{
    std::cout << "average: " << average(1.0, 2, 3, 5) << std::endl;

    auto print_with_delim = [](auto delim, auto x){ std::cout << x << delim; };
    auto print = [&](auto x) { print_with_delim(", ", x); };
    for_each(print, 1, 2, 3, 4, 5);
    std::cout << '\n';

    auto noisy_adder = [](auto x, auto y) { std::cout << "Adding " << y << '\n'; return x + y; };
    std::cout << accumulate(noisy_adder, 0, 1, 2, 3.4, 4, 5) << '\n';

    // Difference between lvalue and rvalue HackAdder
    auto ha = HackAdder{};
    std::cout << accumulate(ha, 0, 1, 2, 3.4, 4, 5) << '\n';
    std::cout << accumulate(HackAdder{}, 0, 1, 2, 3.4, 4, 5) << '\n';

    // overloaded example
    const auto overloaded_lambda = overloaded {
        [](int) { std::cout << "int\n"; },
        [](double) { std::cout << "double\n"; },
        [](auto) { std::cout << "default\n"; }
    };

    overloaded_lambda(1);
    overloaded_lambda(2.3);
    overloaded_lambda("asdasd");
}
