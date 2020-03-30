#include <iostream>
#include <algorithm>

template<typename T>
class ReverseIterator
{
 public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;
    
    ReverseIterator(pointer ptr): m_ptr{ptr} {}
    bool operator!=(const ReverseIterator& other) const
    {
        return m_ptr != other.m_ptr;
    }

    ReverseIterator& operator++()
    {
        --m_ptr;
        return *this;
    }

    ReverseIterator operator++(int)
    {
        ReverseIterator tmp{*this};
        --m_ptr;
        return *this;
    }

    const_reference operator*() const
    {
        return *m_ptr;
    }

    reference operator*()
    {
        return *m_ptr;
    }

    const_pointer operator->() const
    {
        return m_ptr;
    }

    pointer operator->()
    {
        return m_ptr;
    }

    ReverseIterator& operator+=(difference_type offset)
    {
        m_ptr -= offset;
        return *this;
    }

    ReverseIterator operator+(difference_type offset)
    {
        ReverseIterator result{*this};
        return (result += offset);
    }

    difference_type operator-(const ReverseIterator& other)
    {
        return other.m_ptr - m_ptr;
    }

    ReverseIterator operator-(difference_type offset)
    {
        ReverseIterator result{*this};
        return (result -= offset);
    }

    ReverseIterator& operator-=(difference_type offset)
    {
        return (*this += -offset);
    }

    ReverseIterator& operator--()
    {
        ++m_ptr;
        return *this;
    }

    ReverseIterator operator--(int)
    {
        ReverseIterator tmp{*this};
        ++m_ptr;
        return tmp;
    }

    operator bool() const
    {
        return m_ptr != nullptr;
    }
 private:
    pointer m_ptr{nullptr};
};

template<typename T, size_t m_size>
struct array
{
 public:
    size_t size() const { return m_size; }
    bool empty() const { return m_size != 0; }

    const T* cbegin() const { return std::cbegin(m_arr); }
    const T* cend() const { return std::cend(m_arr); }
    T* begin() { return std::begin(m_arr); }
    T* end() { return std::end(m_arr); }
    
    ReverseIterator<T> rbegin() { return { end() - 1 }; }
    ReverseIterator<T> rend() { return { begin() - 1 }; }
    
    T& operator[](size_t index) { return m_arr[index]; }
    const T& operator[](size_t index) const { return m_arr[index]; }
    
    T& front() { return *begin(); }
    const T& front() const { return *cbegin(); }
    
    T& back() { return *(end() - 1); }
    const T& back() const { return *(cend() - 1); }
    
    T* data() { return m_arr; }
    const T* data() const { return m_arr; }
    
    void fill(const T& elem) { std::fill(begin(), end(), elem); }

    T m_arr[m_size];
};

template<typename T, size_t m_size>
bool operator==(const array<T, m_size>& lhs, const array<T, m_size>& rhs)
{
    return std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
}

template<typename T, size_t m_size>
bool operator!=(const array<T, m_size>& lhs, const array<T, m_size>& rhs)
{
    return !(lhs == rhs);
}

template<typename T, size_t m_size>
bool operator<(const array<T, m_size>& lhs, const array<T, m_size>& rhs)
{
    return std::lexicographical_compare(lhs.cbegin(), lhs.cend(), rhs.cbegin());
}

template<typename T, size_t m_size>
bool operator>(const array<T, m_size>& lhs, const array<T, m_size>& rhs)
{
    return rhs < lhs;
}

template<typename T, size_t m_size>
bool operator<=(const array<T, m_size>& lhs, const array<T, m_size>& rhs)
{
    return !(rhs < lhs);
}

template<typename T, size_t m_size>
bool operator>=(const array<T, m_size>& lhs, const array<T, m_size>& rhs)
{
    return !(lhs < rhs);
}

template<typename T, size_t m_size>
std::ostream& operator<<(std::ostream& out, const array<T, m_size> arr)
{
    std::for_each(
        arr.cbegin(),
        arr.cend(),
        [&](const T& element) {
            std::cout << element << ' ';
        }
    );

    return out;
}

int main()
{
    array<int, 3> xx{6, 5, 4};
    
    struct print { void operator()(int a) { std::cout << a << ' '; } };

    std::cout << xx << std::endl;

    for (int num : xx)
    {
        std::cout << num << ' ';
    }

    std::cout << std::endl;

    std::for_each(
        xx.rbegin(),
        xx.rend(),
        print{}
    );

    std::cout << std::endl;

    std::cout << *std::lower_bound(
        xx.rbegin(),
        xx.rend(),
        5
    ) << std::endl;

    std::cout << '\n';

    return 0;
}
