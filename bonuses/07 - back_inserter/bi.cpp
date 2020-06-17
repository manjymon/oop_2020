#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>

template<typename Container>
class back_inserter_iterator
{
 public:
    using iterator_category = std::output_iterator_tag;
    using value_type = typename Container::value_type;
    using difference_type = void;
    using pointer = void;
    using reference = void;

    back_inserter_iterator() = default;
    back_inserter_iterator(Container& container):
        m_container{&container}
    {}

    back_inserter_iterator& operator=(const value_type& value)
    {
        m_container->emplace_back(value);
        return *this;
    }

    back_inserter_iterator& operator*()
    {
        return *this;
    }

    back_inserter_iterator& operator++()
    {
        return *this;
    }

    back_inserter_iterator& operator++(int)
    {
        return *this;
    }

 private:
    Container* m_container{nullptr};
};

int main()
{
    std::vector<int> v;
    std::copy(
        std::istream_iterator<int>{std::cin},
        std::istream_iterator<int>{},
        back_inserter_iterator<std::vector<int>>{v}
    ); // OK. back_inserter deals with resizing

    for (int x : v)
    {
        std::cout << x;
    }

    return 0;
}
