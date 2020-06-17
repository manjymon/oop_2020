#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

template<typename Container>
class back_inserter_iterator
{
 public:
    using iterator_category = std::output_iterator_tag;
    using value_type = void;
    using difference_type = void;
    using pointer = void;
    using reference = void;
    
    back_inserter_iterator() = default;
    back_inserter_iterator(Container& container) :
        m_container{&container}
    { }

    back_inserter_iterator& operator=(const typename Container::value_type& value)
    {
        m_container->push_back(value);
        
        return *this;
    }

    back_inserter_iterator& operator*() { return *this; }
    back_inserter_iterator& operator++() { return *this; }
    back_inserter_iterator& operator++(int) { return *this; }
 private:
    Container* m_container{nullptr};
};

template<typename Container>
// someone added std::back_inserter to the global namespace :@
auto my_back_inserter(Container& c)
{
    return back_inserter_iterator<Container>{c};
}

int main()
{
    std::vector<int> v;

    std::copy_if(
        std::istream_iterator<int>{std::cin},
        std::istream_iterator<int>{},
        my_back_inserter(v),
        [](int x) {
            return x % 2 == 0;
        }
    );

    for (auto num : v)
    {
        std::cout << num << std::endl;
    }

    return 0;
}
