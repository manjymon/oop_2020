#include <iostream>
#include <optional>

template<typename Func>
class lazy
{
 public:
    using result_type = std::invoke_result_t<Func>;
    explicit lazy(Func f): m_f{f} {}
    lazy(const lazy&) = delete;
    lazy& operator=(const lazy&) = delete;

    operator result_type()
    {
        if (!m_value)
        {
            m_value = m_f();
        }

        return m_value.value();
    }
 private:
    std::optional<result_type> m_value{std::nullopt};
    Func m_f;
};

template<typename F>
auto make_lazy(F f)
{
    return lazy<F>{f};
}

int main()
{
    auto x = make_lazy(
        [](){
            std::cout << "Imagine this is a sloooooooooow calculation\n";
            return 10 * 2;
        }
    );

    std::cout << "No calculation yet\n";

    [](int a) {
        std::cout << a << '\n';
    }(x);

    std::cout << x << '\n';

    return 0;
}
